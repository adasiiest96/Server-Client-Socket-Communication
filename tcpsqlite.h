#ifndef tcpsqlite_h
#define tcpsqlite_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

char *zErrMsg = 0; //array for holding error message
int  rc;            //stores status of a query
char *sql;          //stores the sql query

int connectDb(const char *filename,sqlite3 **ppDb){
    rc = sqlite3_open(filename, ppDb);
    if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*ppDb));
      return(-1);
   }else{
      fprintf(stderr, "Opened database successfully\n");
      return 0;
   }
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
int createTable(sqlite3 *db){

    sql = "CREATE TABLE CHAT("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "USERNAME           TEXT    NOT NULL," \
         "MESSAGE        VARCHAR(140)," \
         "STATUS         INT );";
    
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table created successfully\n");
    }
}

int inserTable(sqlite3 *db,int id,char *user){
    
}
#endif