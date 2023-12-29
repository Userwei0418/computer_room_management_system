#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
using namespace std;


class Mysql_Connect
{
public:

  
    Mysql_Connect(const string& host, const string& user, const string& password, const string& database, int port = 3306);

    ~Mysql_Connect();

    bool Connect();

    void Close();

    bool CreateRecord(const string& tableName, const string& columnName1, const string& columnName2, const string& columnName3, const string& value1, const string& value2, const string& value3);

    bool CreateOrder(const string& tableName, const string& value1, const string& value2, const string& value3, const string& value4, const string& value5, const string& value6);

    bool UpdateRecord(const string& tableName, const string& columnName, const string& value, const string& condition);

    bool DeleteRecord(const string& tableName, const string& condition);

    bool ExecuteQuery(const string& query);

    MYSQL_RES* GetQueryResult(const string& query);

private:
    string host_;
    string user_;
    string password_;
    string database_;
    int port_;
    MYSQL* connection_;
};

