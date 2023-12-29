#pragma once
#include <iostream>
#include <fstream>
#include "globalFile.h"
#include "Mysql_Connect.h"
#include <string>

using namespace std;

//抽象基类
class Identity
{
public:
	//操作菜单 纯虚函数
	virtual void operMenu() = 0;
	//用户名
	string m_name;
	//密码
	string m_Pwd;
};

