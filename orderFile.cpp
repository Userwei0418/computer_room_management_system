#include "orderFile.h"

/*
date:2023-10-5 intervals:2 stuId:2022001 stuName:���� roomId:2 status:1
��������һ����¼ ���Խ�date:2023-10-5��Ϊһ��  intervals:2��Ϊһ�� ����
Ȼ����ܴ����һ�� 
	��date��intervals��stuId����Ϊkey
	��2023-10-5��2��2022001 Ϊvalue
	�ļ�ֵ������ date:2023-10-5Ϊһ�� intervals:2��Ϊһ�� ����������һ��map<string,string>
Ȼ����ֻ�����һ����¼ ����n��
��Ҫ����n��map<string,string>������
�����ü�¼��Ϊkey ��map<string,string>Ϊvalue
��� map<int,map<string,stirng>>
*/

orderFile::orderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;      //����
	string intervals;  //ʱ���
	string stuId;     //ѧ�����
	string stuName;   //ѧ������
	string roomId;    //�������
	string status;    //ԤԼ״̬


	this->m_Size = 0; //ԤԼ��¼����

	while (ifs >> date && ifs >> intervals && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		//��ǰ��ȡ����ÿһ����ÿһ�� ��û����
		
	/*	cout << date << endl;
		cout << intervals << endl;
		cout << stuId << endl;
		cout << stuName << endl;
		cout << roomId << endl;
		cout << status << endl;*/
		

		string key;
		string value;
		map<string, string> m;

		int pos = date.find(":");
		if (pos != -1)
		{
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = intervals.find(":");
		if (pos != -1)
		{
			key = intervals.substr(0, pos);
			value = intervals.substr(pos + 1, intervals.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = stuId.find(":");
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = stuName.find(":");
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = roomId.find(":");
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}


		this->m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
	}

	/*for (map<int, map<string, string>>::iterator it = m_orderData.begin(); it != m_orderData.end();it++)
	{
		cout << "key = " << it->first << " value = " << endl;
		for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
		{
			cout << mit->first << " " << mit->second << " ";
		}
		cout << endl;
	}*/

	ifs.close();

}

void orderFile::updateOrder()
{//��һ��ʼ���ļ�ȡ�����ļ�¼ �����¼�¼ Ȼ������д���ļ� ��������д �������
	if (this->m_Size == 0)
	{
		return;
	}

	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < m_Size; i++)
	{
		ofs << "date:" << this->m_orderData[i]["date"] << " ";
		ofs << "intervals:" << this->m_orderData[i]["intervals"] << " ";
		ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << endl;
	}
	ofs.close();
}

