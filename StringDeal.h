#pragma once
#include <string>
#include <vector>

using namespace std;

//辅助读取config的字符串，用于处理配置文件中 XXX=YYY的情况。
struct ConfigReadStructs
{
	string VarName;
	string VarValue;
};

/*
	根据字符串中指定字符划分字符串为两截，用于处理配置文件中 XXX=YYY的情况。
	param: 指定分割的字符串，划分的指定字符，划分结果。
	return: true划分成功，false未找到指定字符c
	需要注意的是这里会根据第一个找到的字符c进行划分（string的find函数）
*/
bool SplitStringByChar(const string&str, const char c, ConfigReadStructs &ret)
{
	size_t pos = str.find(c);
	if (pos != str.npos)
	{
		ret.VarName = str.substr(0, pos);
		ret.VarValue = str.substr(pos + 1);
		return true;
	}
	return false;
}

//warnig!!!!! 这个函数没有对输入做检查，请务必保证输入的合理性！
vector<int> StringToVecInt(const string str)
{
	string Input = str;
	vector<int> ret;
	size_t pos=Input.find(' ');
	while (pos != Input.npos)
	{
		ret.push_back(atoi (Input.substr(0, pos).c_str() ) );
		Input = Input.substr(pos + 1);
		pos = Input.find(' ');
	}
	ret.push_back( atoi(Input.c_str())   );
	return ret;
}