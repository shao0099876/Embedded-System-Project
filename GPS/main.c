/************************************************
 *  GPS read demo ,use com2
 *  by Zou jian guo <ah_zou@163.com>   
 *  2004-10-22
 *
*************************************************/


#include <termios.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <pthread.h>
#include "gps.h"


#define BAUDRATE B9600
#define COM1 "/dev/ttyS0"
//#define COM2 "/dev/ttySAC1"
#define COM2 "/dev/ttySAC1"
#define ENDMINITERM 27 /* ESC to quit miniterm */
#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE;
volatile int fd;
GPS_INFO gps_info;
int GET_GPS_OK=FALSE;
char GPS_BUF[1024];
static int baud=BAUDRATE;


int get_baudrate(int argc,char** argv);

void child_handler(int s)
{
  printf("stop!!!\n");
   STOP=TRUE;
}

/*--------------------------------------------------------*/
void* keyboard(void * data)		
{
    int c;
	for (;;){
		if((c=getchar()) == 10){
       		STOP=TRUE;
       		break ;
		}
		printf("key=%d\n",c);
	}
    return NULL;
}
/*--------------------------------------------------------*/
void* writeData(void * data)
{
	while(1){
		if(GET_GPS_OK){
			GET_GPS_OK=FALSE;
			printf("%s",GPS_BUF);
			gps_parse(GPS_BUF,&gps_info);
			writeSQLite(&gps_info);
		}
		usleep(100);
		if(STOP)break;
	}

}
/*--------------------------------------------------------*/
/* 
	READ GPS information handler 
	if receive the enter char ,then copy the line to GPS_BUF.
*/
void* receive(void * data)
{
	int i=0;
	char c;
	char buf[1024];
	GPS_INFO GPS;
  	printf("read modem\n");
  	while (STOP==FALSE) 
  	{
    	read(fd,&c,1); /* com port */
    	buf[i++] = c;
		if(c == '\n'){
			strncpy(GPS_BUF,buf,i);
			i=0;
			GET_GPS_OK=TRUE;
		}
		if(STOP)break;
		write(1,&c,1); /* stdout */
  	}
  	printf("exit from reading modem\n");
  	return NULL; 
}
void* start(void* data){
	struct termios oldtio,newtio,oldstdtio,newstdtio;
	//struct sigaction sa;
	int ok;
 	pthread_t th_a, th_b, th_show;
 	void * retval;

	fd = open(COM2, O_RDWR );
	if (fd <0) {
    	perror(COM2);
    	exit(-1);
  	}

  	tcgetattr(0,&oldstdtio);
  	tcgetattr(fd,&oldtio); /* save current modem settings */
  	tcgetattr(fd,&newstdtio); /* get working stdtio */
	newtio.c_cflag = baud | CRTSCTS | CS8 | CLOCAL | CREAD;/*ctrol flag*/
	newtio.c_iflag = IGNPAR; /*input flag*/
	newtio.c_oflag = 0;		/*output flag*/
 	newtio.c_lflag = 0;
 	newtio.c_cc[VMIN]=1;
	newtio.c_cc[VTIME]=0;

	/* now clean the modem line and activate the settings for modem */
 	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&newtio);/*set attrib	  */
	
  	//pthread_create(&th_a, NULL, keyboard, 0);
  	pthread_create(&th_b, NULL, receive, 0);

  	pthread_create(&th_show, NULL, writeData, 0);
	printf("stop =%d \n",STOP);
	while(!STOP){
		usleep(100000);
	}

	tcsetattr(fd,TCSANOW,&oldtio); /* restore old modem setings */
  	tcsetattr(0,TCSANOW,&oldstdtio); /* restore old tty setings */
  	close(fd);
  	exit(0); 
}
/*--------------------------------------------------------*/
int main(int argc,char** argv)
{

	struct termios oldtio,newtio,oldstdtio,newstdtio;
	//struct sigaction sa;
	int ok;
 	pthread_t th_a, th_b, th_show;
 	void * retval;

   	fd = open(COM2, O_RDWR );
	if (fd <0) {
    	perror(COM2);
    	exit(-1);
  	}
	
	if(argc < 2)
                printf("Default baudrate is 4800 bps. If not, please enter baudrate as a parameter\n");
       else
		baud=get_baudrate(argc, argv);

  	tcgetattr(0,&oldstdtio);
  	tcgetattr(fd,&oldtio); /* save current modem settings */
  	tcgetattr(fd,&newstdtio); /* get working stdtio */
	newtio.c_cflag = baud | CRTSCTS | CS8 | CLOCAL | CREAD;/*ctrol flag*/
	newtio.c_iflag = IGNPAR; /*input flag*/
	newtio.c_oflag = 0;		/*output flag*/
 	newtio.c_lflag = 0;
 	newtio.c_cc[VMIN]=1;
	newtio.c_cc[VTIME]=0;
	

 /* now clean the modem line and activate the settings for modem */
 	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&newtio);/*set attrib	  */
	
  	pthread_create(&th_a, NULL, keyboard, 0);
  	pthread_create(&th_b, NULL, receive, 0);

  	pthread_create(&th_show, NULL, show_gps_info, 0);
	printf("stop =%d \n",STOP);
	while(!STOP){
		usleep(100000);
	}

/*		
  	pthread_join(th_a, &retval);
  	pthread_join(th_b, &retval);
  	pthread_join(th_show, &retval);
*/
  	tcsetattr(fd,TCSANOW,&oldtio); /* restore old modem setings */
  	tcsetattr(0,TCSANOW,&oldstdtio); /* restore old tty setings */
  	close(fd);
  	exit(0); 
}

int get_baudrate(int argc,char** argv)
{
	int v=atoi(argv[1]);
	 switch(v){
		case 4800:
			return B4800;
			
		case 9600:
			return B9600;
			
		case 19200:
			return B19200;
			
		case 38400:
			return B38400;
			
		case 57600:
			return B57600;
			
		case 115200:
			return B115200;
		default:
			return -1;
	 } 	 
}
