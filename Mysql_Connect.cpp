#include "Mysql_Connect.h"

Mysql_Connect::Mysql_Connect(const string& host, const string& user, const string& password, const string& database, int port)
    : host_(host), user_(user), password_(password), database_(database), port_(port), connection_(nullptr) {
}

Mysql_Connect::~Mysql_Connect() {
    Close();
}

bool Mysql_Connect::Connect() 
{
    connection_ = mysql_init(nullptr);

    if (connection_)
    {
        if (mysql_options(connection_, MYSQL_SET_CHARSET_NAME, "gbk") == 0)
        {
            if (mysql_real_connect(connection_, host_.c_str(), user_.c_str(), password_.c_str(), database_.c_str(), port_, nullptr, 0))
            {
                cout << "已连接到MySQL数据库" << endl;
                return true;
            }
            else
            {
                throw runtime_error("连接到MySQL时发生错误：" + string(mysql_error(connection_)));
            }
        }
        else 
        {
            throw runtime_error("设置MySQL字符集时发生错误");
        }
    }
    else 
    {
        throw runtime_error("初始化MySQL连接时发生错误。");
    }
    return false;
}

void Mysql_Connect::Close() 
{
    if (connection_)
    {
        mysql_close(connection_);
        cout << endl << "已断开与MySQL数据库的连接" << endl;
        connection_ = nullptr;
    }
}

bool Mysql_Connect::CreateRecord(const string& tableName, const string& columnName1, const string& columnName2, const string& columnName3, const string& value1, const string& value2, const string& value3)
{
    string query = "INSERT INTO " + tableName 
        + " (" + columnName1 + "," + columnName2 + "," + columnName3 + ") VALUES ('" + value1 + "','" + value2 + "','" + value3 + "')";
    return ExecuteQuery(query);
}

bool Mysql_Connect::CreateOrder(const string& tableName, const string& value1, const string& value2, const string& value3, const string& value4, const string& value5, const string& value6)
{
    string query = "INSERT INTO " + tableName 
        + " VALUES ('" + value1 + "','" + value2 + "','" + value3 + "','" + value4 + "','" + value5 + "','" + value6 + "')";
    return ExecuteQuery(query);
}

bool Mysql_Connect::UpdateRecord(const string& tableName, const string& columnName, const string& value, const string& condition)
{
    string query = "UPDATE " + tableName + " SET " + columnName + " = '" + value + "' WHERE " + condition;
    return ExecuteQuery(query);
}

bool Mysql_Connect::DeleteRecord(const string& tableName, const string& condition)
{
    string query = "DELETE FROM " + tableName + " WHERE " + condition;
    return ExecuteQuery(query);
}

bool Mysql_Connect::ExecuteQuery(const string& query)
{
    if (connection_)
    {
        if (mysql_query(connection_, query.c_str()) == 0)
        {
            //cout << "执行成功" << endl;
            return true;
        }
        else
        {
            cerr << "执行失败: " << mysql_error(connection_) << endl;
        }
    }
    return false;
}

MYSQL_RES* Mysql_Connect::GetQueryResult(const string& query)
{
    if (connection_)
    {
        if (mysql_query(connection_, query.c_str()) == 0)
        {
            return mysql_store_result(connection_);
        }
        else
        {
            cerr << "查询失败: " << mysql_error(connection_) << endl;
        }
    }
    return nullptr;
}