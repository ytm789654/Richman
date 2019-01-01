#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "node.h"
using namespace std;

class Player
{
public:
	static int UsedId;
	Player(int _Money, string _Name, bool _State = true)
		:m_Money(_Money),m_Name(_Name),m_State(_State)
	{
		m_Id = UsedId++;
		cout << "Player:" << m_Name << " created!" << endl;
	}
	string GetName()
	{
		return m_Name;
	}
	int GetMoney()
	{
		return m_Money;
	}

	void SetMoney(int Num)
	{
		if (Num < 0)	return;
		m_Money = Num;
	}

	void AddMoney(int Num)
	{
		if (Num < 0)
			return;
		m_Money += Num;
	}

	bool CheckLose()		//返回false表示失败
	{
		m_State = ! (m_Money <= 0);
		if (!m_State)
			GameOver();
		return m_State;
	}

	int ReduceMoney(int Num)		//返回实际的减少的值
	{
		if (m_Money < Num)
		{
			int ret = m_Money;
			m_Money = 0;
			return ret;
		}
		else
		{
			m_Money -= Num;
			return Num;
		}
	}

	int GetId()
	{
		return m_Id;
	}

	vector<NodeEstate*> GetEstate()
	{
		return m_VecEstate;
	}

	void GameOver();

private:
	string m_Name;
	int m_Money;
	bool m_State;		//false表示玩家游戏失败
	int m_Id;
	vector<NodeEstate*> m_VecEstate;
};

extern vector<Player*> g_Players;