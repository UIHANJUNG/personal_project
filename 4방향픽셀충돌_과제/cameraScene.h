#pragma once
#include "singletonBase.h"

class cameraScene : singletonBase<cameraScene>
{
private:
	//ī�޶� target ����
	POINTFLOAT* target;

	//ī�޶� ��Ʈ (�����ִ� ũ��)
	RECT rc;

	//ī�޶� ������
	POINTFLOAT pos;
public:
	cameraScene() {}
	~cameraScene() {}

	void update();
	void render();
	
	//ī�޶� �ٲٴ� �Լ�
	void Chasing();

	//ī�޶� target Ÿ�� �ٲٱ�
	void SetTarget(POINTFLOAT* target);
};

