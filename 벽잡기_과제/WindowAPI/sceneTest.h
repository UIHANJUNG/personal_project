#pragma once
#include "gameNode.h"
#include "player.h" //�÷��̾� Ŭ���� ����ϱ� ����
#include "enemyManager.h" //���Ŵ��� Ŭ���� ����ϱ� ����

class sceneTest : public gameNode
{
private:
	player* _player;				//�÷��̾� Ŭ���� ����
	enemyManager* _enemyManager;	//���Ŵ��� Ŭ���� ����

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	//�浹�Լ�
	void collision();

	sceneTest() {}
	~sceneTest() {}
};

