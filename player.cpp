#include "player.h"
#include "node.h"

vector<Player*> g_Players;

void Player::GameOver()
{
	cout << this->GetName() << "破产，退出游戏！" << endl;
	vector<NodeEstate*> VecEstate = this->GetEstate();
	for (size_t i = 0;i < VecEstate.size();i++)
		VecEstate[i]->SetNodeNoOwner();
	/*						
	这里需要观察一下是不是要从g_Players删掉，同时删掉的时候要不要delete
	delete可能会有野指针。不delete可能会泄露，可能要在别的地方delete。
	或者说在游戏结束的时候才来统一释放内存。						
	vector<Player*>::iterator iter;
	for (iter=g_Players.begin();iter!=g_Players.end();++iter)
	{
		if ( (*iter)->GetId() == this->GetId())
			g_Players.erase(iter);
		return;
	}
	cout<<"全局删除Player错误！"
	*/
}