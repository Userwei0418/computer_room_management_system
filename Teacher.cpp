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
	cout << "欢迎教师：" << this->m_name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.审核预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//查看所有预约
void Teacher::showAllOrder()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "、 ";

		cout << "预约日期： " << of.m_orderData[i]["date"];
		cout << " 时段：" << (of.m_orderData[i]["intervals"] == "1" ? "上午" : "下午");
		cout << " 学号：" << of.m_orderData[i]["stuId"];
		cout << " 姓名：" << of.m_orderData[i]["stuName"];
		cout << " 机房：" << of.m_orderData[i]["roomId"];
		string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "审核未通过，预约失败";
		}
		else
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

void Teacher::showAllOrder(Mysql_Connect& connector)
{
	// 执行查询
	string query = "SELECT * FROM orders";
	MYSQL_RES* result = connector.GetQueryResult(query);

	if (result)
	{
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(result)))
		{
			cout << "预约日期: " << row[0];
			cout << "\t时间段: " << (strcmp(row[1], "1") == 0 ? "上午" : "下午");
			cout << "\t学号：" << row[2];
			cout << "\t姓名：" << row[3];
			cout << "\t机房号: " << row[4];
			string status = "\t状态: ";

			if (strcmp(row[5], "1") == 0)
			{
				status += "审核中";
			}
			else if (strcmp(row[5], "2") == 0)
			{
				status += "预约成功";
			}
			else if (strcmp(row[5], "-1") == 0)
			{
				status += "预约失败，审核未通过";
			}
			else if (strcmp(row[5], "0") == 0)
			{
				status += "预约已取消";
			}
			cout << status << endl;
		}
		mysql_free_result(result);
	}
	else
	{
		cout << "查询失败" << endl;
	}
	system("pause");
	system("cls");
}


//审核预约
void Teacher::validOrder()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "待审核的预约记录如下：" << endl;

	vector<int>v;
	int index = 0;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << ++index << "、 ";
			cout << "预约日期： " << of.m_orderData[i]["date"];
			cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房：" << of.m_orderData[i]["roomId"];
			string status = " 状态： ";
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			cout << status << endl;
		}
	}

	cout << "请输入审核的预约记录,0代表返回" << endl;
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
				cout << "请输入审核结果" << endl;
				cout << "1、通过" << endl;
				cout << "2、不通过" << endl;
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
				cout << "审核完毕！" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}

	system("pause");
	system("cls");
}

void Teacher::validOrder(Mysql_Connect& connector)
{
	cout << "待审核的预约记录如下：" << endl;

	string query = "SELECT * FROM orders WHERE status = 1";

	MYSQL_RES* result = connector.GetQueryResult(query);

	if (result)
	{
		MYSQL_ROW row;
		map<int, map<string, string>> records; // 存储符合条件的记录
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
			cout << it->first << " 、";
			for (auto mit = it->second.begin(); mit != it->second.end(); ++mit)
			{
				cout << mit->first << " " << mit->second << " ";
			}
			cout << endl;
		}

		cout << "请输入审核的预约记录,或输入0返回" << endl;
		int select = 0;
		int ret = 0;
		while (true)
		{
			cin >> select;
			if (select >= 1 && select < index)
			{
				cout << "请输入审核结果" << endl;
				cout << "1、通过" << endl;
				cout << "2、不通过" << endl;
				
				CHOICE:
				cin >> ret;
				if (ret == 1)
				{
					string condition = "date='" + records[select]["date"]
						+ "' AND intervals='" + records[select]["intervals"]
						+ "' AND roomId='" + records[select]["roomId"] + "'";
					if (connector.UpdateRecord("orders", "status", "2", condition))
					{
						cout << "记录更新成功" << endl;
					}
					else
					{
						cout << "记录更新失败" << endl;
					}
				}
				else if (ret == 2)
				{
					string condition = "date='" + records[select]["date"]
						+ "' AND intervals='" + records[select]["intervals"]
						+ "' AND roomId='" + records[select]["roomId"] + "'";
					if (connector.UpdateRecord("orders", "status", "-1", condition))
					{
						cout << "记录更新成功" << endl;
					}
					else
					{
						cout << "记录更新失败" << endl;
					}
				}
				else
				{
					cout << "输入有误，请重新输入" << endl;
					goto CHOICE;
				}
				cout << "审核完毕！" << endl;
				break;
			}
			else if (select == 0)
			{
				break; // 返回
			}
			cout << "输入有误，请重新输入" << endl;
		}
	}
	else
	{
		cout << "查询失败" << endl;
	}
	system("pause");
	system("cls");
}