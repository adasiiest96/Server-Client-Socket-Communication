#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
int main(){
    string name;
    string deli =", " ;
    string finish = ")";
    printf("enter a name?");
    cin >> name;
    int id = 42;
    string mesg = "NONE";
    int status = 0;
    string sql = "Insert into COMPANY (ID,NAME,AGE,ADDRESS,SALARY) VALUES (";
    name  = "'" + name + "'";
    sql  = sql + to_string(id) +deli +  name + mesg + deli + to_string(status) + finish;

    cout << sql<<endl;

    return 0;
}