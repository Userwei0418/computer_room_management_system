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

	//ԤԼ����
	int m_Size;

	//��¼����ԤԼ��Ϣ������
	//keyΪ��¼���� valueΪ��ֵ����Ϣ
	map<int, map<string, string>> m_orderData;
};

