#ifndef YJSQLite_H
#define YJSQLite_H
#include <stdio.h>
#include "./sqlite/sqlite3.h"
#include <stdlib.h>
#include<string.h>

sqlite3 *db;//全局的数据连接

/******在用户还没有创建table时可用该函数创建一个table****/
int sqliteDB_create_oldtable(){
 
	char* zErrMsg=NULL;
 	char sql[256]="CREATE TABLE olduser(name varchar(40) primary key,sex varchar(40) not null,age varchar(40) not null,address varchar(200) not null,state varchar(150) not null);";
 
	int nret=sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);

 	if(nret!=SQLITE_OK){ 
 		printf("%s\n",sqlite3_errmsg(db));
  	return 1;//失败
 	}
 	else

  	return 0;//成功
}

/******在用户还没有创建table时可用该函数创建一个table****/
int sqliteDB_create_pathtable(){
 
	char* zErrMsg=NULL;
 	char sql[256]="CREATE TABLE path(name varchar(40) primary key,jidu varchar(40) not null,weidu varchar(40) not null,high varchar(40) not null,speed varchar(40) not null,timer varchar(100) not null);";
 
	int nret=sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);

 	if(nret!=SQLITE_OK){ 
 		printf("%s\n",sqlite3_errmsg(db));
  	return 1;//失败
 	}
 	else

  	return 0;//成功
}

/******在用户还没有创建table时可用该函数创建一个table****/
int sqliteDB_create_usertable(){
 
	char* zErrMsg=NULL;
 	char sql[256]="CREATE TABLE user(name varchar(40) primary key,sex varchar(40) not null,age varchar(40) not null,phone varchar(100) not null,address varchar(200) not null,relation varchar(150) not null,password varchar(40) not null);";
 
	int nret=sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);

 	if(nret!=SQLITE_OK){ 
 		printf("%s\n",sqlite3_errmsg(db));
  	return 1;//失败
 	}
 	else

  	return 0;//成功
}

/******初始化数据库table时预插入两条数据****/
int sqliteDB_insert_records()
{
 	char* zErrMsg=NULL;
 	char sql1[256]="INSERT INTO olduser VALUES('Andy','man','78','erth','illness');";
 	char sql2[256]="INSERT INTO user VALUES('june','man','48','433443','erth','son','0000');";
	char sql3[256]="INSERT INTO user VALUES('marry','woman','45','433444','erth','wife of son','0000');";

 	int nret=sqlite3_exec(db,sql1,NULL,NULL,&zErrMsg);

 	nret=sqlite3_exec(db,sql2,NULL,NULL,&zErrMsg);
	nret=sqlite3_exec(db,sql3,NULL,NULL,&zErrMsg);

 	if(nret!=SQLITE_OK){
 	 	printf("%s\n",sqlite3_errmsg(db));
  		return 1;//失败
 	}
 	else
  	return 0;//成功
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName);

/*** *建立与数据库的连接* **/
int sqliteDB_open(){

	int rc;//操作标志
	printf("开始连接数据库s\n");
	rc = sqlite3_open("YJDB.db", &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	printf("\nOpen sucess!");

	if(!sqliteDB_create_usertable())
		printf("\ntable exist");	
	if(!sqliteDB_create_pathtable())
		printf("\ntable exist");	
	if(!sqliteDB_create_oldtable())
		printf("\ntable exist");

	sqliteDB_insert_records();//初始化数据
	return 0;//成功
}

/**** 关闭与数据库的连接 **/
int sqliteDB_close(){
	if(db != 0)  
		sqlite3_close(db);
	return 0;//成功
}

/**** 添加一条记录到已知或未知数据库表**/
int sqliteDB_opt_addolduser(char *name,char *sex,char *age,char *address,char *state){
	int rc;
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="insert into merchandise values('";

	char tem_sql0[5] = "','";
   char tem_sql1[5] = "'";
   char tem_sql2[5] = ");";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,sex);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,age);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,address);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,state);
	sql = strcat(sql,tem_sql1);

	sql = strcat(sql,tem_sql2);

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 1;//失败
	}
	 return 0;//成功
}
/**** 添加一条记录到已知或未知数据库表**/
int sqliteDB_opt_adduser(char *name,char *sex,char *age,char *phone,char *address,char *relation,char *password){
	int rc;
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="insert into user values('";

	char tem_sql0[5] = "','";
   char tem_sql1[5] = "'";
   char tem_sql2[5] = ");";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,sex);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,age);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,phone);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,address);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,relation);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,password);
	sql = strcat(sql,tem_sql1);

	sql = strcat(sql,tem_sql2);

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 1;//失败
	}
	return 0;//成功
}
/**** 添加一条记录到已知或未知数据库表**/
int sqliteDB_opt_addpath(char *name,char *jidu,char *weidu,char *high,char *speed,char *timer){
	int rc;
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="insert into path values('";

	char tem_sql0[5] = "','";
   char tem_sql1[5] = "'";
   char tem_sql2[5] = ");";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,jidu);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,weidu);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,high);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,speed);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,timer);
	sql = strcat(sql,tem_sql1);

	sql = strcat(sql,tem_sql2);

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 1;//失败
	}
	return 0;//成功
}


/**** 删除表中的一条记录* @param name*/
int sqliteDB_opt_deleteolduser(char *name){
	int rc;
	char n[4];
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="delete from olduser where name = '";//
	char tem_sql0[5] = "'";
	char tem_sql1[5] = ";";

	//删除之前查询该条记录，如存在则显示该记录，并询问是否真的要删除
	                        //如不存在则推出本次操作

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 1;//失败
	}
	return 0;//成功
}
/**** 删除表中的一条记录* @param name*/
int sqliteDB_opt_deleteuser(char *name){
	int rc;
	char n[4];
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="delete from user where name = '";//
	char tem_sql0[5] = "'";
	char tem_sql1[5] = ";";

	//删除之前查询该条记录，如存在则显示该记录，并询问是否真的要删除
	                        //如不存在则推出本次操作

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 1;//失败
	}
	return 0;//成功
}
/**** 删除表中的一条记录* @param name*/
int sqliteDB_opt_deletepath(char *name){
	int rc;
	char n[4];
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="delete from path where name = '";//
	char tem_sql0[256] = "'";
	char tem_sql1[256] = ";";

	//删除之前查询该条记录，如存在则显示该记录，并询问是否真的要删除
	                        //如不存在则推出本次操作

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return 1;//失败
	}
	return 0;//成功
}


/*******************************************************
******************************************************/
/**
*
* 修改数据库表中的记录内容
* //暂不提供修改函数2007-3-21
*/
int sqliteDB_opt_modify();
/**
*
* 用预编译的sql语句减少sql语句的分析时间
* 
* 只举例 查询语句
* @2007-3-22
* 查询语句
*/

char *sqliteDB_opt_select_allolduser(){

	sqlite3_stmt* stmt=NULL;

	char dest[1000]={0,};//结果
	char s[]="no result";

 	char* zErrMsg=NULL;
 	
 	int nret=sqlite3_prepare(db,"SELECT * FROM olduser;",strlen("SELECT * FROM olduser;"),&stmt,(const char**)(&zErrMsg));
 	
	if(nret!=SQLITE_OK)
  		return s;	printf("\n\tname\t\tsex\t\tage\t\taddress\t\tstate\n");//测试数据库写对没有
 	printf("\t------------------------------------------------------------\n");//测试
 	while(1){ 
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;
  		char *name=( char *)sqlite3_column_text(stmt,0);
		char *sex=( char *)sqlite3_column_text(stmt,1);
  		char *age=( char *)sqlite3_column_text(stmt,2);
		char *address=( char *)sqlite3_column_text(stmt,3);
		char *state=( char *)sqlite3_column_text(stmt,4);
		char *spl="#";
		printf("\t%s\t\t%s\t\t%d\t\t%s\t\t%s\n",name,sex,age,address,state);//测试
  		/*char name[50]="sqlite3_column_text(stmt,0)";
		char sex[50]="sqlite3_column_text(stmt,1)";
  		char age[50]="sqlite3_column_text(stmt,2)";
		char address[200]="sqlite3_column_text(stmt,3)";
		char state[200]="sqlite3_column_text(stmt,4)";*/

		strcat(dest,name);
		strcat(dest,spl);
		strcat(dest,sex);
		strcat(dest,spl);
		strcat(dest,age);
		strcat(dest,spl);
		strcat(dest,address);
		strcat(dest,spl);
		strcat(dest,state);
		strcat(dest,spl);
 	}

 	sqlite3_finalize(stmt);
	printf("%s\n",dest);//测试
 	return dest;//返回结果
}
char *sqliteDB_opt_select_alluser(){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;

	char dest[1000]={0,};//结果
	char s[]="no result";
 	int nret=sqlite3_prepare(db,"SELECT * FROM user;",strlen("SELECT * FROM user;"),&stmt,(const char**)(&zErrMsg));
 	
	if(nret!=SQLITE_OK)
  		return s;
 	printf("\n\tname\t\tsex\t\tage\t\tphone\t\taddress\t\trelation\n");//测试
 	printf("\t------------------------------------------------------------\n");
 	while(1){ 
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;
  		char *name=( char *)sqlite3_column_text(stmt,0);
		char *sex=( char *)sqlite3_column_text(stmt,1);
  		char *age=( char *)sqlite3_column_text(stmt,2);
		char *phone=( char *)sqlite3_column_text(stmt,3);
		char *address=( char *)sqlite3_column_text(stmt,4);
		char *relation=( char *)sqlite3_column_text(stmt,5);
		char *spl="#";
  		/*char name[50]="sqlite3_column_text(stmt,0)";
		char sex[50]="sqlite3_column_text(stmt,1)";
  		char age[50]="sqlite3_column_text(stmt,2)";
		char phone[50]="sqlite3_column_text(stmt,3)";
		char address[200]="sqlite3_column_text(stmt,4)";
		char relation[50]="sqlite3_column_text(stmt,5)";*/
		printf("\t%s\t\t%s\t\t%d\t\t%s\t\t%s\t\t%s\n",name,sex,age,phone,address,relation);//测试

		strcat(dest,name);
		strcat(dest,spl);
		strcat(dest,sex);
		strcat(dest,spl);
		strcat(dest,age);
		strcat(dest,spl);
		strcat(dest,phone);
		strcat(dest,spl);
		strcat(dest,address);
		strcat(dest,spl);
		strcat(dest,relation);
		strcat(dest,spl);
  }

 	sqlite3_finalize(stmt);
	printf("%s\n",dest);//测试
 	return dest;
}
char *sqliteDB_opt_select_allpath(){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;

	char dest[1000]={0,};//结果
	char s[]="no result";

 	int nret=sqlite3_prepare(db,"SELECT * FROM path;",strlen("SELECT * FROM path;"),&stmt,(const char**)(&zErrMsg));
 	
	if(nret!=SQLITE_OK)
  		return s;
 	while(1){ 
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;
  		char *name=( char *)sqlite3_column_text(stmt,0);
		char *jidu=( char *)sqlite3_column_text(stmt,1);
		char *weidu=( char *)sqlite3_column_text(stmt,2);
		char *high=( char *)sqlite3_column_text(stmt,3);
		char *speed=( char *)sqlite3_column_text(stmt,4);
		char *timer=( char *)sqlite3_column_text(stmt,5);
		char *spl="#";
  		/*char name[50]="sqlite3_column_text(stmt,0)";
		char jidu[50]="sqlite3_column_text(stmt,1)";
		char weidu[50]="sqlite3_column_text(stmt,2)";
		char high[50]="sqlite3_column_text(stmt,3)";
		char speed[50]="sqlite3_column_text(stmt,4)";
		char timer[50]="sqlite3_column_text(stmt,5)";*/


		strcat(dest,name);
		strcat(dest,spl);
		strcat(dest,jidu);
		strcat(dest,spl);
		strcat(dest,weidu);
		strcat(dest,spl);
		strcat(dest,high);
		strcat(dest,spl);
		strcat(dest,speed);
		strcat(dest,spl);
		strcat(dest,timer);
		strcat(dest,spl);
 	}

 	sqlite3_finalize(stmt);
 	return dest;
}

/*** 查询符合查询条件的记录* @param name*/
char *sqliteDB_opt_selectolduser(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;

	char dest[1000]={0,};//结果
	char s[]="no result";

 	int nret=0;
	int rc;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="select * from olduser where name = '";//
	char tem_sql0[5] = "'";
	char tem_sql1[5] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);

	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	if(nret!=SQLITE_OK)
		return s;
 	while(1){ 
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
   			break;
  		char *_name=( char *)sqlite3_column_text(stmt,0);
		char *_sex=( char *)sqlite3_column_text(stmt,1);
  		char *_age=( char *)sqlite3_column_text(stmt,2);
		char *_address=( char *)sqlite3_column_text(stmt,3);
		char *_state=( char *)sqlite3_column_text(stmt,4);
		char *spl="#";
  		/*char _name[50]="sqlite3_column_text(stmt,0)";
		char _sex[50]="sqlite3_column_text(stmt,1)";
  		char _age[50]="sqlite3_column_text(stmt,2)";
		char _address[200]="sqlite3_column_text(stmt,3)";
		char _state[200]="sqlite3_column_text(stmt,4)";*/


		strcat(dest,_name);
		strcat(dest,spl);
		strcat(dest,_sex);
		strcat(dest,spl);
		strcat(dest,_age);
		strcat(dest,spl);
		strcat(dest,_address);
		strcat(dest,spl);
		strcat(dest,_state);
		strcat(dest,spl);
 	}
	
	sqlite3_finalize(stmt);
	return dest;
}
char *sqliteDB_opt_selectuser(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
	
	char dest[1000]={0,};//结果
	char s[]="no result";

 	int nret=0;
	int rc;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="select * from user where name = '";//
	char tem_sql0[5] = "'";
	char tem_sql1[5] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	if(nret!=SQLITE_OK)
		return s;
 	
 	while(1){ 
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
   			break;
  		char *_name=( char *)sqlite3_column_text(stmt,0);
		char *_sex=( char *)sqlite3_column_text(stmt,1);
  		char *_age=( char *)sqlite3_column_text(stmt,2);
		char *_phone=( char *)sqlite3_column_text(stmt,3);
		char *_address=( char *)sqlite3_column_text(stmt,4);
		char *_relation=( char *)sqlite3_column_text(stmt,5);
		char *spl="#";
		/*char _name[50]="sqlite3_column_text(stmt,0)";
		char _sex[50]="sqlite3_column_text(stmt,1)";
  		char _age[50]="sqlite3_column_text(stmt,2)";
		char _phone[50]="sqlite3_column_text(stmt,3)";
		char _address[200]="sqlite3_column_text(stmt,4)";
		char _relation[50]="sqlite3_column_text(stmt,5)";*/

		strcat(dest,_name);
		strcat(dest,spl);
		strcat(dest,_sex);
		strcat(dest,spl);
		strcat(dest,_age);
		strcat(dest,spl);
		strcat(dest,_phone);
		strcat(dest,spl);
		strcat(dest,_address);
		strcat(dest,spl);
		strcat(dest,_relation);
		strcat(dest,spl);
 	}
	
	sqlite3_finalize(stmt);
	return dest;
}
char *sqliteDB_opt_selectpath(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;

	char dest[1000]={0,};//结果
	char s[]="no result";

 	int nret=0;
	int rc;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="select * from path where name = '";//
	char tem_sql0[5] = "'";
	char tem_sql1[5] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);

	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	if(nret!=SQLITE_OK)
		return s;
 	while(1){ 
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
   			break;
 		 char *_name=( char *)sqlite3_column_text(stmt,0);
		 char *_jidu=( char *)sqlite3_column_text(stmt,1);
		 char *_weidu=( char *)sqlite3_column_text(stmt,2);
		 char *_high=( char *)sqlite3_column_text(stmt,3);
		 char *_speed=( char *)sqlite3_column_text(stmt,4);
		 char *_timer=( char *)sqlite3_column_text(stmt,5);
		 char *spl="#";
		/*char _name[50]="sqlite3_column_text(stmt,0)";
		char _jidu[50]="sqlite3_column_text(stmt,1)";
		char _weidu[50]="sqlite3_column_text(stmt,2)";
		char _high[50]="sqlite3_column_text(stmt,3)";
		char _speed[50]="sqlite3_column_text(stmt,4)";
		char _timer[50]="sqlite3_column_text(stmt,5)";*/

		strcat(dest,_name);
		strcat(dest,spl);
		strcat(dest,_jidu);
		strcat(dest,spl);
		strcat(dest,_weidu);
		strcat(dest,spl);
		strcat(dest,_high);
		strcat(dest,spl);
		strcat(dest,_speed);
		strcat(dest,spl);
		strcat(dest,_timer);
		strcat(dest,spl);
  		
 	}
	
	sqlite3_finalize(stmt);
	
	return dest;
}

/********内部调用函数****/
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  	int i;
  	for(i=0; i<argc; i++){
    		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  	}

  	printf("\n");
  	return 0;
}


/******内部调用函数**功能判断所查询的记录是否存在* 依据：name**/
int sqliteDB_existolduser(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	int nret=0;
	int rc;

	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="select * from olduser where name = '";//
	char tem_sql0[5] = "'";
	char tem_sql1[5] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);

	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	
	if(nret!=SQLITE_OK)
		return 1;//失败
	nret=sqlite3_step(stmt);
	if(nret!=SQLITE_ROW){
		
		return 1;//失败
	}
	
	sqlite3_finalize(stmt);
	return 0;//成功
}
int sqliteDB_existuser(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	
 	int nret=0;
	int rc;

	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="select * from user where name = '";//
	char tem_sql0[5] = "'";
	char tem_sql1[5] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);

	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	
	if(nret!=SQLITE_OK)
		return 1;//失败
	nret=sqlite3_step(stmt);
	if(nret!=SQLITE_ROW){
		
		return 1;//失败
	}
	
	sqlite3_finalize(stmt);
	return 0;//成功
}
int sqliteDB_existpath(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	
 	int nret=0;
	int rc;

	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="select * from path where name = '";//
	char tem_sql0[256] = "'";
	char tem_sql1[256] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);

	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	
	if(nret!=SQLITE_OK)
		return 1;//失败
	nret=sqlite3_step(stmt);
	if(nret!=SQLITE_ROW){
		
		return 1;//失败
	}
	
	sqlite3_finalize(stmt);
	return 0;//成功
}

double StringtoDouble(char *str){//将char*转换为double类型
	double f;
	f=atof(str);
	return f;
}

char *DoubletoString(double f){//将double转换为char*类型
	char str[50];
	sprintf(str,"%f",f);
	return str;//返回数组首地址
}

#endif


/*extern int sqliteDB_open();

extern int sqliteDB_close();

extern int sqliteDB_opt_addolduser(char *name,char *sex,int age,char *address,char *state);

extern int sqliteDB_opt_adduser(char *name,char *sex,int age,char *phone,char *address,char *relation,char *password);

extern int sqliteDB_opt_addpath(char *name,double jidu,double weidu,double high,double speed,char *timer);

extern int sqliteDB_opt_deleteolduser(char *name);

extern int sqliteDB_opt_deleteuser(char *name);

extern int sqliteDB_opt_deletepath(char *name);

extern int sqliteDB_opt_modify();

extern char sqliteDB_opt_select_allolduser();

extern char sqliteDB_opt_select_alluser();

extern char sqliteDB_opt_select_allpath();

extern char sqliteDB_opt_selectolduser(char *name);

extern char sqliteDB_opt_selectuser(char *name);

extern char sqliteDB_opt_selectpath(char *name);

extern int sqliteDB_create_oldtable();

extern int sqliteDB_create_pathtable();

extern int sqliteDB_create_usertable();

extern int sqliteDB_insert_records();//初始化里面加的值

extern int sqliteDB_existolduser(char *name);

extern int sqliteDB_existuser(char *name);

extern int sqliteDB_existpath(char *name);
*/




