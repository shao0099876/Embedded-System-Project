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
