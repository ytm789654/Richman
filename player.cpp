#include "player.h"
#include "node.h"

void Player::GameOver()
{
	cout << this->GetName() << "�Ʋ����˳���Ϸ��" << endl;
	vector<NodeEstate*> VecEstate = this->GetEstate();
	for (int i = 0;i < VecEstate.size();i++)
		VecEstate[i]->SetNodeNoOwner();
	/*						
	������Ҫ�۲�һ���ǲ���Ҫ��g_Playersɾ����ͬʱɾ����ʱ��Ҫ��Ҫdelete
	delete���ܻ���Ұָ�롣��delete���ܻ�й¶������Ҫ�ڱ�ĵط�delete��
	����˵����Ϸ������ʱ�����ͳһ�ͷ��ڴ档						
	vector<Player*>::iterator iter;
	for (iter=g_Players.begin();iter!=g_Players.end();++iter)
	{
		if ( (*iter)->GetId() == this->GetId())
			g_Players.erase(iter);
		return;
	}
	cout<<"ȫ��ɾ��Player����"
	*/
}