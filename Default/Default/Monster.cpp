#include "stdafx.h"
#include "Monster.h"
#include "ScrollMgr.h"

CMonster::CMonster()
{
}

CMonster::CMonster(TYPE _eType)
{
	m_tType = _eType;
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	if (m_tType == TYPE_MONSTER_MOVE)
	{
		m_tInfo.fCX = 35.f;
		m_tInfo.fCY = 35.f;
		m_tInfo.m_fSpeed = 5.f;
		m_fTemp = m_tInfo.fX;

	}

	if (m_tType == TYPE_MONSTER_BULLET)
	{
		m_tInfo.fCX = 50.f;
		m_tInfo.fCY = 70.f;
		m_fTemp = m_tInfo.fX;
		m_tInfo.m_fSpeed = 3.f;

	}

}

void CMonster::Release(void)
{
}

int CMonster::Update(void)
{

	if (m_bDead)
		return OBJ_DEAD;

	if (m_tType == TYPE_MONSTER_MOVE) //이동 몬스터
	{
		m_tInfo.fX += m_tInfo.m_fSpeed;
		
		if (200 > m_tInfo.fX || 600 < m_tInfo.fX)
		{
			m_tInfo.m_fSpeed *= -1.f;

		}
	
	}

	else if (m_tType == TYPE_MONSTER_BULLET) // 총알 몬스터
	{

		float fWidth = m_tTarget->Get_Info().fX - m_tInfo.fX; 
		float fHeight = m_tTarget->Get_Info().fY - m_tInfo.fY;

		float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight); 

		float fRadian = acosf(fWidth / fDiagonal); 
		
		//범위 다시 지정해주기
		if ( 200.f <= fDiagonal && 600.f > fDiagonal)
		{
			m_tInfo.fX -= m_tInfo.m_fSpeed;

			if (500 >= m_tInfo.fX || 700 < m_tInfo.fX)
			{
				m_tInfo.m_fSpeed *= -1.f;

			}
		}
		
		else if( 200.f > fDiagonal)
			m_tInfo.fX += m_tInfo.m_fSpeed * cosf(fRadian);

	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	//if (m_tType == TYPE_MONSTER_MOVE)
	//{
	//	if ( 200 >= m_tRect.left || 400 <= m_tRect.right)
	//	{
	//		m_tInfo.m_fSpeed *= -1.f;
	//	}
	//}

	
}

void CMonster::Render(HDC hDC)
{

	HBRUSH	brush;
	HGDIOBJ h_old_brush;

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	switch (m_tType)
	{
	case TYPE_MONSTER_MOVE: 
		brush = CreateSolidBrush(RGB(255, 128, 64));
		h_old_brush = SelectObject(hDC, brush);
		Ellipse(hDC, m_tRect.left+iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		break;

	case TYPE_MONSTER_BULLET:
		brush = CreateSolidBrush(RGB(64, 128, 128));
		h_old_brush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		break;

	default:
		break;
	}

}
