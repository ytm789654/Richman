#ifndef __NODE__
#define __NODE__
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define PASS_STAET_MONEY 1000
class Player;		//用了Player指针，所以要声明一下

class NodeBase
{
public:
	NodeBase()
	{
		m_next = nullptr;
	}
	virtual ~NodeBase()
	{
		
	}

	void SetNextNode(NodeBase* _next)
	{
		m_next = _next;
	}

	NodeBase* GetNextNode()
	{
		return m_next;
	}

	virtual void StopAction(Player *pPlayer)	//停在这个点的事件
	{
		cout<<"Nothing when Stop!"<<endl;	
	}	

	virtual void PassAction(Player *pPlayer)	//路过这个点的事件
	{
		cout<<"Nothing when Pass!"<<endl;
	} 

	//输出节点信息，调试用
	virtual void NodeDump()
	{
		cout << "This is a base node..." << endl;
	}
private:
	NodeBase * m_next;
};

class NodeChance:public NodeBase
{
public:
	NodeChance()
	:NodeBase()
	{
		
	}
	~NodeChance()
	{
		cout << "NodeChance delete...." << endl;
	}
	void NodeDump()
	{
		cout << "NodeChance..." << endl;
	}
	void StopAction(Player *pPlayer);
};

class NodeEstate:public NodeBase	//可以买卖的Node
{
public: 
	NodeEstate(string _Name,int _BuyCost,vector<int> _Earn,  int _BuildCost = 1500, int _Level = 0)
	:NodeBase(),m_Name(_Name),m_BuyCost(_BuyCost),m_OwnerID(-1),m_Level(_Level),m_BuildCost(_BuildCost)
	{
		for (int i = 0;i < 4;i++)
		{
			m_Earn[i] = _Earn[i];
		}
	}
	~NodeEstate()
	{
		cout << "节点" << m_Name << "析构完成................" << endl;
	}
	int GetOwnerId()
	{
		return m_OwnerID;
	}
	int GetCostLevel()
	{
		return m_Level;
	}

	int GetCost()
	{
		return m_Earn[GetCostLevel()];
	}

	int GetBuyCost()
	{
		return m_BuyCost;
	}

	void SetNodeNoOwner()
	{
		SetOwnerId(-1);
		cout <<m_Name << "现在已经是无主之地了" << endl;
	}

	void SetOwnerId(int _OwnerId)
	{
		m_OwnerID = _OwnerId;
	}

	int GetBuildCost()
	{
		return m_BuildCost;
	}
	
	bool Build()
	{
		if (m_Level < 3)
		{
			AddCostLevel();
			return true;
		}
		else
		{
			cout << "未知错误!" << endl;
			return false;
		}
	}

	void AddCostLevel()
	{
		m_Level++;
	}
	bool BeBought(Player* pPlayer);
	Player* GetPlayerByOwnerId();
	void StopAction(Player *pPlayer);

	void NodeDump()
	{
		cout << "输出节点" << m_Name << " 信息:" << endl;
		cout << "节点名称:" << m_Name << endl;
		cout << "购买费用:" << m_BuyCost << endl;
		cout << "收入:" << m_Earn[0] << " " << m_Earn[1] << " " << m_Earn[2] << " " << m_Earn[3] << endl;
		cout << "建造费用:" << m_BuildCost << endl;
	}
;
private:
	int m_OwnerID;	//所有者ID
	string m_Name;	//土地的名称
	int m_BuyCost;		//购买费用
	int m_Earn[4];		//别人停留收取费用
	int m_Level;			//房屋等级
	int m_BuildCost;	//建造费用
};

class NodeStart :public NodeBase
{
public:
	NodeStart()
		:NodeBase()
	{

	}
	~NodeStart()
	{
		cout << "开始节点析构完成" << endl;
	}
	void NodeDump()
	{
		cout << "这只是一个开始节点..." << endl;
	}
	void PassAction(Player* pPlayer);
};
#endif
