#pragma once
#include "node.h"
#include "StringDeal.h"
#include <iostream>
#include <fstream>

using namespace std;

class GameMap
{
public:
	GameMap()
	{

	}
	~GameMap()
	{
		NodeBase *p = mp_StartNode;
		NodeBase *q = p;
		for (int i = 0;i < m_NodeCount;i++)
		{
			q = p->GetNextNode();
			delete p;
			p = q;
		}
	}
	
	bool ReadConfigString(string &result,const string& ConfigName,const string& err)
	{
		string InputString;
		if (getline(m_FILE,InputString))
		{
			ConfigReadStructs tmpInfo;
			SplitStringByChar(InputString,'=',tmpInfo);
			if (tmpInfo.VarName!=ConfigName)
			{
				cout<<err<<endl;
				return false;	
			}
			result = tmpInfo.VarValue;
			return true;
		}
		else
		{
			cout<<"地图配置格式错误!"<<endl;
			return false;			
		}		
	}
	
	bool ReadConfigInt(int& result,const string &ConfigName,const string& err)
	{
		string InputString;
		if (getline(m_FILE,InputString))
		{
			ConfigReadStructs tmpInfo;
			SplitStringByChar(InputString,'=',tmpInfo);
			if (tmpInfo.VarName!=ConfigName)
			{
				cout<<err<<endl;
				return false;	
			}
			result = atoi(tmpInfo.VarValue.c_str());
			return true;
		}
		else
		{
			cout<<"地图配置格式错误!"<<endl;
			return false;			
		}			
	}
	
	bool ReadConfigIntVec(vector<int>& result,const string &ConfigName, const string& err)
	{
		string InputString;
		if (getline(m_FILE,InputString))
		{
			ConfigReadStructs tmpInfo;
			SplitStringByChar(InputString,'=',tmpInfo);
			if (tmpInfo.VarName!=ConfigName)
			{
				cout<<err<<endl;
				return false;	
			}
			//todo 在stringdeal.h里边写一个string转vector<int>的函数 StringToVecInt
			result = StringToVecInt(tmpInfo.VarValue);
			if (result.size() != 4)
			{
				cout << "地图配置文件错误:节点收入配置错误!" << endl;
				return false;
			}
			return true;
		}
		else
		{
			cout<<"地图配置格式错误!"<<endl;
			return false;
		}
	} 
	
	bool ReadMapName()
	{
		return ReadConfigString(m_Name,"MAPNAME","地图配置错误:地图名称配置错误!");
	}
	
	bool ReadNodeCount()
	{
		return ReadConfigInt(m_NodeCount,"NODECOUNT","地图配置错误:地图节点数量配置错误!");	
	}
		
	bool ReadEstateNode()
	{
		string NodeName;
		if(!ReadConfigString(NodeName,"NODENAME","地图配置错误:节点名称配置错误!"))
			return false;
		int NodeBuyCost;						  
		if(!ReadConfigInt(NodeBuyCost,"NODEBUYCOST","地图配置错误:节点购买价格配置错误!"))
			return false;
		vector<int>  EarnInfo;
		if(!ReadConfigIntVec(EarnInfo,"NODEEARN","地图配置错误:节点收入配置错误!"))
			return false;
		int BuildCost;
		if (!ReadConfigInt(BuildCost, "NODEBUILDCOST", "地图配置错误:节点建造价格配置错误!"))
			return false;
		NodeEstate* NewNode = new NodeEstate(NodeName,NodeBuyCost, EarnInfo, BuildCost);
		LastNode->SetNextNode(NewNode);
		LastNode = LastNode->GetNextNode();
		return true;
	}
	
	void InitMapFromFile(const string& path)
	{
		m_FILE.open(path.c_str(), ios::in);
		string InputString;
		if (!m_FILE.is_open())
		{
			cout << "文件打开错误！" << endl;
			return;
		}		
		//读取文件头，地图名称 
		if (!ReadMapName())
			return ;
		//读取文件头，地图节点数量 
		if (!ReadNodeCount())
			return ;
		//过滤空行 
		getline(m_FILE,InputString);	
		//读取各个节点	
		for(int i=0;i<m_NodeCount;i++)
		{
			if(!getline(m_FILE,InputString))
			{
				cout<<"地图配置文件错误,意外的终止!"<<endl;
				return ;	
			} 
			//else
			ConfigReadStructs tmpNodeInfo;
			SplitStringByChar(InputString,'=',tmpNodeInfo);
			if (tmpNodeInfo.VarName !="NODETYPE")
			{
				cout<<"地图配置错误,地图节点配置错误!"<<endl;
				return ;
			}
			//开始节点 
			if (tmpNodeInfo.VarValue == "NODESTART")
			{
				mp_StartNode = new NodeStart();
				LastNode = mp_StartNode;
				//过滤掉空行 
				getline(m_FILE,InputString);
			}
			//地产节点 
			if (tmpNodeInfo.VarValue == "NODEESTATE")
			{
				if (!ReadEstateNode())
					return ;
				//读完信息后过滤掉空行 
				getline(m_FILE, InputString);
			}
		}
		m_FILE.close();
		//把最后一个node指向开始节点
		LastNode->SetNextNode(mp_StartNode);
		return;
	}

	//输出地图信息，调试用
	void DumpMap()
	{
		cout << "输出地图信息:" << endl;
		cout << "地图名称:" <<m_Name << endl;
		cout << "节点数量:" << m_NodeCount << endl;
		cout << "节点信息:" << endl;
		NodeBase *p = mp_StartNode;
		for (int i = 0;i < m_NodeCount;i++)
		{
			p->NodeDump();
			p = p->GetNextNode();
		}
	}

private:
	string m_Name;
	int m_NodeCount;
	NodeBase* mp_StartNode;
	NodeBase* LastNode;
	ifstream m_FILE;
};
