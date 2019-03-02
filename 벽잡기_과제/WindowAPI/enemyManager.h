#pragma once
#include "gameNode.h"
#include "minion.h"		//�̴Ͼ� Ŭ������ ����ϱ� ����
#include "bullet.h"		//�Ѿ� Ŭ������ ����ϱ� ����

//#include "player.h"
//�÷��̾� ��ȣ�����ϱ� ���� Ŭ���� ���漱��
class player;

class enemyManager : public gameNode
{
private:
	vector<enemy*> _vMinion;
	vector<enemy*>::iterator _viMinion;

	bullet* _bullet;		//�����Ѿ� Ŭ����
	int _count;

	player* _player;		//�����Ҵ� �ϸ� �ȵȴ�!!!

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�̴Ͼ� ���� => �ʱ�ȭ�� �ֱ�
	void setMinion();

	//�̴Ͼ� �Ѿ˹߻�
	void minionBulletFire();

	//�̴Ͼ� ����
	void removeMinion(int index);

	//�浹�Լ�
	void collision();

	//�̴Ͼ� ���� ��������
	vector<enemy*> getMinion() { return _vMinion; }

	//��ȣ������ �÷��̾� ������ �ѱ� �����Լ�
	void setPlayerLink(player* player) { _player = player; }

	enemyManager() {}
	~enemyManager() {}
};

