#include <stdio.h>
#include "./sqlite/sqlite3.h"
#include <stdlib.h>
#include<string.h>
#ifndef false
 #define false 0
#endif
#ifndef true
 #define true 1
#endif

int sqliteDB_open();

int sqliteDB_close();

int sqliteDB_opt_addolduser(char *name,char *sex,int age,char *address,char *state);

int sqliteDB_opt_adduser(char *name,char *sex,int age,char *phone,char *address,char *relation,char *password);

int sqliteDB_opt_addpath(char *name,double jidu,double weidu,double high,double speed,char *timer);

int sqliteDB_opt_deleteolduser(char *name);

int sqliteDB_opt_deleteuser(char *name);

int sqliteDB_opt_deletepath(char *name);

int sqliteDB_opt_modify();

char sqliteDB_opt_select_allolduser();

char sqliteDB_opt_select_alluser();

char sqliteDB_opt_select_allpath();

char sqliteDB_opt_selectolduser(char *name);

char sqliteDB_opt_selectuser(char *name);

char sqliteDB_opt_selectpath(char *name);

int sqliteDB_create_oldtable();

int sqliteDB_create_pathtable();

int sqliteDB_create_usertable();

int sqliteDB_insert_records();//初始化里面加的值

int sqliteDB_existolduser(char *name);

int sqliteDB_existuser(char *name);

int sqliteDB_existpath(char *name);


