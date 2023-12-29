#pragma once
#include "Identity.h"
#include <string>
#include "orderFile.h"
#include <vector>
class Teacher : public Identity
{
public:
	Teacher();
	Teacher(int empId, string name, string pwd);

	virtual void operMenu();

	//查看所有预约
	void showAllOrder();
	void showAllOrder(Mysql_Connect& connector);

	//审核预约
	void validOrder();
	void validOrder(Mysql_Connect& connector);
	int m_EmpId; //教师编号
};

