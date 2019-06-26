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
        //sqliteDB_open();
        //sqliteDB_opt_delete_path(name);
        //sqliteDB_close();
        return 0;
    }
    return 0;
}
