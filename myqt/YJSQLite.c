#include "YJSQLite.h"

sqlite3 *db;//全局的数据连接

//用户第一次打开数据库时应创建对应的table并添加适当的数据记录

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

	return 1;
}

/**** 关闭与数据库的连接 **/
int sqliteDB_close(){
	if(db != 0)  
		sqlite3_close(db);
}

/**** 添加一条记录到已知或未知数据库表**/
int sqliteDB_opt_addolduser(char *name,char *sex,int age,char *address,char *state){
	int rc;
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="insert into olduser values('";

// by sprife for mem out

	char tem_sql0[5] = "','";
      	char tem_sql1[5] = "'";
      	char tem_sql2[5] = ");";
	char tem_age[20];

	sprintf(tem_age, " %d" , age);//将int数据转换为字符串

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,sex);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,tem_age);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,address);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,state);
	sql = strcat(sql,tem_sql1);

	sql = strcat(sql,tem_sql2);

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//	printf("\n rc = %d",rc);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}
/**** 添加一条记录到已知或未知数据库表**/
int sqliteDB_opt_adduser(char *name,char *sex,int age,char *phone,char *address,char *relation,char *password){
	int rc;
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="insert into user values('";

// by sprife for mem out

	char tem_sql0[5] = "','";
      	char tem_sql1[5] = "'";
      	char tem_sql2[5] = ");";
	char tem_age[20];

	sprintf(tem_age, " %d" , age);//将int数据转换为字符串

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,sex);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,tem_age);
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
//	printf("\n rc = %d",rc);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}
/**** 添加一条记录到已知或未知数据库表**/
int sqliteDB_opt_addpath(char *name,double jidu,double weidu,double high,double speed,char *timer){
	int rc;
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="insert into path values('";

// by sprife for mem out

	char tem_sql0[5] = "','";
   char tem_sql1[5] = "'";
   char tem_sql2[5] = ");";
	char tem_jidu[20];
	char tem_weidu[20];
	char tem_high[20];
	char tem_speed[20];

	sprintf(tem_jidu, " %f" , jidu);//将int数据转换为字符串
	sprintf(tem_weidu, " %f" , weidu);//将int数据转换为字符串
	sprintf(tem_high, " %f" , high);//将int数据转换为字符串
	sprintf(tem_speed, " %f" , speed);//将int数据转换为字符串

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,tem_jidu);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,tem_weidu);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,tem_high);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,tem_speed);
	sql = strcat(sql,tem_sql0);

	sql = strcat(sql,timer);
	sql = strcat(sql,tem_sql1);

	sql = strcat(sql,tem_sql2);

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//	printf("\n rc = %d",rc);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}


/**** 删除表中的一条记录* @param name*/
int sqliteDB_opt_deleteolduser(char *name){
	int rc;
	char n[4];
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="delete from olduser where name = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	//删除之前查询该条记录，如存在则显示该记录，并询问是否真的要删除
	                        //如不存在则推出本次操作

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//	printf("\n rc = %d",rc);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}
/**** 删除表中的一条记录* @param name*/
int sqliteDB_opt_deleteuser(char *name){
	int rc;
	char n[4];
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="delete from user where name = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	//删除之前查询该条记录，如存在则显示该记录，并询问是否真的要删除
	                        //如不存在则推出本次操作

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//	printf("\n rc = %d",rc);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}
/**** 删除表中的一条记录* @param name*/
int sqliteDB_opt_deletepath(char *name){
	int rc;
	char n[4];
	char *zErrMsg = 0;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="delete from path where name = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	//删除之前查询该条记录，如存在则显示该记录，并询问是否真的要删除
	                        //如不存在则推出本次操作

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
//	printf("\n rc = %d",rc);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
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

int sqliteDB_opt_select_allolduser(){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	char *name,*sex,*address,*state;
 	int age=0;
 	int nret=sqlite3_prepare(db,"SELECT * FROM olduser;",strlen("SELECT * FROM olduser;"),&stmt,(const char**)(&zErrMsg));
 	
	if(nret!=SQLITE_OK)
  		return false;
 	printf("\n\tname\t\tsex\t\tage\t\taddress\t\tstate\n");
 	printf("\t------------------------------------------------------------\n");
 	while(1){ 
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;
  		name=sqlite3_column_text(stmt,0);
		sex=sqlite3_column_text(stmt,1);
  		age=sqlite3_column_int(stmt,2);
		address=sqlite3_column_text(stmt,3);
		state=sqlite3_column_text(stmt,4);
  		printf("\t%s\t\t%s\t\t%d\t\t%s\t\t%s\n",name,sex,age,address,state);
 	}

 	sqlite3_finalize(stmt);
 	printf("\n");
 	return true;
}
char sqliteDB_opt_select_alluser(){

	sqlite3_stmt* stmt=NULL;
 	char zErrMsg=NULL;
 	char name,sex,address,phone,relation;
 	int age=0;
 	int nret=sqlite3_prepare(db,"SELECT * FROM user;",strlen("SELECT * FROM user;"),&stmt,(const char**)(zErrMsg));
 	char str1;
	if(nret!=SQLITE_OK)
  		return false;
 	while(1){ 
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;
  		name=sqlite3_column_text(stmt,0);
		sex=sqlite3_column_text(stmt,1);
  		age=sqlite3_column_int(stmt,2);
		phone=sqlite3_column_text(stmt,3);
		address=sqlite3_column_text(stmt,4);
		relation=sqlite3_column_text(stmt,5);
		str1=name;
 	}

 	sqlite3_finalize(stmt);
 	return str1;
}
int sqliteDB_opt_select_allpath(){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	char *name,*timer;
 	double jidu=0.0,weidu=0.0;
	double high=0.0,speed=0.0;
 	int nret=sqlite3_prepare(db,"SELECT * FROM path;",strlen("SELECT * FROM path;"),&stmt,(const char**)(&zErrMsg));
 	
	if(nret!=SQLITE_OK)
  		return false;
 	printf("\n\tname\t\tjidu\t\tweidu\t\thigh\t\tspeed\t\ttimer\n");
 	printf("\t------------------------------------------------------------\n");
 	while(1){ 
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
  	 		break;
  		name=sqlite3_column_text(stmt,0);
		jidu=sqlite3_column_double(stmt,1);
		weidu=sqlite3_column_double(stmt,2);
		high=sqlite3_column_double(stmt,3);
		speed=sqlite3_column_double(stmt,4);
		timer=sqlite3_column_text(stmt,5);
  		printf("\t%s\t\t%f\t\t%f\t\t%f\t\t%f\t\t%s\n",name,jidu,weidu,high,speed,timer);
 	}

 	sqlite3_finalize(stmt);
 	printf("\n");
 	return true;
}

/*** 查询符合查询条件的记录* @param name*/
int sqliteDB_opt_selectolduser(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
	char *_name,*_sex,*_address,*_state;
 	int age=0;
 	int nret=0;
	int rc;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="select * from olduser where name = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	if(nret!=SQLITE_OK)
		return false;
 	printf("\n\tname\t\tsex\t\tage\t\taddress\t\tstate\n");
 	printf("\t------------------------------------------------------------\n");
 	while(1){ 
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
   			break;
  		_name=sqlite3_column_text(stmt,0);
		_sex=sqlite3_column_text(stmt,1);
  		age=sqlite3_column_int(stmt,2);
		_address=sqlite3_column_text(stmt,3);
		_state=sqlite3_column_text(stmt,4);
  		printf("\t%s\t\t%s\t\t%d\t\t%s\t\t%s\n",_name,_sex,age,_address,_state);
 	}
	
	sqlite3_finalize(stmt);
	printf("\n");
	return true;
}
int sqliteDB_opt_selectuser(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
	char *_name,*_sex,*_address,*_phone,*_relation;
 	int age=0;
 	int nret=0;
	int rc;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="select * from user where name = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	if(nret!=SQLITE_OK)
		return false;
 	printf("\n\tname\t\tsex\t\tage\t\tphone\t\taddress\t\trelation\n");
 	printf("\t------------------------------------------------------------\n");
 	while(1){ 
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
   			break;
  		_name=sqlite3_column_text(stmt,0);
		_sex=sqlite3_column_text(stmt,1);
  		age=sqlite3_column_int(stmt,2);
		_phone=sqlite3_column_text(stmt,3);
		_address=sqlite3_column_text(stmt,4);
		_relation=sqlite3_column_text(stmt,5);
  		printf("\t%s\t\t%s\t\t%d\t\t%s\t\t%s\t\t%s\n",_name,_sex,age,_phone,_address,_relation);
 	}
	
	sqlite3_finalize(stmt);
	printf("\n");
	return true;
}
int sqliteDB_opt_selectpath(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
	char *_name,*_timer;
 	double jidu=0.0,weidu=0.0,high=0.0,speed=0.0;
 	int nret=0;
	int rc;
	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="select * from path where name = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);
//	printf("\n###############################");
//	printf("\n%s",sql);
//	printf("\n###############################");
	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	if(nret!=SQLITE_OK)
		return false;
 	printf("\n\tname\t\tjidu\t\tweidu\t\thigh\t\tspeed\t\ttimer\n");
 	printf("\t------------------------------------------------------------\n");
 	while(1){ 
  		nret=sqlite3_step(stmt);
  		if(nret!=SQLITE_ROW)
   			break;
 		_name=sqlite3_column_text(stmt,0);
		jidu=sqlite3_column_double(stmt,1);
		weidu=sqlite3_column_double(stmt,2);
		high=sqlite3_column_double(stmt,3);
		speed=sqlite3_column_double(stmt,4);
		_timer=sqlite3_column_text(stmt,5);
  		printf("\t%s\t\t%f\t\t%f\t\t%f\t\t%f\t\t%s\n",_name,jidu,weidu,high,speed,_timer);
 	}
	
	sqlite3_finalize(stmt);
	printf("\n");
	return true;
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

/******在用户还没有创建table时可用该函数创建一个table****/
int sqliteDB_create_oldtable(){
 
	char* zErrMsg=NULL;
 	char sql[256]="CREATE TABLE olduser(name varchar(40) primary key,sex varchar(40) not null,age int not null,address varchar(200) not null,state varchar(150) not null);";
 
	int nret=sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);

 	if(nret!=SQLITE_OK){ 
 		printf("%s\n",sqlite3_errmsg(db));
  	return false;
 	}
 	else

  	return true;
}

/******在用户还没有创建table时可用该函数创建一个table****/
int sqliteDB_create_pathtable(){
 
	char* zErrMsg=NULL;
 	char sql[256]="CREATE TABLE path(name varchar(40) primary key,jidu double not null,weidu double not null,high double not null,speed double not null,timer varchar(100) not null);";
 
	int nret=sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);

 	if(nret!=SQLITE_OK){ 
 		printf("%s\n",sqlite3_errmsg(db));
  	return false;
 	}
 	else

  	return true;
}

/******在用户还没有创建table时可用该函数创建一个table****/
int sqliteDB_create_usertable(){
 
	char* zErrMsg=NULL;
 	char sql[256]="CREATE TABLE user(name varchar(40) primary key,sex varchar(40) not null,age int not null,phone varchar(100) not null,address varchar(200) not null,relation varchar(150) not null,password varchar(40) not null);";
 
	int nret=sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);

 	if(nret!=SQLITE_OK){ 
 		printf("%s\n",sqlite3_errmsg(db));
  	return false;
 	}
 	else

  	return true;
}

/******初始化数据库table时预插入两条数据****/
int sqliteDB_insert_records()
{
 	char* zErrMsg=NULL;
 	char sql1[256]="INSERT INTO olduser VALUES('Andy','man',78,'erth','illness');";
 	char sql2[256]="INSERT INTO user VALUES('june','man',48,'433443','erth','son','0000');";
	char sql3[256]="INSERT INTO user VALUES('marry','woman',45,'433444','erth','wife of son','0000');";

 	int nret=sqlite3_exec(db,sql1,NULL,NULL,&zErrMsg);

 	nret=sqlite3_exec(db,sql2,NULL,NULL,&zErrMsg);
	nret=sqlite3_exec(db,sql3,NULL,NULL,&zErrMsg);

 	if(nret!=SQLITE_OK){
 	 	printf("%s\n",sqlite3_errmsg(db));
  		return false;
 	}
 	else
  	return true;
}

/******内部调用函数**功能判断所查询的记录是否存在* 依据：name**/
int sqliteDB_existolduser(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	char *_name,*_sex,*_address,*_state;
 	int age=0;
 	int nret=0;
	int rc;

	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="select * from olduser where name = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);

	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	printf("sql: %s",sql);
	if(nret!=SQLITE_OK)
		return false;
	nret=sqlite3_step(stmt);
	if(nret!=SQLITE_ROW){
		printf("\n this record does not exist!!");
		return false;
	}
	
	sqlite3_finalize(stmt);
	return true;
}
int sqliteDB_existuser(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	char *_name,*_sex,*_address,*_phone,*_relation;
 	int age=0;
 	int nret=0;
	int rc;

	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="select * from user where name = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);

	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	printf("sql: %s",sql);
	if(nret!=SQLITE_OK)
		return false;
	nret=sqlite3_step(stmt);
	if(nret!=SQLITE_ROW){
		printf("\n this record does not exist!!");
		return false;
	}
	
	sqlite3_finalize(stmt);
	return true;
}
int sqliteDB_existpath(char *name){

	sqlite3_stmt* stmt=NULL;
 	char* zErrMsg=NULL;
 	char *_name,*_timer;
 	double jidu=0.0,weidu=0.0,high=0.0,speed=0.0;
 	int nret=0;
	int rc;

	char *sql=0;//动态生成的SQL语句
	char tem_sql[256]="select * from path where name = '";//
	char tem_sql0[3] = "'";
	char tem_sql1[3] = ";";

	sql = strcat(tem_sql,name);
	sql = strcat(sql,tem_sql0);
	sql = strcat(sql,tem_sql1);

	nret=sqlite3_prepare(db,sql,strlen(sql),&stmt,(const char**)(&zErrMsg));
	printf("sql: %s",sql);
	if(nret!=SQLITE_OK)
		return false;
	nret=sqlite3_step(stmt);
	if(nret!=SQLITE_ROW){
		printf("\n this record does not exist!!");
		return false;
	}
	
	sqlite3_finalize(stmt);
	return true;
}
