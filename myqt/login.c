#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tools.h"
#include"/arm2410cl/Trolltech/qt-embedded-4.4.0/myqt/YJSQLite.h"
#define DEBUG 0
int main(){
    printf("Content-type: text/html\n\n");
    char *data=getenv("QUERY_STRING");
    char* username=analyze(data,"username");
    char* password=analyze(data,"password");
    char* a;
    sqliteDB_open();
    char* a=Login(username,password);
    sqliteDB_close();
    if(DEBUG){
        a="successed";
    }
    if(strcmp(a,"successed")==0){
        printf("<script>window.location.href=\"/map.html\"</script>\n");
    }
    else{
        printf("error");
    }
    return 0;
}
