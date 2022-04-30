#pragma once

#include "Include.h"
/*
��ũ�� ����
������ �߽����� ������Ʈ���� �����ϰųĸ� �켱 ���Ѵ�.
�÷��̾ �߽����� �����δٰ� �����ϸ�
��� ������Ʈ���� �÷��̾��� �ӵ���ŭ ���������Ѵ�.
���� ��� �÷��̾��� �ӵ��� 5��� �����ϸ�
�÷��̾ ������ OffSet(���� ��)�� �Ѿ�� ��
������ ������ ��ũ�� ��ǥ�� �÷��̾��� �ӵ���ŭ ���ϰ�
������ ������ ��ũ�� ��ǥ�� �÷��̾��� �ӵ���ŭ ����
���� ��ǥ�� ��ũ����ǥ�� ���� ��ǥ�� �׸��� �׷��ָ� �÷��̾� �ӵ���ŭ �̵��ϴ°� ó�� ���δ�.


��ǥ�� ���� ������ ���� ������
�ػ��� ����� 800x600 �̶�� �������� ��
�÷��̾��� ��ǥ�� ��ũ�� ��ǥ��ŭ �����ִٺ��� �ػ��� ũ�⸦ �������
������ �� �� ��ũ�� ��ǥ��ŭ ������ ������ �׸��� ������ ����� ����.
������� ��� �����ִٰ� �÷��̾��� X����ǥ�� 10000�� �Ǿ��ٰ� �ص�
�������� �� 10000��ǥ�� �������� �ȴ�.
*/

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float Get_ScrollX(void) { return m_fScrollX; }
	void Set_ScrollX(float _fX) { m_fScrollX += _fX; }
	
	float Get_ScrollY(void) { return m_fScrollY; }
	void Set_ScrollY(float _fY) { m_fScrollY -= _fY; }

public:
	static CScrollMgr* Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;
	
			return m_pInstance;
	}

	static void Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CScrollMgr* m_pInstance;
	float m_fScrollX = 0.f;
	float m_fScrollY = 0.f;
};





