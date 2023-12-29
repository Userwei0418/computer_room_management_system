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

	//申请预约
	void applyOrder();
	void applyOrder(Mysql_Connect& connector);

	//查看自身预约
	void showMyOrder();
	void showMyOrder(Mysql_Connect& connector);

	//查看所有预约
	void showAllOrder();
	void showAllOrder(Mysql_Connect& connector);

	//取消预约
	void cancelOrder();
	void cancelOrder(Mysql_Connect& connector);


	int m_Id;

	//机房信息
	vector<ComputerRoom> vCom;
};

