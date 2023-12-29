#include "Manager.h"
#include <string>

//Ĭ�Ϲ���
Manager::Manager()
{

}

//�вι���
Manager::Manager(string name, string pwd)
{
	this->m_name = name;
	this->m_Pwd = pwd;
	this->initVector();//��ʦ ѧ�� ����
}

//ѡ��˵�
void Manager::operMenu()
{
	cout << "��ӭ����Ա��" << this->m_name << "��¼��" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.����˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.�鿴�˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.�鿴����            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.���ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.ע����¼            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

//����˺�
//�ļ���д��
void Manager::addPerson()
{
	cout << "����������˺ŵ�����" << endl;
	cout << "1�����ѧ��" << endl;
	cout << "2�������ʦ" << endl;

	string fileName;
	string tip;
	string errortip;

	ofstream ofs;
	int select = 0;

choice:
	cin >> select;
	if (select == 1)
	{
		fileName = STUDENT_FILE;
		tip = "������ѧ�ţ�";
		errortip = "ѧ���ظ� ����������";
	}
	else if (select == 2)
	{
		fileName = TEACHER_FILE;
		tip = "������ְ���ţ�";
		errortip = "ְ�����ظ� ����������";
	}
	else
	{
		cout << "�������� ���������룺" << endl;
		goto choice;
	}

	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;

	cout << tip << endl;
	while (true)
	{
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret)
		{
			cout << errortip << endl;
		}
		else
		{
			break;
		}
	}
	cout << "����������" << endl;
	cin >> name;
	cout << "����������" << endl;
	cin >> pwd;


	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ�" << endl;

	system("pause");
	system("cls");

	ofs.close();
	//���¼�¼��������
	this->initVector();//���������ȡ ������������ ��һ��������ݿ��� ��ʱ������
}
//mysql��
void Manager::addPerson(Mysql_Connect& connector)
{
	cout << "����������˺ŵ�����" << endl;
	cout << "1�����ѧ��" << endl;
	cout << "2�������ʦ" << endl;

	string tip;
	string table_name;
	
	int select = 0;

choice:
	cin >> select;
	if (select == 1)
	{
		table_name = "students";
		tip = "������ѧ�ţ�";
	}
	else if (select == 2)
	{
		table_name = "teachers";
		tip = "������ְ���ţ�";
	}
	else
	{
		cout << "�������� ���������룺" << endl;
		goto choice;
	}

	
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	cin >> id;
	cout << "����������" << endl;
	cin >> name;
	cout << "����������" << endl;
	cin >> pwd;
	if (connector.CreateRecord(table_name, "id", "name", "pwd", to_string(id), name, pwd))
	{
		cout << "��¼�����ɹ�" << endl;
	}
	else
	{
		cout << "��¼����ʧ��" << endl;
	}


	system("pause");
	system("cls");
}


//�鿴�˺�
//�ļ���д��
void printStudent(Student& s)
{
	cout << "ѧ�ţ� " << s.m_Id << " ������ " << s.m_name << " ���룺" << s.m_Pwd << endl;
}
void printTeacher(Teacher& t)
{
	cout << "ְ���ţ� " << t.m_EmpId << " ������ " << t.m_EmpId << " ���룺" << t.m_Pwd << endl;
}
void Manager::showPerson()
{
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1���鿴����ѧ��" << endl;
	cout << "2���鿴������ʦ" << endl;

	int select = 0;

	cin >> select;

	if (select == 1)
	{
		cout << "����ѧ����Ϣ���£� " << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		cout << "������ʦ��Ϣ���£� " << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}
//mysql��
void Manager::showPerson(Mysql_Connect& connector)
{
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1���鿴����ѧ��" << endl;
	cout << "2���鿴������ʦ" << endl;

	int select = 0;

SELECT:
	cin >> select;

	if (select == 1)
	{
		cout << "����ѧ����Ϣ���£� " << endl;
		string query = "SELECT * FROM students";
		MYSQL_RES* result = connector.GetQueryResult(query);

		if (result)
		{
			MYSQL_ROW row;
			while ((row = mysql_fetch_row(result)))
			{
				cout << "ID: " << row[0]
					<< ", Name: " << row[1]
					<< ", password: " << row[2] 
					<< endl;
			}
			mysql_free_result(result);
		}
		else
		{
			cout << "��ѯʧ��" << endl;
		}
	}
	else if (select == 2)
	{
		cout << "������ʦ��Ϣ���£� " << endl;
		string query = "SELECT * FROM teachers";
		MYSQL_RES* result = connector.GetQueryResult(query);

		if (result)
		{
			MYSQL_ROW row;
			while ((row = mysql_fetch_row(result)))
			{
				cout << "ID: " << row[0]
					<< ", Name: " << row[1]
					<< ", password: " << row[2]
					<< endl;
			}
			mysql_free_result(result);
		}
		else
		{
			cout << "��ѯʧ��" << endl;
		}
	}
	else
	{
		cout << "������������������";
		goto SELECT;
	}
	system("pause");
	system("cls");
}


//�鿴������Ϣ
//�ļ���д
void Manager::showComputer()
{
	cout << "������Ϣ���£� " << endl;
	for (auto it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "������ţ� " << it->m_ComId << " ������������� " << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}
//mysql
void Manager::showComputer(Mysql_Connect& connector)
{
	cout << "������Ϣ���£� " << endl;
	string query = "SELECT * FROM computers";
	MYSQL_RES* result = connector.GetQueryResult(query);

	if (result)
	{
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(result)))
		{
			cout << "ID: " << row[0]
				<< ", Size: " << row[1]
				<< endl;
		}
		mysql_free_result(result);
	}
	else
	{
		cout << "��ѯʧ��" << endl;
	}
	system("pause");
	system("cls");
}


//���ԤԼ��¼
//�ļ���д
void Manager::cleanFile()
{
	cout << "ȷ����գ���ȷ����1   ȡ����0��" << endl;
	int choice;

CHOICE:
	cin >> choice;
	if (choice == 1)
	{
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();

		cout << "��ճɹ�" << endl;
	}
	else if (choice == 0)
	{
		cout << "��ȡ��" << endl;
	}
	else
	{
		cout << "�������� ����������" << endl;
		goto CHOICE;
	}
	system("pause");
	system("cls");
}
//mysql
void Manager::cleanFile(Mysql_Connect& connector)
{
	cout << "ȷ����գ���ȷ����1   ȡ����0��" << endl;
	int choice;

CHOICE:
	cin >> choice;
	if (choice == 1)
	{
		if (connector.DeleteRecord("orders", "1 = 1"))
		{
			cout << "�����" << endl;
		}
		else
		{
			cout << "���ʧ��" << endl;
		}
	}
	else if (choice == 0)
	{
		cout << "��ȡ��" << endl;
	}
	else
	{
		cout << "�������� ����������" << endl;
		goto CHOICE;
	}
	system("pause");
	system("cls");

	
}

//��ʼ������ ��ȡ�ļ����ݵ�vector ����ȥ�أ�mysql�治��Ҫ �������ɣ�
void Manager::initVector()
{
	vStu.clear();
	vTea.clear();
	vCom.clear();

	ifstream ifs;
	//��ȡ��Ϣ ѧ�� 

	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	//cout << "��ǰѧ������Ϊ�� " << vStu.size() << endl;
	ifs.close();

	//��ȡ��ʦ��Ϣ
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	//cout << "��ǰ��ʦ����Ϊ�� " << vStu.size() << endl;
	ifs.close();

	//��ȡ������Ϣ
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		vCom.push_back(com);
	}
	//cout << "��ǰ��������Ϊ�� " << vCom.size() << endl;
	ifs.close();
}

//����ظ�                ѧ/����  �������
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (auto it = vStu.begin(); it != vStu.end(); ++it)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else//ǰ���Ѿ����й�ɸѡ ֻ��1��2�ᱻ������ ֱ��else����
	{
		for (auto it = vTea.begin(); it != vTea.end(); ++it)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}
	return false;
}