#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include"YJSQLite.h"
int main(){
    //printf("Contenttype:text/plain\n\n");
    printf("Content-type: text/html\n\n");
    char *data=getenv("QUERY_STRING");
    if(data==NULL){
        printf("error");
        return 0;
    }
    char* pos=strstr(data,"username");
    int length=0;
    while((char)*(pos+length)!='&'){
        length+=1;
    }
    char username[20];
    for(int i=0;i<=length;i++){
        username[i]='\0';
    }
    strncpy(username,pos,length);
    pos=strstr(data,"password");
    length=0;
    while((char)*(pos+length)!='&'){
        length+=1;
    }
    char password[20];
    for(int i=0;i<=length;i++){
        password[i]='\0';
    }
    strncpy(password,pos,length);
    //sqliteDB_open();
    //char* a=Login(username,password);
    char* a;
    if(strcmp(a,"successed")==0){
        printf("<script>window.location.href=\"/map.html\"</script>\n");
    }
    else{
        printf("error");
    }
    //sqliteDB_close();
    return 0;
}