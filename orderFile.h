#pragma once
#include <iostream>
using namespace std;
#include "globalFile.h"
#include <fstream>
#include <map>
#include <string>
class orderFile
{
public:
	orderFile();

	void updateOrder();

	//预约条数
	int m_Size;

	//记录所有预约信息的容器
	//key为记录条数 value为键值对信息
	map<int, map<string, string>> m_orderData;
};

