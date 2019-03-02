#include "stdafx.h"
#include "cameraManager.h"

//카메라 렉트는 타겟 따라가기
void cameraManager::Chasing()
{
	if (targetX != nullptr && targetY != nullptr) 
	{
		pos.x = *targetX;
		pos.y = *targetY;
		rc = RectMakeCenter(pos.x, pos.y, WINSIZEX, WINSIZEY);
	}
}

//카메라 타겟 지정
void cameraManager::SetTarget(float* targetX, float* targetY)
{
	this->targetX = targetX;
	this->targetY = targetY;
}
