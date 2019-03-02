#pragma once
#include "singletonBase.h"
class cameraManager : public singletonBase<cameraManager>
{
private:
	//ī�޶� target ����
	float* targetX;
	float* targetY;

	//ī�޶� ��Ʈ (�����ִ� ũ��)
	RECT rc;

	//ī�޶� ������
	POINTFLOAT pos;
public:
	cameraManager() {}
	~cameraManager() {}

	//ī�޶� �ٲٴ� �Լ�
	void Chasing();

	//ī�޶� target Ÿ�� �ٲٱ�
	void SetTarget(float* targetX, float* targetY);

	//��Ʈ ��������
	RECT GetRect() { return rc; }
};

