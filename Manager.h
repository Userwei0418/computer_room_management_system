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
	//Ĭ�Ϲ���
	Manager();

	//�вι���  ����Ա����������
	Manager(string name, string pwd);

	//ѡ��˵�
	virtual void operMenu();

	//����˺�  
	void addPerson();
	void addPerson(Mysql_Connect& connector);

	//�鿴�˺�
	void showPerson();
	void showPerson(Mysql_Connect& connector);

	//�鿴������Ϣ
	void showComputer();
	void showComputer(Mysql_Connect& connector);

	//���ԤԼ��¼
	void cleanFile();
	void cleanFile(Mysql_Connect& connector);

	//��ʼ������
	void initVector();

	//����ظ�        ѧ/����  �������
	bool checkRepeat(int id, int type);

	//ѧ������
	vector<Student> vStu;

	//��ʦ����
	vector<Teacher> vTea;

	//������Ϣ
	vector<ComputerRoom> vCom;
};

