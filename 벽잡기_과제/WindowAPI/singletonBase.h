#pragma once

template<class T>
class singletonBase
{
protected:
	//�̱��� �ν��Ͻ� ����
	static T* singleton;

	singletonBase() {}
	~singletonBase() {}

public:
	//�̱��� ��������
	static T* getSingleton(void);
	//�̱��� �޸𸮿��� �����ϱ�
	void releaseSingleton(void);

};

//�̱��� �ʱ�ȭ
template <class T>
T* singletonBase<T>::singleton = 0;

//�̱��� ��������
template<class T>
inline T * singletonBase<T>::getSingleton(void)
{
	//�̱����� ������ ���� ����
	if (!singleton) singleton = new T;
	return singleton;
}

//�̱��� �޸𸮿��� �����ϱ�
template<class T>
inline void singletonBase<T>::releaseSingleton(void)
{
	//�̱����� �ִٸ� �޸𸮿��� ����
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}
