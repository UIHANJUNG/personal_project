#pragma once
#include "gameNode.h"
#include "bullet.h"
class pixelCollisionScene : public gameNode
{
private:
	float _x, _y;
	image* _background;
	image* _backgroundColor;

	image* _ball;
	RECT _rc;

	int _probeY;

	bullet* _bullet;

	int _timeCount = 0;

	bool _istarget;

	bool _isMove;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	pixelCollisionScene() {}
	~pixelCollisionScene() {}
};

