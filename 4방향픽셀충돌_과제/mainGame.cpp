#include "stdafx.h"
#include "mainGame.h"

#include "cameraScene.h"
//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화를 한다

	//앞으로 메인게임 클래스 안에서는 씬들만 관리를 한다
	//그리고 각각의 씬들이 메인게임 역할을 하면 된다

	/*씬추가*/
	SCENEMANAGER->addScene("테스트씬", new sceneTest);
	SCENEMANAGER->addScene("픽셀충돌", new pixelCollisionScene);

	//현재씬 설정
	SCENEMANAGER->loadScene("픽셀충돌");

	return S_OK;
	//return S_OK; 아래에 코드가 있으면 안됨!!!
}

//=============================================================
//	## 해제 ## release(void)
//=============================================================
void mainGame::release(void)
{
	gameNode::release();
}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void mainGame::update(void)
{
	gameNode::update();

	//씬매니져 업데이트
	SCENEMANAGER->update();
	
}

//=============================================================
//	## 렌더 ## render(void)
//=============================================================
void mainGame::render(void)
{
	//흰색 빈 비트맵 (이것도 렌더에 그냥 두기)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
//=============================================================

	//씬매니져 렌더
	SCENEMANAGER->render();

//=============================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 두기)
	this->getBackBuffer()->render(getHDC());
}


