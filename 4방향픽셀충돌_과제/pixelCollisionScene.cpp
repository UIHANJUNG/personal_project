#include "stdafx.h"
#include "pixelCollisionScene.h"

HRESULT pixelCollisionScene::init(void)
{
	//빽그라운드 이미지
	_background = IMAGEMANAGER->addImage("shop", "shop.bmp", WINSIZEX, WINSIZEY, true, RGB(255,0,255));

	//픽셀충돌용 백그라운드 이미지
	_backgroundColor = IMAGEMANAGER->addImage("shopPixel", "shopPixel.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//공 이미지
	_ball = IMAGEMANAGER->addImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));

	//공 위치
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 1.5f;
	
	//렉트 생성
	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	//픽셀 체크 간격
	//_probeY = _y + _ball->getHeight() / 2;


	CAMERAMANAGER->SetTarget(&_x, &_y);

	_istarget = false;

	_isMove = true;

	return S_OK;
}

void pixelCollisionScene::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
}

void pixelCollisionScene::update(void)
{
	_timeCount++;



	//렉트 생성
	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	//픽셀 체크 간격
	//_probeY = _y + _ball->getHeight() / 2;

	//렉트 왼쪽 픽셀
	for (int i = _rc.left; i < _rc.left + 15; i++) 
	{
		for (int j = _rc.top + 10; j < _rc.bottom - 10; j++)
		{
			COLORREF color = GetPixel(_backgroundColor->getMemDC(), i, j);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 0)
			{
				_isMove = false;
				_x += 0.01f;
			}
			else 
			{
				_isMove = true;
			}
		}

	}

	//렉트 오른쪽 픽셀
	for (int i = _rc.right - 15; i < _rc.right; i++)
	{
		for (int j = _rc.top + 10; j < _rc.bottom - 10; j++)
		{
			COLORREF color = GetPixel(_backgroundColor->getMemDC(), i, j);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 0)
			{
				_isMove = false;
				_x -= 0.01f;
			}
			else
			{
				_isMove = true;
			}
		}

	}

	//렉트 위 픽셀
	for (int i = _rc.left + 10; i < _rc.right - 10; i++)
	{
		for (int j = _rc.top; j < _rc.top + 15; j++)
		{
			COLORREF color = GetPixel(_backgroundColor->getMemDC(), i, j);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 0)
			{
				_isMove = false;
				_y += 0.01f;
			}
			else
			{
				_isMove = true;
			}
		}

	}

	//렉트 아래 픽셀
	for (int i = _rc.left + 10; i < _rc.right - 10; i++)
	{
		for (int j = _rc.bottom - 15; j < _rc.bottom; j++)
		{
			COLORREF color = GetPixel(_backgroundColor->getMemDC(), i, j);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 0)
			{
				_isMove = false;
				_y -= 0.01f;
			}
			else
			{
				_isMove = true;
			}
		}
	}
	
	if (_isMove == true) 
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_x -= 5.0f;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_x += 5.0f;
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_y -= 5.0f;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_y += 5.0f;
		}
	}

	//	
	//
	//	if (!(r == 255 && g == 0 && b == 255))
	//	{
	//		_y = i - _ball->getHeight() / 2;
	//		break;
	//	}
	//} (int i = _probeY - 50; i < _probeY + 50; i++) 
	//{	

	//HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
	//HGDIOBJ oldbrush = SelectObject(_background->getMemDC(), brush);
	//HPEN pen = CreatePen(PS_NULL, 0, RGB(255, 0, 255));
	//HGDIOBJ oldpen = SelectObject(_background->getMemDC(), pen);

	//SelectObject(_background->getMemDC(), oldbrush);
	//SelectObject(_background->getMemDC(), oldpen);
	//DeleteObject(pen);
	//DeleteObject(brush);


	


	CAMERAMANAGER->Chasing();
}

void pixelCollisionScene::render(void)
{
	_background->render(getMemDC(), - CAMERAMANAGER->GetRect().left, - CAMERAMANAGER->GetRect().top);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		_backgroundColor->render(getMemDC(), -CAMERAMANAGER->GetRect().left, -CAMERAMANAGER->GetRect().top);
	}

	_ball->render(getMemDC(), _rc.left - CAMERAMANAGER->GetRect().left, _rc.top - CAMERAMANAGER->GetRect().top);


	//if (KEYMANAGER->isToggleKey(VK_F1))
	//{
	//	Rectangle(_background->getMemDC(), _rc);
	//}
	//

//	_bullet->render();

	
}
