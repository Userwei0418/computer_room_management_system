#pragma once
#include <iostream>
#include <fstream>
#include "globalFile.h"
#include "Mysql_Connect.h"
#include <string>

using namespace std;

//�������
class Identity
{
public:
	//�����˵� ���麯��
	virtual void operMenu() = 0;
	//�û���
	string m_name;
	//����
	string m_Pwd;
};

