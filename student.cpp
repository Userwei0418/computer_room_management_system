#include "Student.h"
Student::Student()
{

}

Student::Student(int id, string name, string pwd)
{
	this->m_Id = id;
	this->m_name = name;
	this->m_Pwd = pwd;

	vCom.clear();
	ifstream ifs;
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

void Student::operMenu()
{
	cout << "��ӭѧ������" << this->m_name << "��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.����ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.�鿴�ҵ�ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.�鿴����ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.ȡ��ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.ע����¼              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

//����ԤԼ
void Student::applyOrder()
{
	string date;
	int intervals;
	int room;

	regex datePattern("^[0-9]{4}-[0-9]{1,2}-[0-9]{1,2}$");
	cout << "����������ԤԼ��ʱ��:(yy-mm-dd)" << endl;
	while (true) {
		cin >> date;

		if (regex_match(date, datePattern)) {
			break; // ����Ϸ����˳�ѭ��
		}
		else {
			cout << "���ڸ�ʽ����ȷ������������" << endl;
		}
	}

	cout << "����������ԤԼ��ʱ���:(1:���� 2:����)" << endl;
	while (true)
	{
		cin >> intervals;
		if (intervals >= 1 && intervals <= 2)
		{
			break;
		}
		cout << "������������������" << endl;
	}

	cout << "��ѡ�����: " << endl;
	for (auto i = 0; i < vCom.size(); ++i)
	{
		cout << vCom[i].m_ComId << "�Ż�������Ϊ: "
			<< vCom[i].m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "������������������" << endl;
	}

	cout << "ԤԼ�ɹ��������" << endl;
	
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	ofs << "date:" << date << " ";
	ofs << "intervals:" << intervals << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();
	system("pause");
	system("cls");
}

void Student::applyOrder(Mysql_Connect& connector)
{
	string date;
	int intervals;
	int room;

	regex datePattern("^[0-9]{4}-[0-9]{1,2}-[0-9]{1,2}$");
	cout << "����������ԤԼ��ʱ��:(yyyy-mm-dd)" << endl;
	while (true) {
		cin >> date;

		if (regex_match(date, datePattern)) {
			break; // ����Ϸ����˳�ѭ��
		}
		else {
			cout << "���ڸ�ʽ����ȷ������������" << endl;
		}
	}

	cout << "����������ԤԼ��ʱ���:(1:���� 2:����)" << endl;
	while (true)
	{
		cin >> intervals;
		if (intervals >= 1 && intervals <= 2)
		{
			break;
		}
		cout << "������������������" << endl;
	}

	cout << "��ѡ�����: " << endl;
	for (auto i = 0; i < vCom.size(); ++i)
	{
		cout << vCom[i].m_ComId << "�Ż�������Ϊ: "
			<< vCom[i].m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "������������������" << endl;
	}

	cout << "ԤԼ�ɹ��������" << endl;

	if (connector.CreateOrder("orders", date, to_string(intervals), to_string(this->m_Id), this->m_name, to_string(room), "1"))
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


//�鿴����ԤԼ
void Student::showMyOrder()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; ++i)
	{
		//.c_str() ��stringת�� const char*
		//atoi ��const char* ת��int
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			cout << "ԤԼ���ڣ�" << of.m_orderData[i]["date"];
			cout << "\tʱ��Σ� " << (of.m_orderData[i]["intervals"] == "1" ? "����" : "����");
			cout << "\t�����ţ�" << of.m_orderData[i]["roomId"];
			string status = "\t״̬: ";
			//1:����� 2:�ɹ�ԤԼ -1:ԤԼʧ�� 0:ȡ��ԤԼ
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
				status += "ԤԼʧ�ܣ����δͨ��";
			}
			else if (of.m_orderData[i]["status"] == "0")
			{
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;
		}
	}
	system("pause");
	system("cls");
}

void Student::showMyOrder(Mysql_Connect& connector)
{
	int id = this->m_Id;
	// ִ�в�ѯ
	string query = "SELECT * FROM orders WHERE stuId =" + to_string(id);
	MYSQL_RES* result = connector.GetQueryResult(query);

	if (result)
	{
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(result)))
		{//ע��YSQL_ROW ���ص���������c����ַ�����ʽ��ʾ�� Ҫ��strcmp�Ƚ�
			cout << "ԤԼ����: " << row[0];
			cout << "\tʱ���: " << (strcmp(row[1],"1") == 0 ? "����" : "����");
			cout << "\t������: " << row[4];
			string status = "\t״̬: ";

			if (strcmp(row[5],"1") == 0)
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


//�鿴����ԤԼ
void Student::showAllOrder()
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

		cout << " ԤԼ���ڣ� " << of.m_orderData[i]["date"];
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

void Student::showAllOrder(Mysql_Connect& connector)
{
	// ִ�в�ѯ
	string query = "SELECT * FROM orders";
	MYSQL_RES* result = connector.GetQueryResult(query);

	if (result)
	{
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(result)))
		{//ע��YSQL_ROW ���ص���������c����ַ�����ʽ��ʾ�� Ҫ��strcmp�Ƚ�
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


//ȡ��ԤԼ
void Student::cancelOrder()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;
	vector<int> v;//�������������е��±���
	int index = 1;
	for (int i = 0; i < of.m_Size; ++i)
	{
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "��";
				cout << "ԤԼ���ڣ�" << of.m_orderData[i]["date"];
				cout << " ʱ�Σ�" << (of.m_orderData[i]["intervals"] == "1" ? "����" : "����");
				cout << " ������" << of.m_orderData[i]["roomId"];
				string status = " ״̬�� ";  // 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ  -1 ԤԼʧ��
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "�����";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;
			}
		}
	}
	cout << "������ȡ���ļ�¼,0������" << endl;
	int select = 0;
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
				//	cout << "��¼����λ�ã� " << v[select - 1] << endl;
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "��ȡ��ԤԼ" << endl;
				break;
			}
		}
		cout << "������������������" << endl;
	}

	system("pause");
	system("cls");
}

void Student::cancelOrder(Mysql_Connect& connector)
{
	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ������ѡ��Ҫȡ���ļ�¼" << endl;

	string query = "SELECT * FROM orders WHERE";
	int stuId = this->m_Id;
	string statuses = "1,2"; 
	query += " stuId=" + to_string(stuId) + " AND status IN (" + statuses + ")";

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

		for (auto it = records.begin(); it != records.end(); it++)
		{
			cout << it->first << " ��";
			for (auto mit = it->second.begin(); mit != it->second.end(); mit++)
			{
				cout << mit->first << " " << mit->second << " ";
			}
			cout << endl;
		}

		cout << "������Ҫȡ���ļ�¼�������� (1, 2, ...)�������� 0 ���أ�" << endl;
		int select = 0;
		while (true)
		{
			cin >> select;
			if (select >= 1 && select < index)
			{
				string condition = "date='" + records[select]["date"]
					+ "' AND intervals='" + records[select]["intervals"] 
					+ "' AND roomId='" + records[select]["roomId"] + "'";
				if (connector.UpdateRecord("orders", "status", "0", condition))
				{
					cout << "��¼���³ɹ�" << endl;
				}
				else
				{
					cout << "��¼����ʧ��" << endl;
				}
				// ִ��ȡ����������������ֵѡ��Ҫȡ���ļ�¼
				cout << "��ȡ��ԤԼ��" << endl;
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