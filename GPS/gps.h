#ifndef _GPS_H
	#define _GPS_H
//#include "types.h"

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

void gps_parse(char *line,GPS_INFO *GPS);
void writeSQLite(GPS_INFO *GPS);
#endif
