#ifndef _GPS_H
#define _GPS_H
//头文件引用区
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <termios.h>
#include <pthread.h>
#include <string.h>
#include "YJSQLite.h"
//预定义区
#define BAUDRATE B9600
#define COM1 "/dev/ttyS0"
#define COM2 "/dev/ttySAC1"
#define ENDMINITERM 27 /* ESC to quit miniterm */
#define FALSE 0
#define TRUE 1
#define USE_BEIJING_TIMEZONE
//结构体定义区
typedef struct{
	int year;  
	int month; 
	int day;
	int hour;
	int minute;
	int second;
}date_time;
typedef struct{
	 date_time D;//时间
	 char status;  		//接收状态
	 double	latitude;   //纬度
	 double longitude;  //经度
	 char NS;           //南北极
	 char EW;           //东西
	 double speed;      //速度
	 double high;       //高度
}GPS_INFO;
//全局变量定义区
volatile int STOP=FALSE;
volatile int file_device;
GPS_INFO gps_info;
int GET_GPS_OK=FALSE;
char GPS_BUF[1024];
static int baud=BAUDRATE;

//函数声明区
void* start(void* data);//调用该函数启动线程以实现自动数据采集
//函数定义区
char *DATE_TIME_TO_STR(date_time time){
	char res[100];
	sprintf(res,"%d%d%d%d%d%d",time.year,time.month,time.day,time.minute,time.second);
	return res;
}
void writeSQLite(GPS_INFO *GPS)//改造成数据库读写函数
{
	/*	sqliteDB_open();
	char* a=sqliteDB_opt_select_alluser();
	sqliteDB_close();
	ui.textEdit->setText(a); */
	sqliteDB_open();
	char *name=DATE_TIME_TO_STR(GPS->D);
	char *longitude;
	sprintf(longitude,"%f",GPS->longitude);
	char *latitude;
	sprintf(latitude,"%f",GPS->latitude);
	char *high;
	sprintf(high,"%f",GPS->high);
	char *speed;
	sprintf(speed,"%f",GPS->speed);
	char *timer=name;
	sqliteDB_opt_addpath(name,longitude,latitude,high,speed,timer);
	sqliteDB_close();
}

////////////////////////////////////////////////////////////////////////////////
//解释gps发出的数据
//0      7  0   4 6   0     6 8 0        90         0  3      0        9  	
//$GPRMC,091400,A,3958.9870,N,11620.3278,E,000.0,000.0,120302,005.6,W*62	
//$GPGGA,091400,3958.9870,N,11620.3278,E,1,03,1.9,114.2,M,-8.3,M,,*5E	
static double get_double_number(char *s){
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
static int GetComma(int num,char *str){
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
static void UTC2BTC(date_time *GPS){
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
void gps_parse(char *line,GPS_INFO *GPS){
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
/*--------------------------------------------------------*/
void* writeData(void * data){
	while(TRUE){
		if(GET_GPS_OK){
			GET_GPS_OK=FALSE;
			gps_parse(GPS_BUF,&gps_info);
			writeSQLite(&gps_info);
		}
		usleep(100);
	}
	return NULL;
}
/*--------------------------------------------------------*/
/* 
	READ GPS information handler 
	if receive the enter char ,then copy the line to GPS_BUF.
*/
void* receive(void * data){
	int i=0;
	char buf[1024];
	GPS_INFO GPS;
	while(TRUE){
		char c;
		read(file_device,&c,1);
		buf[i++]=c;
		if(c=='\n'){
			strncpy(GPS_BUF,buf,i);
			i=0;
			GET_GPS_OK=TRUE;
		}
	}
	return NULL; 
}
void* start(void* data){
	struct termios oldtio,newtio,oldstdtio,newstdtio;
	int ok;
	pthread_t th_getdata,th_writeDB;

	file_device = open(COM2, O_RDWR);
	if (file_device <0) {
    	perror(COM2);
    	exit(-1);
  	}

  	tcgetattr(0,&oldstdtio);
  	tcgetattr(file_device,&oldtio); /* save current modem settings */
  	tcgetattr(file_device,&newstdtio); /* get working stdtio */
	newtio.c_cflag = baud | CRTSCTS | CS8 | CLOCAL | CREAD;/*ctrol flag*/
	newtio.c_iflag = IGNPAR; /*input flag*/
	newtio.c_oflag = 0;		/*output flag*/
 	newtio.c_lflag = 0;
 	newtio.c_cc[VMIN]=1;
	newtio.c_cc[VTIME]=0;

	/* now clean the modem line and activate the settings for modem */
 	tcflush(file_device, TCIFLUSH);
	tcsetattr(file_device,TCSANOW,&newtio);/*set attrib	  */
	
  	pthread_create(&th_getdata, NULL, receive, 0);
  	pthread_create(&th_writeDB, NULL, writeData, 0);
	//tcsetattr(file_device,TCSANOW,&oldtio); /* restore old modem setings */
  	//tcsetattr(0,TCSANOW,&oldstdtio); /* restore old tty setings */
  	//close(file_device);
  	return NULL;
}
#endif
