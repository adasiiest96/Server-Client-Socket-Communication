#include <stdio.h>
#include <stdlib.h>
#include "tcpsqlite.h"
#include <sqlite3.h> 

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   char *sql;

   /* Open database */
   /*rc = sqlite3_open("test.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }else{
      fprintf(stdout, "Opened database successfully\n");
   }*/
   connectDb("test.db",&db);


   
   /* Execute SQL statement */
   createTable(db);
   sqlite3_close(db);
   return 0;
}