#include<stdio.h>
#include<stdlib.h>
#include"tools.h"
#include<string.h>
#include"/arm2410cl/Trolltech/qt-embedded-4.4.0/myqt/YJSQLite.h"
#define DEBUG 0
void data_to_str(char *data_str){
    int tip;
	 int i;
    for(i=0;i<strlen(data_str);i++){
        if(data_str[i]=='.'){
            tip=i;
            break;
        }
    }
    tip-=2;
    double data=0,m=0;
    for(i=0;i<tip;i++){
        data*=10;
        data+=data_str[i]-'0';
    }
    for(i=tip;i<tip+2;i++){
        m*=10;
        m+=data_str[i]-'0';
    }
    
    int tmp=10;
    for(i=tip+1;i<tip+7;i++){
        m+=(data_str[i]-'0')/tmp;
        tmp*=10;
    }
    data+=m/60.0;

    ///122.09395837,37.52878708
    //12204.671390,3731.523980
    memset(data_str,'\0',sizeof(char)*50);
    sprintf(data_str,"%.3f",data);
}
int main(){
    puts("Content-type: text/plain\n\n");
    char *data=getenv("QUERY_STRING");
    char* operate=analyze(data,"operate");
    if(strcmp(operate,"refresh")==0){
        char** res;
        sqliteDB_open();
        res=sqliteDB_opt_select_newpath_src();
        sqliteDB_close();
        if(DEBUG){
            res[0]="name";
            res[1]="12204.671390";
            res[2]="3731.523980";
        };
        char langitude_str[50];
        strcpy(langitude_str,res[1]);
        data_to_str(langitude_str);
        char latitude_str[50];
        strcpy(latitude_str,res[2]);
        data_to_str(latitude_str);
        printf("%s,%s,%s,%s,%s",langitude_str,latitude_str,res[0],res[1],res[2]);
    }
    else{
        printf("error");
    }
    return 0;
}
