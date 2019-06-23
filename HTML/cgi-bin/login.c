#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char* getcgidata(FILE* fp,char* requestmethod){
    char *input;
    int len;
    int size=1024;
    int i=0;
    if(!strcmp(requestmethod,"GET")){
        input=getenv("QUERY_STRING");
        return input;
    }
    else if(!strcmp(requestmethod,"POST")){
        len=atio(getenv("CONTENT_LENGTH"));
        input=(char*)malloc(sizeof(char)*(size+1));
        if(len==0){
            input[0]='\0';
            return input;
        }
        while(1){
            input[i]=(char)fgetc(fp);
            if(i==size){
                input[i+1]='\0';
                return input;
            }
            --len;
            if(feof(fp)||(!(len))){
                i++;
                input[i]='\0';
                return input;
            }
            i++;
        }
    }
    return NULL;
}
int main(){
    char *req_method=getenv("REQUEST_METHOD");
    char *input=getcgidata(stdin,req_method);

}