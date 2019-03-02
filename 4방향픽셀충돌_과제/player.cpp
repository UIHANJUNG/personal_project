#include "stdafx.h"
#include "player.h"
#include "enemyManager.h" //cpp���Ͽ� ������ �� ����� �Ѵ�

HRESULT player::init(void)
{
	//�÷��̾� �̹��� �ʱ�ȭ
	_rocket = IMAGEMANAGER->addImage("rocket", "rocket.bmp", WINSIZEX / 2, WINSIZEY - 100, 52, 64, true, RGB(255, 0, 255));

	//�̻��� Ŭ���� ������ �ʱ�ȭ
	_missile = new missile;
	_missile->init(10, 500);

	//�̻���M1 Ŭ���� ������ �ʱ�ȭ
	_missileM1 = new missileM1;
	_missileM1->init(5, 600);

	//ü�¹� Ŭ���� ������ �ʱ�ȭ
	_hpBar = new progressBar;
	_hpBar->init("progressBarFront", "progressBarBack", _rocket->getX(), _rocket->getY() - 20, 50, 10);
	//���� �ʱ�ȭ
	_maxHp = 100;
	_currentHp = 100;
	_hpBar->setGauge(_currentHp, _maxHp);

	return S_OK;
}

void player::release(void)
{
	//�̻��� Ŭ���� ����
	_missile->release();
	SAFE_DELETE(_missile);
	//�̻��� Ŭ���� ����
	_missileM1->release();
	SAFE_DELETE(_missileM1);
	//ü�¹� Ŭ���� ����
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void player::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rocket->getX() > 0)
	{
		_rocket->setX(_rocket->getX() - 5.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rocket->getX() + _rocket->getWidth() < WINSIZEX)
	{
		_rocket->setX(_rocket->getX() + 5.0f);
	}

	//�Ѿ˹߻�
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//�Ѿ�Ŭ������ �ϲ� �߻���~
		_missile->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}
	//��ź�߻�
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		//�Ѿ�Ŭ������ �ϲ� �߻���~
		_missileM1->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}

	//�̻��� Ŭ���� ������Ʈ
	_missile->update();
	//�̻���M1 Ŭ���� ������Ʈ
	_missileM1->update();

	//�浹ó��
	this->collision();

	//ü�¹� Ŭ���� ������Ʈ
	_hpBar->update();
	//ü�¹ٰ� �÷��̾� �Ӹ����� ����ٴϰ� �����
	_hpBar->setX(_rocket->getX());
	_hpBar->setY(_rocket->getY() - 20);
	_hpBar->setGauge(_currentHp, _maxHp);

	//���̺�ε�
	/*
	//�÷��̾� ��ġ��ǥ, HP
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//ü������
		SAVEDATA->setHp(_currentHp);
		//��ġ��ǥ
		POINT pos; 
		pos.x = _rocket->getX();
		pos.y = _rocket->getY();
		SAVEDATA->setPos(pos);

	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		//ü�·ε�
		_currentHp = SAVEDATA->getHp();
		//��ġ��ǥ �ε�
		_rocket->setX(SAVEDATA->getPos().x);
		_rocket->setY(SAVEDATA->getPos().y);
	}
	*/
	
	//���̺�
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//itoa => ������ ���ڷ�
		char temp[128];
		vector<string> vStr;
		vStr.push_back(itoa(_rocket->getX(), temp, 10));
		vStr.push_back(itoa(_rocket->getY(), temp, 10));
		vStr.push_back(itoa(_currentHp, temp, 10));
		
		TXTDATA->txtSave("save.txt", vStr);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		vector<string> vStr;
		vStr = TXTDATA->txtLoad("save.txt");
		//atoi => ���ڸ� ���ڷ�
		_rocket->setX(atoi(vStr[0].c_str()));
		_rocket->setY(atoi(vStr[1].c_str()));
		_currentHp = (atoi(vStr[2].c_str()));
	}




}

void player::render(void)
{
	//�÷��̾� ����
	_rocket->render(getMemDC(), _rocket->getX(), _rocket->getY());
	
	//�̻��� Ŭ���� ����
	_missile->render();
	//�̻���M1 Ŭ���� ����
	_missileM1->render();
	//ü�¹� Ŭ���� ����
	_hpBar->render();
}

void player::removeMissileM1(int index)
{
	//�̻���M1 �ϰ� �Ѿ� ������~ ���� �ε����� �Ѱ����ٲ�~
	_missileM1->removeMissileM1(index);
}

//�浹�Լ�(�÷���� �Ѿ˵�� ���Ŵ����� �̴Ͼ�)
void player::collision()
{
	for (int i = 0; i < _missileM1->getVBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_missileM1->getVBullet()[i].rc,
				&_em->getMinion()[j]->getRect()))
			{
				_missileM1->removeMissileM1(i);
				_em->removeMinion(j);
				break;
			}
		}
	}
}

void player::hitDamage(float damage)
{
	_currentHp -= damage;
}
