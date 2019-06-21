#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
//#include "types.h"
#include "gps.h"

#define USE_BEIJING_TIMEZONE

static int GetComma(int num,char* str);
static void UTC2BTC(date_time *GPS);
static double get_double_number(char *s);

void writeSQLite(GPS_INFO *GPS)//改造成数据库读写函数
{
	// printf("DATE     : %ld-%02d-%02d \n",GPS->D.year,GPS->D.month,GPS->D.day);
	// printf("TIME     :  %02d:%02d:%02d \n",GPS->D.hour,GPS->D.minute,GPS->D.second);
	// printf("Latitude : %10.6f %c\n",GPS->latitude,GPS->NS);	
	// printf("Longitude: %10.6f %c\n",GPS->longitude,GPS->EW);	
	// printf("high     : %10.4f \n",GPS->high);	
	// printf("STATUS   : %c\n",GPS->status);	
}

////////////////////////////////////////////////////////////////////////////////
//解释gps发出的数据
//0      7  0   4 6   0     6 8 0        90         0  3      0        9  	
//$GPRMC,091400,A,3958.9870,N,11620.3278,E,000.0,000.0,120302,005.6,W*62	
//$GPGGA,091400,3958.9870,N,11620.3278,E,1,03,1.9,114.2,M,-8.3,M,,*5E	
void gps_parse(char *line,GPS_INFO *GPS)
////////////////////////////////////////////////////////////////////////////////
{
	int i,tmp,start,end;
	char c;
	char* buf=line;
	c=buf[5];

	if(c=='C'){//"GPRMC"
		GPS->D.hour   =(buf[ 7]-'0')*10+(buf[ 8]-'0');
		GPS->D.minute =(buf[ 9]-'0')*10+(buf[10]-'0');
		GPS->D.second =(buf[11]-'0')*10+(buf[12]-'0');
		tmp = GetComma(9,buf);
		GPS->D.day    =(buf[tmp+0]-'0')*10+(buf[tmp+1]-'0');
		GPS->D.month  =(buf[tmp+2]-'0')*10+(buf[tmp+3]-'0');
		GPS->D.year   =(buf[tmp+4]-'0')*10+(buf[tmp+5]-'0')+2000;
		//------------------------------
		GPS->status	  =buf[GetComma(2,buf)];
		GPS->latitude =get_double_number(&buf[GetComma(3,buf)]);
		GPS->NS       =buf[GetComma(4,buf)];
		GPS->longitude=get_double_number(&buf[GetComma(5,buf)]);
		GPS->EW       =buf[GetComma(6,buf)];
#ifdef USE_BEIJING_TIMEZONE
		UTC2BTC(&GPS->D);
#endif
	}
	if(c=='A'){ //"$GPGGA"
		GPS->high     = get_double_number(&buf[GetComma(9,buf)]);
		
	}
}

static double get_double_number(char *s)
{
	char buf[128];
	int i;
	double rev;
	i=GetComma(1,s);
	strncpy(buf,s,i);
	buf[i]=0;
	rev=atof(buf);
//	printf("s=%s ,buf= %s,val= %f\n",s,buf,rev);
	return rev;
	
}
////////////////////////////////////////////////////////////////////////////////
//得到指定序号的逗号位置
static int GetComma(int num,char *str)
{
	int i,j=0;
	int len=strlen(str);
	for(i=0;i<len;i++)
	{
		if(str[i]==',')j++;
		if(j==num)return i+1;	
	}
	return 0;	
}

//#ifdef USE_BEIJING_TIMEZONE
////////////////////////////////////////////////////////////////////////////////
//将世界时转换为北京时
static void UTC2BTC(date_time *GPS)
{

//***************************************************
//如果秒号先出,再出时间数据,则将时间数据+1秒
		GPS->second++; //加一秒
		if(GPS->second>59){
			GPS->second=0;
			GPS->minute++;
			if(GPS->minute>59){
				GPS->minute=0;
				GPS->hour++;
			}
		}	

//***************************************************
		GPS->hour+=8;
		if(GPS->hour>23)
		{
			GPS->hour-=24;
			GPS->day+=1;
			if(GPS->month==2 ||
			   		GPS->month==4 ||
			   		GPS->month==6 ||
			   		GPS->month==9 ||
			   		GPS->month==11 ){
				if(GPS->day>30){
			   		GPS->day=1;
					GPS->month++;
				}
			}
			else{
				if(GPS->day>31){
			   		GPS->day=1;
					GPS->month++;
				}
			}
			if(GPS->year % 4 == 0 ){//
		   		if(GPS->day > 29 && GPS->month ==2){
		   			GPS->day=1;
					GPS->month++;
				}
			}
			else{
		   		if(GPS->day>28 &&GPS->month ==2){
		   			GPS->day=1;
					GPS->month++;
				}
			}
			if(GPS->month>12){
				GPS->month-=12;
				GPS->year++;
			}		
		}
}
