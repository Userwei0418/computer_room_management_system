/*
使用了文件读写和连接mysql数据库两种方式 基本是按照面向对象的方式 把各个模块封装成类
但是对于私有公有等没有刻意强调 半成品吧
主文件里的这几个菜单的全局函数应该也能封装起来 以后再看吧
这里的对mysql的一个封装很关键 
用了不少goto 虽然说最好别用 但用它来跳出很深的循环真的很管用……
貌似没有什么逻辑上的问题 就简单的输入错误跳转重新输罢了
难度不大 感觉一直都是做差不多的事情 感觉还能封装很多函数 省很多步骤
还有这个mysql的语句 难道每次条件变了就得重新写接口吗 太麻烦了吧 
为什么没人把这个模板做出来……
还是说c++的赛道不在这 其他语言会方便很多
啧
本来还想着加上些easyX的东西进去的
但已经用了整整12小时了 有些累了 算了吧 那种东西还得自己手动计算坐标……
不知道qt会是什么样
慢慢来吧
*/

/*
mysql中使用以下初始化：

create database 机房预约系统;
use 机房预约系统;
CREATE TABLE students (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    pwd VARCHAR(255) NOT NULL
);
CREATE TABLE teachers (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    pwd VARCHAR(255) NOT NULL
);
CREATE TABLE managers (
    name VARCHAR(255) NOT NULL,
    pwd VARCHAR(255) NOT NULL
);
CREATE TABLE computers (
    id INT NOT NULL,
    size INT NOT NULL
);
CREATE TABLE orders (
    date DATE NOT NULL,
    intervals INT NOT NULL,
    stuId INT NOT NULL ,
    stuName VARCHAR(255) NOT NULL,
    roomId int NOT NULL ,
    status int NOT NULL
);

insert into managers(name, pwd) values ('admin','123');
insert into computers(id, size) VALUES ('1','20');
insert into computers(id, size) VALUES ('2','50');
insert into computers(id, size) VALUES ('3','100');
*/

#include <iostream>
#include "Mysql_Connect.h"
#include "Identity.h"
#include "globalFile.h"
#include <fstream>
#include <string>
#include "student.h"
#include "teacher.h"
#include "Manager.h"
using namespace std;

//以两种方式实现 接口在main的case部分

//57~288为文件读写的方式实现
//进入学生子菜单界面
void studentMenu(Identity*& student)
{
    while (true)
    {
        student->operMenu();
        Student* stu = (Student*)student;
        int select = 0;

SELECT:
        cin >> select;
        if (select == 1)//申请预约
        {
            cout << "申请预约" << endl;
            stu->applyOrder();
        }
        else if (select == 2)//查看自身预约
        {
            cout << "查看自身预约" << endl;
            stu->showMyOrder();
        }
        else if (select == 3)//查看所有预约
        {
            cout << "查看所有预约" << endl;
            stu->showAllOrder();
        }
        else if (select == 4)//取消预约
        {
            cout << "取消预约" << endl;
            stu->cancelOrder();
        }
        else if (select == 0)
        {
            delete student;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "输入有误 请重新输入" << endl;
            goto SELECT;
        }
    }
}

//进入教师子菜单界面
void teacherMenu(Identity*& teacher)
{
    while (true)
    {
        teacher->operMenu();
        Teacher* tea = (Teacher*)teacher;
        int select = 0;

SELECT:
        cin >> select;
        if (select == 1)//查看所有预约  
        {
            cout << "查看所有预约" << endl;
            tea->showAllOrder();
        }
        else if (select == 2)//审核预约
        {
            cout << "审核预约" << endl;
            tea->validOrder();
        }
        else if (select == 0)
        {
            delete teacher;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "输入有误 请重新输入" << endl;
            goto SELECT;
        }
    }
}

//进入管理员子菜单
void managerMenu(Identity*& manager)
{
    while (true)
    {
        //调用管理员子菜单
        manager->operMenu();
        Manager* man = (Manager*)manager;
        int select = 0;
  
SELECT:
        cin >> select;
        if (select == 1)//添加账号
        {
            cout << "添加账号" << endl;
            man->addPerson();
        }
        else if (select == 2)//查看账号
        {
            cout << "查看账号" << endl;
            man->showPerson();
        } 
        else if (select == 3)//查看机房
        {
            cout << "查看机房" << endl;
            man->showComputer();
        }
        else if (select == 4)//清空预约
        {
            cout << "清空预约" << endl;
            man->cleanFile();
        }
        else if (select == 0)
        {
            delete manager;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "输入有误 请重新输入" << endl;
            goto SELECT;
        }
    }
}

//使用文件读写
void LoginIn(string FileName, int type)
{//                 文件名     身份类型
    Identity* person = NULL;//父类指针 用于指向子类对象

    //读文件
    ifstream ifs;
    ifs.open(FileName, ios::in);

    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    //准备接收信息
    int id = 0;
    string name;
    string pwd;

    if (type == 1)
    {
        cout << "请输入你的学号" << endl;
        cin >> id;
    }
    else if (type == 2)
    {
        cout << "请输入你的职工号" << endl;
        cin >> id;
    }

    cout << "请输入用户名： " << endl;
    cin >> name;

    cout << "请输入密码： " << endl;
    cin >> pwd;

    if (type == 1)
    {
        int fId;
        string fName;
        string fPwd;
        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if (fId == id && fName == name && fPwd == pwd)
            {
                cout << "学生验证登入成功！" << endl;
                system("pause");
                system("cls");
                person = new Student(id, name, pwd);

                studentMenu(person);
                return;
            }
        }
    }
    else if (type == 2)
    {
        int fId;
        string fName;
        string fPwd;
        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if (fId == id && fName == name && fPwd == pwd)
            {
                cout << "教师验证登入成功！" << endl;
                system("pause");
                system("cls");
                person = new Teacher(id, name, pwd);

                teacherMenu(person);
                return;
            }
        }
    }
    else if (type == 3)
    {
        string fName;
        string fPwd;
        while (ifs >> fName && ifs >> fPwd)
        {
            if (fName == name && fPwd == pwd)
            {
                cout << "管理员验证登入成功！" << endl;
                system("pause");
                system("cls");
                person = new Manager(name, pwd);

                managerMenu(person);
                return;
            }
        }
    }

    cout << "验证登入失败！" << endl;
    system("pause");
    system("cls");
}


//291~548为mysql实现
//使用mysql
//管理员菜单
void managerMenu(Identity*& manager, Mysql_Connect& connector)
{
    while (true)
    {
        //调用管理员子菜单
        manager->operMenu();
        Manager* man = (Manager*)manager;
        int select = 0;

SELECT:
        cin >> select;
        if (select == 1)//添加账号
        {
            cout << "添加账号" << endl;
            man->addPerson(connector);
        }
        else if (select == 2)//查看账号
        {
            cout << "查看账号" << endl;
            man->showPerson(connector);
        }
        else if (select == 3)//查看机房
        {
            cout << "查看机房" << endl;
            man->showComputer(connector);
        }
        else if (select == 4)//清空预约
        {
            cout << "清空预约" << endl;
            man->cleanFile(connector);
        }
        else if (select == 0)
        {
            delete manager;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "输入有误 请重新输入" << endl;
            goto SELECT;
        }
    }
}

//学生菜单
void studentMenu(Identity*& student, Mysql_Connect& connector)
{
    while (true)
    {
        student->operMenu();
        Student* stu = (Student*)student;
        int select = 0;

    SELECT:
        cin >> select;
        if (select == 1)//申请预约
        {
            cout << "申请预约" << endl;
            stu->applyOrder(connector);
        }
        else if (select == 2)//查看自身预约
        {
            cout << "查看自身预约" << endl;
            stu->showMyOrder(connector);
        }
        else if (select == 3)//查看所有预约
        {
            cout << "查看所有预约" << endl;
            stu->showAllOrder(connector);
        }
        else if (select == 4)//取消预约
        {
            cout << "取消预约" << endl;
            stu->cancelOrder(connector);
        }
        else if (select == 0)
        {
            delete student;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "输入有误 请重新输入" << endl;
            goto SELECT;
        }
    }
}

//进入教师子菜单界面
void teacherMenu(Identity*& teacher, Mysql_Connect& connector)
{
    while (true)
    {
        teacher->operMenu();
        Teacher* tea = (Teacher*)teacher;
        int select = 0;

    SELECT:
        cin >> select;
        if (select == 1)//查看所有预约  
        {
            cout << "查看所有预约" << endl;
            tea->showAllOrder(connector);
        }
        else if (select == 2)//审核预约
        {
            cout << "审核预约" << endl;
            tea->validOrder(connector);
        }
        else if (select == 0)
        {
            delete teacher;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "输入有误 请重新输入" << endl;
            goto SELECT;
        }
    }
}

void LoginIn(Mysql_Connect& connector, int type)
{
    Identity* person = NULL;//父类指针 用于指向子类对象

    //准备接收信息
    int id;
    string name;
    string pwd;

    if (type == 1)
    {
        cout << "请输入你的学号" << endl;
        cin >> id;

    }
    else if (type == 2)
    {
        cout << "请输入你的职工号" << endl;
        cin >> id;

    }

    cout << "请输入用户名： " << endl;
    cin >> name;

    cout << "请输入密码： " << endl;
    cin >> pwd;


    if (type == 1)
    {
        string query = "SELECT * FROM students WHERE id=" + to_string(id);
        MYSQL_RES* result = connector.GetQueryResult(query);

        if (result)
        {
            //cout << "查询成功！" << endl;
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result)))
            {
                if (row[0] == to_string(id) && row[1] == name && row[2] == pwd)
                {
                    cout << "学生验证登入成功！" << endl;
                    system("pause");
                    system("cls");
                    person = new Student(id, name, pwd);

                    studentMenu(person, connector);
                    return;
                }

            }
            mysql_free_result(result);
        }
        else
        {
            cout << "查询失败" << endl;
        }
    }
    else if (type == 2)
    {
        string query = "SELECT * FROM teachers WHERE id=" + to_string(id);
        MYSQL_RES* result = connector.GetQueryResult(query);

        if (result)
        {
            //cout << "查询成功！" << endl;
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result)))
            {
                if (row[0] == to_string(id) && row[1] == name && row[2] == pwd)
                {
                    cout << "教师验证登入成功！" << endl;
                    system("pause");
                    system("cls");
                    person = new Teacher(id, name, pwd);

                    teacherMenu(person, connector);
                    return;
                }

            }
            mysql_free_result(result);
        }
        else
        {
            cout << "查询失败" << endl;
        }
    }
    else if (type == 3)
    {
        string query = "SELECT * FROM managers";
        MYSQL_RES* result = connector.GetQueryResult(query);

        if (result)
        {
            //cout << "查询成功！" << endl;
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result)))
            {
                if (row[0] == name && row[1] == pwd)
                {
                    cout << "管理员验证登入成功！" << endl;
                    system("pause");
                    system("cls");
                    person = new Manager(name, pwd);

                    managerMenu(person, connector);
                    return;
                }

            }
            mysql_free_result(result);
        }
        else
        {
            cout << "查询失败" << endl;
        }
    }

    cout << "验证登入失败！" << endl;
    system("pause");
    system("cls");
}


int main()
{
    try 
    {
        // 创建数据库连接
        Mysql_Connect connector("localhost", "root", "zw200495", "机房预约系统");
        
        if (connector.Connect()) 
        {
            system("cls");
            int select = 0;

            while (true)
            {
                cout << "======================  欢迎来到机房预约系统  ====================="<< endl;
                cout << endl << "请输入您的身份" << endl;
                cout << "\t\t -------------------------------\n";
                cout << "\t\t|                               |\n";
                cout << "\t\t|          1.学生代表           |\n";
                cout << "\t\t|                               |\n";
                cout << "\t\t|          2.老    师           |\n";
                cout << "\t\t|                               |\n";
                cout << "\t\t|          3.管 理 员           |\n";
                cout << "\t\t|                               |\n";
                cout << "\t\t|          0.退    出           |\n";
                cout << "\t\t|                               |\n";
                cout << "\t\t -------------------------------\n";
                cout << "输入您的选择: ";

                cin >> select; //接受用户选择

                switch (select)
                {
                case 1:  //学生身份
                    //LoginIn(STUDENT_FILE, 1);
                    LoginIn(connector, 1);
                    break;
                case 2:  //老师身份
                    //LoginIn(TEACHER_FILE, 2);
                    LoginIn(connector, 2);
                    break;
                case 3:  //管理员身份
                    //LoginIn(ADMIN_FILE, 3);
                    LoginIn(connector, 3);
                    break;
                case 0:  //退出系统
                    cout << "欢迎下一次使用" << endl;
                    goto end;
                    break;
                default:
                    cout << "输入有误，请重新选择！" << endl;
                    system("pause");
                    system("cls");
                    break;
                }
            }
        }
        end:
        // 断开连接
        connector.Close();
    }
    catch (const std::exception& e) 
    {
        cerr << "Error: " << e.what() << endl;
    }


    system("pause");
	return 0;
}

/*
测试数据库代码
            // 连接成功，执行数据库操作

            // 创建记录
            if (connector.CreateRecord("students", "name", "John"))
            {
                cout << "记录创建成功" << endl;
            }
            else
            {
                cout << "记录创建失败" << endl;
            }

            // 更新记录
            if (connector.UpdateRecord("students", "name", "Alice", "id = 1"))
            {
                cout << "记录更新成功" << endl;
            }
            else
            {
                cout << "记录更新失败" << endl;
            }

            // 删除记录
            if (connector.DeleteRecord("students", "id = 2"))
            {
                cout << "记录删除成功" << endl;
            }
            else
            {
                cout << "记录删除失败" << endl;
            }

            // 执行查询
            string query = "SELECT * FROM students WHERE id > 2";
            MYSQL_RES* result = connector.GetQueryResult(query);

            if (result)
            {
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(result)))
                {
                    cout << "ID: " << row[0] << ", Name: " << row[1] << ", Email: ";

                    if (row[2] != nullptr)
                    {
                        cout << row[2];
                    }
                    else
                    {
                        cout << "NULL";
                    }
                    cout << endl;

                }
                mysql_free_result(result);
            }
            else
            {
                cout << "查询失败" << endl;
            }
*/