#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init(void)
{
	//미니언 생성 ex)//보스 생성, 일반몬스터 생성
	//따로 함수로 빼서 처리하면 보기에 편하다

	//미니언 생성
	this->setMinion();

	_count = 0;

	//총알 클래스 생성 및 초기화
	_bullet = new bullet;
	_bullet->init("bullet", 15, 600);

	return S_OK;
}

void enemyManager::release(void)
{
	//총알클래스 삭제
	_bullet->release();
	SAFE_DELETE(_bullet);
}

void enemyManager::update(void)
{
	//총알클래스 업데이트
	_bullet->update();

	//벡터에 담긴 미니언들 업데이트
	for (int i = 0; i < _vMinion.size(); i++)
	{
		_vMinion[i]->update();
	}

	//미니언 총알발사
	this->minionBulletFire();

	this->collision();
}

void enemyManager::render(void)
{
	//총알클래스 렌더
	_bullet->render();
	
	//벡터에 담긴 미니언들 렌더
	for (int i = 0; i < _vMinion.size(); i++)
	{
		_vMinion[i]->render();
	}
}

void enemyManager::setMinion()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			enemy* ufo = new minion;
			ufo->init("ufo", PointMake(50 + j * 100, 100 + i * 100));

			_vMinion.push_back(ufo);
		}
	}
}

void enemyManager::minionBulletFire()
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 30, -PI_2, 3.0f);
		}
	}

	//int a = 10;
	//int* p = &a;
	//cout << p << endl;
	//cout << *p << endl;
}

void enemyManager::removeMinion(int index)
{
	_vMinion.erase(_vMinion.begin() + index);
}


//충돌처리 (공용총알, 플레이어)
void enemyManager::collision()
{
	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_bullet->getVBullet()[i].rc,
			&_player->getPlayerImg()->boudingBox()))
		{
			//공용총알 삭제
			_bullet->removeBullet(i);
			//플레이어 체력바 피통깍기
			_player->hitDamage(10);
			break;
		}
	}

}
