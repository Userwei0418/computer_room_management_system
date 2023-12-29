#pragma once
#include "Identity.h"
#include "Teacher.h"
#include "Student.h"
#include <vector>
#include <algorithm>
#include "ComputerRoom.h"
class Manager : public Identity
{
public:
	//默认构造
	Manager();

	//有参构造  管理员姓名，密码
	Manager(string name, string pwd);

	//选择菜单
	virtual void operMenu();

	//添加账号  
	void addPerson();
	void addPerson(Mysql_Connect& connector);

	//查看账号
	void showPerson();
	void showPerson(Mysql_Connect& connector);

	//查看机房信息
	void showComputer();
	void showComputer(Mysql_Connect& connector);

	//清空预约记录
	void cleanFile();
	void cleanFile(Mysql_Connect& connector);

	//初始化容器
	void initVector();

	//检测重复        学/工号  检测类型
	bool checkRepeat(int id, int type);

	//学生容器
	vector<Student> vStu;

	//教师容器
	vector<Teacher> vTea;

	//机房信息
	vector<ComputerRoom> vCom;
};

