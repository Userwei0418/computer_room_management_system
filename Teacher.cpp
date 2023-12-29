#include "Teacher.h"
Teacher::Teacher()
{

}

Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_EmpId = empId;
	this->m_name = name;
	this->m_Pwd = pwd;
}

void Teacher::operMenu()
{
	cout << "��ӭ��ʦ��" << this->m_name << "��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.�鿴����ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.���ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.ע����¼              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

//�鿴����ԤԼ
void Teacher::showAllOrder()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "�� ";

		cout << "ԤԼ���ڣ� " << of.m_orderData[i]["date"];
		cout << " ʱ�Σ�" << (of.m_orderData[i]["intervals"] == "1" ? "����" : "����");
		cout << " ѧ�ţ�" << of.m_orderData[i]["stuId"];
		cout << " ������" << of.m_orderData[i]["stuName"];
		cout << " ������" << of.m_orderData[i]["roomId"];
		string status = " ״̬�� ";  // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ -1 ԤԼʧ��
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "���δͨ����ԤԼʧ��";
		}
		else
		{
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

void Teacher::showAllOrder(Mysql_Connect& connector)
{
	// ִ�в�ѯ
	string query = "SELECT * FROM orders";
	MYSQL_RES* result = connector.GetQueryResult(query);

	if (result)
	{
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(result)))
		{
			cout << "ԤԼ����: " << row[0];
			cout << "\tʱ���: " << (strcmp(row[1], "1") == 0 ? "����" : "����");
			cout << "\tѧ�ţ�" << row[2];
			cout << "\t������" << row[3];
			cout << "\t������: " << row[4];
			string status = "\t״̬: ";

			if (strcmp(row[5], "1") == 0)
			{
				status += "�����";
			}
			else if (strcmp(row[5], "2") == 0)
			{
				status += "ԤԼ�ɹ�";
			}
			else if (strcmp(row[5], "-1") == 0)
			{
				status += "ԤԼʧ�ܣ����δͨ��";
			}
			else if (strcmp(row[5], "0") == 0)
			{
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;
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


//���ԤԼ
void Teacher::validOrder()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����˵�ԤԼ��¼���£�" << endl;

	vector<int>v;
	int index = 0;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << ++index << "�� ";
			cout << "ԤԼ���ڣ� " << of.m_orderData[i]["date"];
			cout << " ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " ������" << of.m_orderData[i]["roomId"];
			string status = " ״̬�� ";
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "�����";
			}
			cout << status << endl;
		}
	}

	cout << "��������˵�ԤԼ��¼,0������" << endl;
	int select = 0;
	int ret = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "��������˽��" << endl;
				cout << "1��ͨ��" << endl;
				cout << "2����ͨ��" << endl;
				cin >> ret;

				if (ret == 1)
				{
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "�����ϣ�" << endl;
				break;
			}
		}
		cout << "������������������" << endl;
	}

	system("pause");
	system("cls");
}

void Teacher::validOrder(Mysql_Connect& connector)
{
	cout << "����˵�ԤԼ��¼���£�" << endl;

	string query = "SELECT * FROM orders WHERE status = 1";

	MYSQL_RES* result = connector.GetQueryResult(query);

	if (result)
	{
		MYSQL_ROW row;
		map<int, map<string, string>> records; // �洢���������ļ�¼
		int index = 1;
		while ((row = mysql_fetch_row(result)))
		{
			string key;
			string value;
			map<string, string> m;

			key = "date";
			value = string(row[0]);
			m.insert(make_pair(key, value));

			key = "intervals";
			value = string(row[1]);
			m.insert(make_pair(key, value));

			key = "stuId";
			value = string(row[2]);
			m.insert(make_pair(key, value));

			key = "stuName";
			value = string(row[3]);
			m.insert(make_pair(key, value));

			key = "roomId";
			value = string(row[4]);
			m.insert(make_pair(key, value));

			key = "status";
			value = string(row[5]);
			m.insert(make_pair(key, value));

			records.insert(make_pair(index, m));
			++index;
		}
		mysql_free_result(result);

		for (auto it = records.begin(); it != records.end(); ++it)
		{
			cout << it->first << " ��";
			for (auto mit = it->second.begin(); mit != it->second.end(); ++mit)
			{
				cout << mit->first << " " << mit->second << " ";
			}
			cout << endl;
		}

		cout << "��������˵�ԤԼ��¼,������0����" << endl;
		int select = 0;
		int ret = 0;
		while (true)
		{
			cin >> select;
			if (select >= 1 && select < index)
			{
				cout << "��������˽��" << endl;
				cout << "1��ͨ��" << endl;
				cout << "2����ͨ��" << endl;
				
				CHOICE:
				cin >> ret;
				if (ret == 1)
				{
					string condition = "date='" + records[select]["date"]
						+ "' AND intervals='" + records[select]["intervals"]
						+ "' AND roomId='" + records[select]["roomId"] + "'";
					if (connector.UpdateRecord("orders", "status", "2", condition))
					{
						cout << "��¼���³ɹ�" << endl;
					}
					else
					{
						cout << "��¼����ʧ��" << endl;
					}
				}
				else if (ret == 2)
				{
					string condition = "date='" + records[select]["date"]
						+ "' AND intervals='" + records[select]["intervals"]
						+ "' AND roomId='" + records[select]["roomId"] + "'";
					if (connector.UpdateRecord("orders", "status", "-1", condition))
					{
						cout << "��¼���³ɹ�" << endl;
					}
					else
					{
						cout << "��¼����ʧ��" << endl;
					}
				}
				else
				{
					cout << "������������������" << endl;
					goto CHOICE;
				}
				cout << "�����ϣ�" << endl;
				break;
			}
			else if (select == 0)
			{
				break; // ����
			}
			cout << "������������������" << endl;
		}
	}
	else
	{
		cout << "��ѯʧ��" << endl;
	}
	system("pause");
	system("cls");
}