#include "stdafx.h"
#include "cameraManager.h"

//ī�޶� ��Ʈ�� Ÿ�� ���󰡱�
void cameraManager::Chasing()
{
	if (targetX != nullptr && targetY != nullptr) 
	{
		pos.x = *targetX;
		pos.y = *targetY;
		rc = RectMakeCenter(pos.x, pos.y, WINSIZEX, WINSIZEY);
	}
}

//ī�޶� Ÿ�� ����
void cameraManager::SetTarget(float* targetX, float* targetY)
{
	this->targetX = targetX;
	this->targetY = targetY;
}
