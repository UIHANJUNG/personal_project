#pragma once
#include "singletonBase.h"

class cameraScene : singletonBase<cameraScene>
{
private:
	//카메라 target 선언
	POINTFLOAT* target;

	//카메라 렉트 (보여주는 크기)
	RECT rc;

	//카메라 포지션
	POINTFLOAT pos;
public:
	cameraScene() {}
	~cameraScene() {}

	void update();
	void render();
	
	//카메라 바꾸는 함수
	void Chasing();

	//카메라 target 타겟 바꾸기
	void SetTarget(POINTFLOAT* target);
};

