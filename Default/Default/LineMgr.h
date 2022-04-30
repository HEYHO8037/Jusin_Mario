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
	bool		Collision_Line(float& _fX, float* pY); //라인 충돌

	void		Create_Line(const CLine& Line); // 라인 복사 생성
	void		Create_Line(const LINEPOINT& tLeft, const LINEPOINT& tRight); // 점 두개로 라인 생성
	
	void		Load_LineData(); // 라인데이터 가져오기
	void		Save_LineData(); // 라인데이터 저장하기

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
	static CLineMgr* m_pInstance; // 싱글톤을 위한 static 포인터
	list<CLine*> m_pLineList; // CLine을 관할하는 리스트

};