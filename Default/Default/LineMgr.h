#pragma once

#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	bool		Collision_Line(float& _fX, float* pY); //���� �浹

	void		Create_Line(const CLine& Line); // ���� ���� ����
	void		Create_Line(const LINEPOINT& tLeft, const LINEPOINT& tRight); // �� �ΰ��� ���� ����
	
	void		Load_LineData(); // ���ε����� ��������
	void		Save_LineData(); // ���ε����� �����ϱ�

public:
	static CLineMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CLineMgr;
		}

		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CLineMgr* m_pInstance; // �̱����� ���� static ������
	list<CLine*> m_pLineList; // CLine�� �����ϴ� ����Ʈ

};