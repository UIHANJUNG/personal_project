#pragma once
#include "gameNode.h"

//�θ�Ŭ���� => �̳��� ��ӹ޾Ƽ� ����, �Ϲݸ��͵��� �����
class enemy : public gameNode
{
private:
	image* _image;		//���ʹ� �̹���
	RECT _rc;			//�浹�� ��Ʈ

	//������ �̹����� ������ ���� ������
	int _count;
	int _currentFrameX;
	int _currentFrameY;

	//�������� �Ѿ˹߻� ��Ÿ�� �ֱ�
	int _fireCount;
	int _rndFireCount;

public:
	HRESULT init(void);
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	virtual void move();		//������Ʈ�� �ֱ�			
	virtual void draw();		//���� �ȿ� �ֱ�
	virtual void animation();	//������Ʈ�� �ֱ�

	bool bulletCountFire();

	//��Ʈ ���
	RECT getRect() { return _rc; }

	enemy() {}
	~enemy() {}
};

