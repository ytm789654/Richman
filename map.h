#pragma once
#include "node.h"
#include <iostream>
#include <fstream>

using namespace std;

class map
{
public:
	map()
	{

	}
	~map()
	{

	}
	void InitMapFromFile(const string& path)
	{
		ifstream FILE;
		FILE.open(path.c_str(), ios::in);
		if (!FILE.is_open())
		{
			cout << "文件打开错误！" << endl;
			return;
		}
	}
private:
	string name;
	int NodeCount;
	NodeBase* StartNode;
};