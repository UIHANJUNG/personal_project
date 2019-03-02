#include "stdafx.h"
#include "cameraScene.h"

void cameraScene::update()
{
	Chasing();
}

void cameraScene::render()
{
	//_background->render(getMemDC(),- _camera.rc.left , -_camera.rc.top);
	//_ballImage->render(getMemDC(), _ballRect.left - _camera.rc.left, _ballRect.top - _camera.rc.top);
	//_bullet.Render(getMemDC(),_camera.rc);
}

void cameraScene::Chasing()
{
	if (target != nullptr)
	{
		pos = *target;
		rc = RectMakeCenter(pos.x, pos.y, WINSIZEX, WINSIZEY);
	}
}

void cameraScene::SetTarget(POINTFLOAT * target)
{
	this->target = target;
}

void Bullet::Fire(POINTFLOAT pos,float angle)
{
	this->pos = pos;
	this->angle = angle;
	this->fire = true;
	gravity = 0.f;
	this->rc = RectMakeCenter(pos.x, pos.y, 50, 50);
}

void Bullet::Update(HDC hdc,Camera* camera,POINTFLOAT* target)
{
	if (fire != false)
	{
		pos.x += cosf(angle) * 4.0f;
		pos.y += -sinf(angle) * 4.0f + gravity;
		gravity += 0.03f;
		this->rc = RectMakeCenter(pos.x, pos.y, 50, 50);

		COLORREF color = GetPixel(hdc, pos.x, pos.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 255 && g == 0 && b == 255) == false)
		{
			HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
			HPEN pen = (HPEN)CreatePen(PS_NULL, 1, RGB(255, 0, 255));
			HPEN oldPen = (HPEN)SelectObject(hdc, pen);

			EllipseMakeCenter(hdc, pos.x, pos.y, 50, 50);
			SelectObject(hdc, oldPen);
			DeleteObject(pen);

			SelectObject(hdc, oldBrush);
			DeleteObject(brush);

			this->fire = false;
			camera->SetTarget(target);
		}
	}
}

void Bullet::Render(HDC hdc,RECT cameraRc)
{
	if (fire)
	{
		RECT relativeRect = rc;
		relativeRect.left -= cameraRc.left;
		relativeRect.top -= cameraRc.top;
		relativeRect.right -= cameraRc.left;
		relativeRect.bottom -= cameraRc.top;
		Rectangle(hdc, relativeRect);
	}
}
