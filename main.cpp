/*
ʹ�����ļ���д������mysql���ݿ����ַ�ʽ �����ǰ����������ķ�ʽ �Ѹ���ģ���װ����
���Ƕ���˽�й��е�û�п���ǿ�� ���Ʒ��
���ļ�����⼸���˵���ȫ�ֺ���Ӧ��Ҳ�ܷ�װ���� �Ժ��ٿ���
����Ķ�mysql��һ����װ�ܹؼ� 
���˲���goto ��Ȼ˵��ñ��� �����������������ѭ����ĺܹ��á���
ò��û��ʲô�߼��ϵ����� �ͼ򵥵����������ת���������
�ѶȲ��� �о�һֱ�������������� �о����ܷ�װ�ܶຯ�� ʡ�ܶಽ��
�������mysql����� �ѵ�ÿ���������˾͵�����д�ӿ��� ̫�鷳�˰� 
Ϊʲôû�˰����ģ������������
����˵c++������������ �������Ի᷽��ܶ�
��
���������ż���ЩeasyX�Ķ�����ȥ��
���Ѿ���������12Сʱ�� ��Щ���� ���˰� ���ֶ��������Լ��ֶ��������ꡭ��
��֪��qt����ʲô��
��������
*/

/*
mysql��ʹ�����³�ʼ����

create database ����ԤԼϵͳ;
use ����ԤԼϵͳ;
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

//�����ַ�ʽʵ�� �ӿ���main��case����

//57~288Ϊ�ļ���д�ķ�ʽʵ��
//����ѧ���Ӳ˵�����
void studentMenu(Identity*& student)
{
    while (true)
    {
        student->operMenu();
        Student* stu = (Student*)student;
        int select = 0;

SELECT:
        cin >> select;
        if (select == 1)//����ԤԼ
        {
            cout << "����ԤԼ" << endl;
            stu->applyOrder();
        }
        else if (select == 2)//�鿴����ԤԼ
        {
            cout << "�鿴����ԤԼ" << endl;
            stu->showMyOrder();
        }
        else if (select == 3)//�鿴����ԤԼ
        {
            cout << "�鿴����ԤԼ" << endl;
            stu->showAllOrder();
        }
        else if (select == 4)//ȡ��ԤԼ
        {
            cout << "ȡ��ԤԼ" << endl;
            stu->cancelOrder();
        }
        else if (select == 0)
        {
            delete student;
            cout << "ע���ɹ�" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "�������� ����������" << endl;
            goto SELECT;
        }
    }
}

//�����ʦ�Ӳ˵�����
void teacherMenu(Identity*& teacher)
{
    while (true)
    {
        teacher->operMenu();
        Teacher* tea = (Teacher*)teacher;
        int select = 0;

SELECT:
        cin >> select;
        if (select == 1)//�鿴����ԤԼ  
        {
            cout << "�鿴����ԤԼ" << endl;
            tea->showAllOrder();
        }
        else if (select == 2)//���ԤԼ
        {
            cout << "���ԤԼ" << endl;
            tea->validOrder();
        }
        else if (select == 0)
        {
            delete teacher;
            cout << "ע���ɹ�" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "�������� ����������" << endl;
            goto SELECT;
        }
    }
}

//�������Ա�Ӳ˵�
void managerMenu(Identity*& manager)
{
    while (true)
    {
        //���ù���Ա�Ӳ˵�
        manager->operMenu();
        Manager* man = (Manager*)manager;
        int select = 0;
  
SELECT:
        cin >> select;
        if (select == 1)//����˺�
        {
            cout << "����˺�" << endl;
            man->addPerson();
        }
        else if (select == 2)//�鿴�˺�
        {
            cout << "�鿴�˺�" << endl;
            man->showPerson();
        } 
        else if (select == 3)//�鿴����
        {
            cout << "�鿴����" << endl;
            man->showComputer();
        }
        else if (select == 4)//���ԤԼ
        {
            cout << "���ԤԼ" << endl;
            man->cleanFile();
        }
        else if (select == 0)
        {
            delete manager;
            cout << "ע���ɹ�" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "�������� ����������" << endl;
            goto SELECT;
        }
    }
}

//ʹ���ļ���д
void LoginIn(string FileName, int type)
{//                 �ļ���     �������
    Identity* person = NULL;//����ָ�� ����ָ���������

    //���ļ�
    ifstream ifs;
    ifs.open(FileName, ios::in);

    if (!ifs.is_open())
    {
        cout << "�ļ�������" << endl;
        ifs.close();
        return;
    }

    //׼��������Ϣ
    int id = 0;
    string name;
    string pwd;

    if (type == 1)
    {
        cout << "���������ѧ��" << endl;
        cin >> id;
    }
    else if (type == 2)
    {
        cout << "���������ְ����" << endl;
        cin >> id;
    }

    cout << "�������û����� " << endl;
    cin >> name;

    cout << "���������룺 " << endl;
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
                cout << "ѧ����֤����ɹ���" << endl;
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
                cout << "��ʦ��֤����ɹ���" << endl;
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
                cout << "����Ա��֤����ɹ���" << endl;
                system("pause");
                system("cls");
                person = new Manager(name, pwd);

                managerMenu(person);
                return;
            }
        }
    }

    cout << "��֤����ʧ�ܣ�" << endl;
    system("pause");
    system("cls");
}


//291~548Ϊmysqlʵ��
//ʹ��mysql
//����Ա�˵�
void managerMenu(Identity*& manager, Mysql_Connect& connector)
{
    while (true)
    {
        //���ù���Ա�Ӳ˵�
        manager->operMenu();
        Manager* man = (Manager*)manager;
        int select = 0;

SELECT:
        cin >> select;
        if (select == 1)//����˺�
        {
            cout << "����˺�" << endl;
            man->addPerson(connector);
        }
        else if (select == 2)//�鿴�˺�
        {
            cout << "�鿴�˺�" << endl;
            man->showPerson(connector);
        }
        else if (select == 3)//�鿴����
        {
            cout << "�鿴����" << endl;
            man->showComputer(connector);
        }
        else if (select == 4)//���ԤԼ
        {
            cout << "���ԤԼ" << endl;
            man->cleanFile(connector);
        }
        else if (select == 0)
        {
            delete manager;
            cout << "ע���ɹ�" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "�������� ����������" << endl;
            goto SELECT;
        }
    }
}

//ѧ���˵�
void studentMenu(Identity*& student, Mysql_Connect& connector)
{
    while (true)
    {
        student->operMenu();
        Student* stu = (Student*)student;
        int select = 0;

    SELECT:
        cin >> select;
        if (select == 1)//����ԤԼ
        {
            cout << "����ԤԼ" << endl;
            stu->applyOrder(connector);
        }
        else if (select == 2)//�鿴����ԤԼ
        {
            cout << "�鿴����ԤԼ" << endl;
            stu->showMyOrder(connector);
        }
        else if (select == 3)//�鿴����ԤԼ
        {
            cout << "�鿴����ԤԼ" << endl;
            stu->showAllOrder(connector);
        }
        else if (select == 4)//ȡ��ԤԼ
        {
            cout << "ȡ��ԤԼ" << endl;
            stu->cancelOrder(connector);
        }
        else if (select == 0)
        {
            delete student;
            cout << "ע���ɹ�" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "�������� ����������" << endl;
            goto SELECT;
        }
    }
}

//�����ʦ�Ӳ˵�����
void teacherMenu(Identity*& teacher, Mysql_Connect& connector)
{
    while (true)
    {
        teacher->operMenu();
        Teacher* tea = (Teacher*)teacher;
        int select = 0;

    SELECT:
        cin >> select;
        if (select == 1)//�鿴����ԤԼ  
        {
            cout << "�鿴����ԤԼ" << endl;
            tea->showAllOrder(connector);
        }
        else if (select == 2)//���ԤԼ
        {
            cout << "���ԤԼ" << endl;
            tea->validOrder(connector);
        }
        else if (select == 0)
        {
            delete teacher;
            cout << "ע���ɹ�" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "�������� ����������" << endl;
            goto SELECT;
        }
    }
}

void LoginIn(Mysql_Connect& connector, int type)
{
    Identity* person = NULL;//����ָ�� ����ָ���������

    //׼��������Ϣ
    int id;
    string name;
    string pwd;

    if (type == 1)
    {
        cout << "���������ѧ��" << endl;
        cin >> id;

    }
    else if (type == 2)
    {
        cout << "���������ְ����" << endl;
        cin >> id;

    }

    cout << "�������û����� " << endl;
    cin >> name;

    cout << "���������룺 " << endl;
    cin >> pwd;


    if (type == 1)
    {
        string query = "SELECT * FROM students WHERE id=" + to_string(id);
        MYSQL_RES* result = connector.GetQueryResult(query);

        if (result)
        {
            //cout << "��ѯ�ɹ���" << endl;
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result)))
            {
                if (row[0] == to_string(id) && row[1] == name && row[2] == pwd)
                {
                    cout << "ѧ����֤����ɹ���" << endl;
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
            cout << "��ѯʧ��" << endl;
        }
    }
    else if (type == 2)
    {
        string query = "SELECT * FROM teachers WHERE id=" + to_string(id);
        MYSQL_RES* result = connector.GetQueryResult(query);

        if (result)
        {
            //cout << "��ѯ�ɹ���" << endl;
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result)))
            {
                if (row[0] == to_string(id) && row[1] == name && row[2] == pwd)
                {
                    cout << "��ʦ��֤����ɹ���" << endl;
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
            cout << "��ѯʧ��" << endl;
        }
    }
    else if (type == 3)
    {
        string query = "SELECT * FROM managers";
        MYSQL_RES* result = connector.GetQueryResult(query);

        if (result)
        {
            //cout << "��ѯ�ɹ���" << endl;
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result)))
            {
                if (row[0] == name && row[1] == pwd)
                {
                    cout << "����Ա��֤����ɹ���" << endl;
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
            cout << "��ѯʧ��" << endl;
        }
    }

    cout << "��֤����ʧ�ܣ�" << endl;
    system("pause");
    system("cls");
}


int main()
{
    try 
    {
        // �������ݿ�����
        Mysql_Connect connector("localhost", "root", "zw200495", "����ԤԼϵͳ");
        
        if (connector.Connect()) 
        {
            system("cls");
            int select = 0;

            while (true)
            {
                cout << "======================  ��ӭ��������ԤԼϵͳ  ====================="<< endl;
                cout << endl << "�������������" << endl;
                cout << "\t\t -------------------------------\n";
                cout << "\t\t|                               |\n";
                cout << "\t\t|          1.ѧ������           |\n";
                cout << "\t\t|                               |\n";
                cout << "\t\t|          2.��    ʦ           |\n";
                cout << "\t\t|                               |\n";
                cout << "\t\t|          3.�� �� Ա           |\n";
                cout << "\t\t|                               |\n";
                cout << "\t\t|          0.��    ��           |\n";
                cout << "\t\t|                               |\n";
                cout << "\t\t -------------------------------\n";
                cout << "��������ѡ��: ";

                cin >> select; //�����û�ѡ��

                switch (select)
                {
                case 1:  //ѧ�����
                    //LoginIn(STUDENT_FILE, 1);
                    LoginIn(connector, 1);
                    break;
                case 2:  //��ʦ���
                    //LoginIn(TEACHER_FILE, 2);
                    LoginIn(connector, 2);
                    break;
                case 3:  //����Ա���
                    //LoginIn(ADMIN_FILE, 3);
                    LoginIn(connector, 3);
                    break;
                case 0:  //�˳�ϵͳ
                    cout << "��ӭ��һ��ʹ��" << endl;
                    goto end;
                    break;
                default:
                    cout << "��������������ѡ��" << endl;
                    system("pause");
                    system("cls");
                    break;
                }
            }
        }
        end:
        // �Ͽ�����
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
�������ݿ����
            // ���ӳɹ���ִ�����ݿ����

            // ������¼
            if (connector.CreateRecord("students", "name", "John"))
            {
                cout << "��¼�����ɹ�" << endl;
            }
            else
            {
                cout << "��¼����ʧ��" << endl;
            }

            // ���¼�¼
            if (connector.UpdateRecord("students", "name", "Alice", "id = 1"))
            {
                cout << "��¼���³ɹ�" << endl;
            }
            else
            {
                cout << "��¼����ʧ��" << endl;
            }

            // ɾ����¼
            if (connector.DeleteRecord("students", "id = 2"))
            {
                cout << "��¼ɾ���ɹ�" << endl;
            }
            else
            {
                cout << "��¼ɾ��ʧ��" << endl;
            }

            // ִ�в�ѯ
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
                cout << "��ѯʧ��" << endl;
            }
*/