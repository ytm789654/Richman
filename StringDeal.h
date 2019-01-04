#pragma once
#include <string>
#include <vector>

using namespace std;

//������ȡconfig���ַ��������ڴ��������ļ��� XXX=YYY�������
struct ConfigReadStructs
{
	string VarName;
	string VarValue;
};

/*
	�����ַ�����ָ���ַ������ַ���Ϊ���أ����ڴ��������ļ��� XXX=YYY�������
	param: ָ���ָ���ַ��������ֵ�ָ���ַ������ֽ����
	return: true���ֳɹ���falseδ�ҵ�ָ���ַ�c
	��Ҫע������������ݵ�һ���ҵ����ַ�c���л��֣�string��find������
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

//warnig!!!!! �������û�ж���������飬����ر�֤����ĺ����ԣ�
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