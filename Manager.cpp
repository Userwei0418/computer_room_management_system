#include "Manager.h"
#include <string>

//默认构造
Manager::Manager()
{

}

//有参构造
Manager::Manager(string name, string pwd)
{
	this->m_name = name;
	this->m_Pwd = pwd;
	this->initVector();//教师 学生 机房
}

//选择菜单
void Manager::operMenu()
{
	cout << "欢迎管理员：" << this->m_name << "登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//添加账号
//文件读写版
void Manager::addPerson()
{
	cout << "请输入添加账号的类型" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;

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
		tip = "请输入学号：";
		errortip = "学号重复 请重新输入";
	}
	else if (select == 2)
	{
		fileName = TEACHER_FILE;
		tip = "请输入职工号：";
		errortip = "职工号重复 请重新输入";
	}
	else
	{
		cout << "输入有误 请重新输入：" << endl;
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
	cout << "请输入姓名" << endl;
	cin >> name;
	cout << "请输入密码" << endl;
	cin >> pwd;


	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;

	system("pause");
	system("cls");

	ofs.close();
	//更新记录进入容器
	this->initVector();//清空重新提取 数据量大不适用 但一大就用数据库了 暂时这样吧
}
//mysql版
void Manager::addPerson(Mysql_Connect& connector)
{
	cout << "请输入添加账号的类型" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;

	string tip;
	string table_name;
	
	int select = 0;

choice:
	cin >> select;
	if (select == 1)
	{
		table_name = "students";
		tip = "请输入学号：";
	}
	else if (select == 2)
	{
		table_name = "teachers";
		tip = "请输入职工号：";
	}
	else
	{
		cout << "输入有误 请重新输入：" << endl;
		goto choice;
	}

	
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	cin >> id;
	cout << "请输入姓名" << endl;
	cin >> name;
	cout << "请输入密码" << endl;
	cin >> pwd;
	if (connector.CreateRecord(table_name, "id", "name", "pwd", to_string(id), name, pwd))
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


//查看账号
//文件读写版
void printStudent(Student& s)
{
	cout << "学号： " << s.m_Id << " 姓名： " << s.m_name << " 密码：" << s.m_Pwd << endl;
}
void printTeacher(Teacher& t)
{
	cout << "职工号： " << t.m_EmpId << " 姓名： " << t.m_EmpId << " 密码：" << t.m_Pwd << endl;
}
void Manager::showPerson()
{
	cout << "请选择查看内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;

	int select = 0;

	cin >> select;

	if (select == 1)
	{
		cout << "所有学生信息如下： " << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		cout << "所有老师信息如下： " << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}
//mysql版
void Manager::showPerson(Mysql_Connect& connector)
{
	cout << "请选择查看内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;

	int select = 0;

SELECT:
	cin >> select;

	if (select == 1)
	{
		cout << "所有学生信息如下： " << endl;
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
			cout << "查询失败" << endl;
		}
	}
	else if (select == 2)
	{
		cout << "所有老师信息如下： " << endl;
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
			cout << "查询失败" << endl;
		}
	}
	else
	{
		cout << "输入有误，请重新输入";
		goto SELECT;
	}
	system("pause");
	system("cls");
}


//查看机房信息
//文件读写
void Manager::showComputer()
{
	cout << "机房信息如下： " << endl;
	for (auto it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "机房编号： " << it->m_ComId << " 机房最大容量： " << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}
//mysql
void Manager::showComputer(Mysql_Connect& connector)
{
	cout << "机房信息如下： " << endl;
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
		cout << "查询失败" << endl;
	}
	system("pause");
	system("cls");
}


//清空预约记录
//文件读写
void Manager::cleanFile()
{
	cout << "确定清空？（确定：1   取消：0）" << endl;
	int choice;

CHOICE:
	cin >> choice;
	if (choice == 1)
	{
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();

		cout << "清空成功" << endl;
	}
	else if (choice == 0)
	{
		cout << "已取消" << endl;
	}
	else
	{
		cout << "输入有误 请重新输入" << endl;
		goto CHOICE;
	}
	system("pause");
	system("cls");
}
//mysql
void Manager::cleanFile(Mysql_Connect& connector)
{
	cout << "确定清空？（确定：1   取消：0）" << endl;
	int choice;

CHOICE:
	cin >> choice;
	if (choice == 1)
	{
		if (connector.DeleteRecord("orders", "1 = 1"))
		{
			cout << "已清空" << endl;
		}
		else
		{
			cout << "清空失败" << endl;
		}
	}
	else if (choice == 0)
	{
		cout << "已取消" << endl;
	}
	else
	{
		cout << "输入有误 请重新输入" << endl;
		goto CHOICE;
	}
	system("pause");
	system("cls");

	
}

//初始化容器 提取文件内容到vector 进而去重（mysql版不需要 主键即可）
void Manager::initVector()
{
	vStu.clear();
	vTea.clear();
	vCom.clear();

	ifstream ifs;
	//读取信息 学生 

	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	//cout << "当前学生数量为： " << vStu.size() << endl;
	ifs.close();

	//获取老师信息
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	//cout << "当前老师数量为： " << vStu.size() << endl;
	ifs.close();

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

//检测重复                学/工号  检测类型
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
	else//前面已经进行过筛选 只有1或2会被传进来 直接else就行
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