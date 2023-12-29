#pragma once
#include "Identity.h"
#include <vector>
#include "ComputerRoom.h"
#include <fstream>
#include <regex>
#include "orderFile.h"
class Student : public Identity
{
public:
	Student();
	Student(int id, string name, string pwd);

	virtual void operMenu();

	//����ԤԼ
	void applyOrder();
	void applyOrder(Mysql_Connect& connector);

	//�鿴����ԤԼ
	void showMyOrder();
	void showMyOrder(Mysql_Connect& connector);

	//�鿴����ԤԼ
	void showAllOrder();
	void showAllOrder(Mysql_Connect& connector);

	//ȡ��ԤԼ
	void cancelOrder();
	void cancelOrder(Mysql_Connect& connector);


	int m_Id;

	//������Ϣ
	vector<ComputerRoom> vCom;
};

