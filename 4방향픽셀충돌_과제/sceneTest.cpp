#include "stdafx.h"
#include "sceneTest.h"


HRESULT sceneTest::init(void)
{
	//��׶��� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addImage("��׶���", "background.bmp", WINSIZEX, WINSIZEY);

	//UFO ������ �̹��� �ʱ�ȭ
	IMAGEMANAGER->addFrameImage("ufo", "ufo.bmp", 530, 32, 10, 1);

	//�Ѿ� �̹���
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));


	//�÷��̾� Ŭ���� ������ �ʱ�ȭ
	_player = new player;
	_player->init();

	//���Ŵ��� Ŭ���� ���� �� �ʱ�ȭ
	_enemyManager = new enemyManager;
	_enemyManager->init();

	//��ȣ������ ������ ��ũ�ϱ�
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	return S_OK;
}

void sceneTest::release(void)
{
	//�̹��� Ŭ������ ���������� ����� �� ����
	//�����Ҵ� new�� ����ߴٸ� �̰����� SAFE_DELETE() ����Ѵ�
	//_bgImage->release();
	//SAFE_DELETE(_bgImage);
	//�̹��� �Ŵ��� ���� �Ŵ����� �˾Ƽ� ���� ���ִϱ�
	//SAFE_DELETE() �� ����� �ʿ䰡 ����

	//�÷��̾� Ŭ���� ����
	_player->release();
	SAFE_DELETE(_player);

	//���Ŵ��� Ŭ���� ����
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
}

void sceneTest::update(void)
{
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	//�����ϰ� �̰����� �ڵ��Ѵٰ� �����ϸ� �ȴ�

	//�÷��̾� Ŭ���� ������Ʈ
	_player->update();

	//���Ŵ��� Ŭ���� ������Ʈ
	_enemyManager->update();

	//�浹�Լ�
	//this->collision();

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->loadScene("�ȼ��浹");
	}
}

void sceneTest::render(void)
{
	//�̰����� WM_PAINT���� �ߴ����� ó���ϸ� �ȴ�

	//��׶��� �̹��� ����
	IMAGEMANAGER->render("��׶���", getMemDC());

	//�÷��̾� Ŭ���� ����
	_player->render();

	//���Ŵ��� Ŭ���� ����
	_enemyManager->render();
}

void sceneTest::collision()
{
	//�浹ó��
	//�÷��̾��� �Ѿ� & �� => �浹ó��
	//�÷��̾�� �Ѿ�Ŭ���� �����´�
	//�Ѿ�Ŭ�������� �Ѿ˺��� �����´�
	//�÷��̾�->�̻���Ŭ����->�Ѿ˺���[]
	//for (int i = 0; i < _player->getMissileM1()->getVBullet().size(); i++)
	//{
	//	
	//}

	//���ʹ�Ŭ�������� �Ѿ�Ŭ������ ������
	//���ʹ̸Ŵ���->���ʹ�Ŭ����->�Ѿ�Ŭ����->�Ѿ˺���
	//���ʹ̸Ŵ������� �Ѿ�Ŭ������ ��� ������
	//���ʹ̸Ŵ���->�Ѿ�Ŭ����->�Ѿ˺���

	//�÷��̾� �Ѿ� M1 vs �̴Ͼ� �浹ó��
	for (int i = 0; i < _player->getMissileM1()->getVBullet().size(); i++) //�÷��̾ �� �Ѿ�
	{
		//�̴Ͼ�
		for (int j = 0; j < _enemyManager->getMinion().size(); j++)//��Ŭ����
		{
			//�浹�߳�?
			RECT rc;
			if (IntersectRect(&rc, &_player->getMissileM1()->getVBullet()[i].rc,
				&_enemyManager->getMinion()[j]->getRect()))
			{
				//�÷��̾� �Ѿ� ����
				_player->removeMissileM1(i);
				//�̴Ͼ� ����
				_enemyManager->removeMinion(j);

				//������
				//SCENEMANAGER->loadScene("Ű��");
				break;
			}
		}
	}

}