#pragma once
#include "gameNode.h"
/*�����δ� ������ ������ ������ϸ� ���ΰ��ӿ� �߰��صд�*/
#include "sceneTest.h"
#include "pixelCollisionScene.h"

class mainGame : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame() {}
	~mainGame() {}
};

