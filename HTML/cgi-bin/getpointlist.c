#include<stdio.h>
#include<stdlib.h>
#include"tools.h"
#include<string.h>
//#include"YJSQLite.h"
#define DEBUG 1
int main(){
    puts("Content-type: text/plain\n\n");
    char *data=getenv("QUERY_STRING");
    char* operate=analyze(data,"operate");
    if(strcmp(operate,"getpointlist")==0){
        char* res;
        //sqliteDB_open();
        //res=sqliteDB_opt_select_allpath();
        //sqliteDB_close();
        if(DEBUG){
            res="哈尔滨工业大学(威海)#122.067#37.517#0#0#P0#1#123.067#37.517#0#0#P1#2#122.067#38.517#0#0#P2";
        }
        printf("%s",res);
    }
    else{
        printf("error");
    }
}