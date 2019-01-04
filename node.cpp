#include "node.h"
#include<cstdlib>
#include "player.h"

void NodeChance::StopAction(Player* pPlayer)
{
	cout << "++++++++++++++Chance++++++++++++++" << endl;
	cout << pPlayer->GetName() << "扣钱500!" << endl;
	if (!pPlayer->ReduceMoney(500))
	{
		pPlayer->GameOver();
	}
}

Player* NodeEstate::GetPlayerByOwnerId()
{
	for (int i = 0;i < g_Players.size();i++)
		if (this->GetOwnerId() == g_Players[i]->GetId())
			return g_Players[i];
	return nullptr;
}

bool NodeEstate::BeBought(Player* pPlayer)
{
	if (pPlayer->GetMoney() > this->GetBuyCost())
	{
		pPlayer->ReduceMoney(this->GetBuyCost());
		this->SetOwnerId(pPlayer->GetId());
		return true;
	}
	else
	{
		cout << "你没有足够的现金!" << endl;
		return false;
	}
}

void NodeEstate::StopAction(Player* pPlayer)
{
	Player* pOwner = this->GetPlayerByOwnerId();

	if (pOwner == nullptr)		//无主之地询问是否购买
	{
		cout<<"是否购买此地？价格："<<this->GetBuyCost()<<"y/n"<<endl;		//todo 以后修改询问方式
		char flag;
		cin >> flag;
		if (flag == 'y')
			this->BeBought(pPlayer);
		return;
	}

	if (pOwner == pPlayer)		//是自己的地，询问造房子。
	{
		cout <<pPlayer->GetName()<< "，这是你自己的地盘." << endl;
		if (this->GetCostLevel() < 3)
		{
			cout << "当前房屋等级为：" << this->GetCostLevel() << "，你是否加盖房屋?y/n" << endl;
			char flag;
			cin >> flag;
			if (flag == 'y')
			{
				if (pPlayer->GetMoney() < this->GetBuildCost())
				{
					cout << "你没有足够的现金!" << endl;
					return;
				}
				else
				{
					this->Build();
					pPlayer->ReduceMoney(this->GetBuildCost());
					return;
				}
			}
			//选n就返回
			return;
		}
		//自己的地盘上，满级房子也返回
		return;
	}

	//跑到别人地盘上了，要付钱
	int Cost = this->GetCost();
	int GetNum = pPlayer->ReduceMoney(Cost);
	pOwner->AddMoney(GetNum);
	pPlayer->CheckLose();
	return;
	//2018.12.31处理完毕人走到普通格子上的情况。接下来处理地图构建，以及处理人走格子的过程。
}

void NodeStart::PassAction(Player* pPlayer)
{
	pPlayer->AddMoney(PASS_STAET_MONEY);
	cout << pPlayer->GetName() << "经过起点," << "增加现金" << PASS_STAET_MONEY << "元!" << endl;
}