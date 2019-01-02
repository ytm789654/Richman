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
		next = nullptr;
	}
	virtual ~NodeBase()
	{
		
	}
	virtual void StopAction(Player *pPlayer)	//停在这个点的事件
	{
		cout<<"Nothing when Stop!"<<endl;	
	}	
	virtual void PassAction(Player *pPlayer)	//路过这个点的事件
	{
		cout<<"Nothing when Pass!"<<endl;
	} 
private:
	NodeBase * next;
};

class NodeChance:public NodeBase
{
public:
	NodeChance()
	:NodeBase()
	{
		
	}
	void StopAction(Player *pPlayer);
};

class NodeEstate:public NodeBase	//可以买卖的Node
{
public: 
	NodeEstate(int _BuyCost,int _cost0,int _cost1,int _cost2,int _cost3,int _Level = 0,int _BuildCost = 1500)
	:NodeBase(),m_OwnerID(-1),m_Level(_Level),m_BuildCost(_BuildCost)
	{
		m_Earn[0] = _cost0;
		m_Earn[1] = _cost1;
		m_Earn[2] = _cost2;
		m_Earn[3] = _cost3;
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
	void PassAction(Player* pPlayer);
};
#endif
