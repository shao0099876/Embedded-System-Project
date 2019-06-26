#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char *analyze(char* raw_data,char* data){
    char* pos=strstr(raw_data,data);
    int length=0;
    while(length<strlen(pos)&&(char)*(pos+length)!='&'){
        length+=1;
    }
    char mid[50];
    memset(mid,'\0',sizeof(char)*50);
    strncpy(mid,pos,length);
    pos=strstr(mid,"=");
    pos=pos+1;
    char* res=malloc(sizeof(char)*strlen(pos)+1);
    strcpy(res,pos);
    res[strlen(pos)]='\0';
    return res;
}