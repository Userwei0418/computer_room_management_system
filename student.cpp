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
	//获取机房信息
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
	{
		vCom.push_back(com);
	}
	//cout << "当前机房数量为： " << vCom.size() << endl;
	ifs.close();
}

void Student::operMenu()
{
	cout << "欢迎学生代表：" << this->m_name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.申请预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.查看我的预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.取消预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//申请预约
void Student::applyOrder()
{
	string date;
	int intervals;
	int room;

	regex datePattern("^[0-9]{4}-[0-9]{1,2}-[0-9]{1,2}$");
	cout << "请输入申请预约的时间:(yy-mm-dd)" << endl;
	while (true) {
		cin >> date;

		if (regex_match(date, datePattern)) {
			break; // 输入合法，退出循环
		}
		else {
			cout << "日期格式不正确，请重新输入" << endl;
		}
	}

	cout << "请输入申请预约的时间段:(1:上午 2:下午)" << endl;
	while (true)
	{
		cin >> intervals;
		if (intervals >= 1 && intervals <= 2)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "请选择机房: " << endl;
	for (auto i = 0; i < vCom.size(); ++i)
	{
		cout << vCom[i].m_ComId << "号机房容量为: "
			<< vCom[i].m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "预约成功！审核中" << endl;
	
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
	cout << "请输入申请预约的时间:(yyyy-mm-dd)" << endl;
	while (true) {
		cin >> date;

		if (regex_match(date, datePattern)) {
			break; // 输入合法，退出循环
		}
		else {
			cout << "日期格式不正确，请重新输入" << endl;
		}
	}

	cout << "请输入申请预约的时间段:(1:上午 2:下午)" << endl;
	while (true)
	{
		cin >> intervals;
		if (intervals >= 1 && intervals <= 2)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "请选择机房: " << endl;
	for (auto i = 0; i < vCom.size(); ++i)
	{
		cout << vCom[i].m_ComId << "号机房容量为: "
			<< vCom[i].m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "预约成功！审核中" << endl;

	if (connector.CreateOrder("orders", date, to_string(intervals), to_string(this->m_Id), this->m_name, to_string(room), "1"))
	{
		cout << "记录创建成功" << endl;
	}
	else
	{
		cout << "记录创建失败" << endl;
	}

	system("pause");
	system("cls");
}


//查看自身预约
void Student::showMyOrder()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; ++i)
	{
		//.c_str() 将string转成 const char*
		//atoi 将const char* 转成int
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			cout << "预约日期：" << of.m_orderData[i]["date"];
			cout << "\t时间段： " << (of.m_orderData[i]["intervals"] == "1" ? "上午" : "下午");
			cout << "\t机房号：" << of.m_orderData[i]["roomId"];
			string status = "\t状态: ";
			//1:审核中 2:成功预约 -1:预约失败 0:取消预约
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
				status += "预约失败，审核未通过";
			}
			else if (of.m_orderData[i]["status"] == "0")
			{
				status += "预约已取消";
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
	// 执行查询
	string query = "SELECT * FROM orders WHERE stuId =" + to_string(id);
	MYSQL_RES* result = connector.GetQueryResult(query);

	if (result)
	{
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(result)))
		{//注意YSQL_ROW 返回的数据是以c风格字符串形式表示的 要用strcmp比较
			cout << "预约日期: " << row[0];
			cout << "\t时间段: " << (strcmp(row[1],"1") == 0 ? "上午" : "下午");
			cout << "\t机房号: " << row[4];
			string status = "\t状态: ";

			if (strcmp(row[5],"1") == 0)
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


//查看所有预约
void Student::showAllOrder()
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

		cout << " 预约日期： " << of.m_orderData[i]["date"];
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

void Student::showAllOrder(Mysql_Connect& connector)
{
	// 执行查询
	string query = "SELECT * FROM orders";
	MYSQL_RES* result = connector.GetQueryResult(query);

	if (result)
	{
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(result)))
		{//注意YSQL_ROW 返回的数据是以c风格字符串形式表示的 要用strcmp比较
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


//取消预约
void Student::cancelOrder()
{
	orderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;
	vector<int> v;//存放在最大容器中的下标编号
	int index = 1;
	for (int i = 0; i < of.m_Size; ++i)
	{
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、";
				cout << "预约日期：" << of.m_orderData[i]["date"];
				cout << " 时段：" << (of.m_orderData[i]["intervals"] == "1" ? "上午" : "下午");
				cout << " 机房：" << of.m_orderData[i]["roomId"];
				string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约  -1 预约失败
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}
	cout << "请输入取消的记录,0代表返回" << endl;
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
				//	cout << "记录所在位置： " << v[select - 1] << endl;
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}

	system("pause");
	system("cls");
}

void Student::cancelOrder(Mysql_Connect& connector)
{
	cout << "审核中或预约成功的记录可以取消，请选择要取消的记录" << endl;

	string query = "SELECT * FROM orders WHERE";
	int stuId = this->m_Id;
	string statuses = "1,2"; 
	query += " stuId=" + to_string(stuId) + " AND status IN (" + statuses + ")";

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

		for (auto it = records.begin(); it != records.end(); it++)
		{
			cout << it->first << " 、";
			for (auto mit = it->second.begin(); mit != it->second.end(); mit++)
			{
				cout << mit->first << " " << mit->second << " ";
			}
			cout << endl;
		}

		cout << "请输入要取消的记录的索引号 (1, 2, ...)，或输入 0 返回：" << endl;
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
					cout << "记录更新成功" << endl;
				}
				else
				{
					cout << "记录更新失败" << endl;
				}
				// 执行取消操作，根据索引值选择要取消的记录
				cout << "已取消预约：" << endl;
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