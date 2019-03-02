#pragma once
#include "singletonBase.h"
class cameraManager : public singletonBase<cameraManager>
{
private:
	//카메라 target 선언
	float* targetX;
	float* targetY;

	//카메라 렉트 (보여주는 크기)
	RECT rc;

	//카메라 포지션
	POINTFLOAT pos;
public:
	cameraManager() {}
	~cameraManager() {}

	//카메라 바꾸는 함수
	void Chasing();

	//카메라 target 타겟 바꾸기
	void SetTarget(float* targetX, float* targetY);

	//렉트 가져오기
	RECT GetRect() { return rc; }
};

