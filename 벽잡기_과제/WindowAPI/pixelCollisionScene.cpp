#include "stdafx.h"
#include "pixelCollisionScene.h"

HRESULT pixelCollisionScene::init(void)
{
	//백그라운드 이미지
	_mountain = IMAGEMANAGER->addImage("mountain3", "mountain3.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//공이미지
	_ball = IMAGEMANAGER->addImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));

	//공 위치 초기화
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	//y축으로 탐지(공의 하단에서 검사함)
	_probeY = _y + _ball->getHeight() / 2;

	bool _isjump = false;

	return S_OK;
}

void pixelCollisionScene::release(void)
{
}

void pixelCollisionScene::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 3.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 3.0f;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_isjump = true;
		_y -= 80.0f;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE)) 
	{
		_isjump = false;
	}


	if (_isjump == false) 
	{
		_y += 3.0f;
	}

	//공의 렉트도 움직이기
	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());
	//y축으로 탐지(공의 하단의 작은렉트)
	_probeY = _y + _ball->getHeight() / 2;
	_probeX = _x + _ball->getWidth() / 2;

	/*이부분이 픽셀충돌의 핵심*/
	//탐지할 Y값의 범위를 위아해로 원하는 만큼 검사를 한다
	for (int i = _probeY - 50; i < _probeY + 50; i++)
	{
		COLORREF color = GetPixel(_mountain->getMemDC(), _x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _ball->getHeight() / 2;
			break;
		}
	}

	for (int i = _probeX - 10; i < _probeX + 10; i++)
	{
		COLORREF color = GetPixel(_mountain->getMemDC(), i, _y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_x = i - _ball->getWidth() / 2;
			break;
		}
	}




	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->loadScene("테스트씬");
	}

}

void pixelCollisionScene::render(void)
{
	//백그라운드 렌더
	_mountain->render(getMemDC());

	//공 이미지 렌더
	_ball->render(getMemDC(), _rc.left, _rc.top);

	if (KEYMANAGER->isToggleKey('A'))
	{
		//작은 사각형 렌더
		RECT rc = RectMakeCenter(_x, _probeY, 10, 10);
		RECT rc2 = RectMakeCenter(_probeX, _y, 10, 10);

		Rectangle(getMemDC(), rc);
		Rectangle(getMemDC(), rc2);
	}
}
