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

	//�鿴����ԤԼ
	void showAllOrder();
	void showAllOrder(Mysql_Connect& connector);

	//���ԤԼ
	void validOrder();
	void validOrder(Mysql_Connect& connector);
	int m_EmpId; //��ʦ���
};

