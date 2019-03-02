#pragma once
#include "gameNode.h"

class pixelCollisionScene : public gameNode
{
private:
	image* _mountain;		//��׶��� �̹���
	image* _ball;			//���̹���
	RECT _rc;				//�� ��Ʈ
	RECT _rc2;				//�� ��Ʈ

	float _x, _y;			//��ġ��ǥ
	int _probeY;			//�ȼ��浹 Ž���� Y��
	int _probeX;			//�ȼ��浹 Ž���� X��

	bool _isjump;			//������ 

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	pixelCollisionScene() {}
	~pixelCollisionScene() {}
};

