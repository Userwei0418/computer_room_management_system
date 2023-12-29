#include "orderFile.h"

/*
date:2023-10-5 intervals:2 stuId:2022001 stuName:张三 roomId:2 status:1
对于这样一条记录 可以将date:2023-10-5作为一对  intervals:2作为一对 ……
然后就能存放在一个 
	以date、intervals、stuId……为key
	以2023-10-5、2、2022001 为value
	的键值对里面 date:2023-10-5为一对 intervals:2作为一对 合起来就是一个map<string,string>
然而这只是针对一条记录 还有n条
需要把这n个map<string,string>存起来
可以用记录数为key 以map<string,string>为value
组成 map<int,map<string,stirng>>
*/

orderFile::orderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;      //日期
	string intervals;  //时间段
	string stuId;     //学生编号
	string stuName;   //学生姓名
	string roomId;    //机房编号
	string status;    //预约状态


	this->m_Size = 0; //预约记录个数

	while (ifs >> date && ifs >> intervals && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		//当前是取到了每一条的每一对 还没拆开来
		
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
{//把一开始从文件取出来的记录 加上新记录 然后重新写进文件 本质是重写 不算添加
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

