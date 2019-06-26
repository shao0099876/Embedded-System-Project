#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tools.h"
//#include"YJSQLite.h"
#define DEBUG 1
int main(){
    char* type=getenv("CONTENT_TYPE");
    int length=atoi(getenv("CONTENT_LENGTH"));
    if(strcmp(type,"application/x-www-form-urlencoded")==0){
        char a[100];
        fread(a, sizeof(char), length, stdin); 
        a[length]='\0';
        char* name=analyze(a,"name");
        char* langitude=analyze(a,"langitude");
        char* latitude=analyze(a,"latitude");
        char* altitude="0";
        char* speed="0";
        char* time=name;
        //sqliteDB_open();
        //sqliteDB_opt_add_path(name,langitude,latitude,altitude,speed,time);
        //sqliteDB_close();
        return 0;
    }
    return 0;
}