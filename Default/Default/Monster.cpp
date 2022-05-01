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
		m_tInfo.fCX = 50.f;
		m_tInfo.fCY = 50.f;
		m_tInfo.m_fSpeed = 3.f;
		m_tInfo.m_iHp = 1;
		m_bDead = false;
	}

	if (m_tType == TYPE_MONSTER_TURTLE)
	{
		m_tInfo.fCX = 40.f;
		m_tInfo.fCY = 70.f;
		m_tInfo.m_fSpeed = 3.f;
		m_tInfo.m_iHp = 3;
		m_bDead = false;
	}

}

void CMonster::Release(void)
{
}

int CMonster::Update(void)
{

	if (m_bDead)
		return OBJ_DEAD;

	if (m_tType == TYPE_MONSTER_MOVE)   
	{
		m_tInfo.fX += m_tInfo.m_fSpeed;
	}

	else if (m_tType == TYPE_MONSTER_TURTLE)  
	{

		if (1 >= m_tInfo.m_iHp)
		{
			if (m_tInfo.fX > m_tTarget->Get_Info().fX)
			{
				m_tInfo.fX += m_tInfo.m_fSpeed;
			}
			else if (m_tInfo.fX < m_tTarget->Get_Info().fX)
			{
				m_tInfo.fX -= m_tInfo.m_fSpeed;
			}
		}

		float fWidth = m_tTarget->Get_Info().fX - m_tInfo.fX;
		float fHeight = m_tTarget->Get_Info().fY - m_tInfo.fY;

		float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight);

		float fRadian = acosf(fWidth / fDiagonal);

		if (450.f > fDiagonal && m_tInfo.m_iHp >=2)
		{
			m_tInfo.fX += m_tInfo.m_fSpeed * cosf(fRadian);

		}
		

	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	if (m_tType == TYPE_MONSTER_MOVE)
	{
		if (0 >= m_tInfo.m_iHp)
			Set_Dead();
	}
	else if (m_tType == TYPE_MONSTER_TURTLE)
	{

		if (2 == m_tInfo.m_iHp) 
		{
			m_tInfo.m_fSpeed = 0.f;
		}
		else if (1 == m_tInfo.m_iHp)
		{
			m_tInfo.m_fSpeed = 8.f;

		}
		else if (0 >= m_tInfo.m_iHp)
		{
			Set_Dead();
		}
	}

	Update_Rect();

}

void CMonster::Render(HDC hDC)
{

	HBRUSH   brush;
	HGDIOBJ h_old_brush;

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	switch (m_tType)
	{
	case TYPE_MONSTER_MOVE:
		brush = CreateSolidBrush(RGB(255, 128, 64));
		h_old_brush = SelectObject(hDC, brush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		break;

	case TYPE_MONSTER_TURTLE:
		if (3 == m_tInfo.m_iHp)
		{
			brush = CreateSolidBrush(RGB(73, 146, 146));
			h_old_brush = SelectObject(hDC, brush);
			Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
			SelectObject(hDC, h_old_brush);
			DeleteObject(brush);
			break;
		}
		else if (3 > m_tInfo.m_iHp)
		{
			brush = CreateSolidBrush(RGB(58, 118, 106));
			h_old_brush = SelectObject(hDC, brush);
			Rectangle(hDC, m_tRect.left, m_tRect.top + 40, m_tRect.right, m_tRect.bottom);
			SelectObject(hDC, h_old_brush);
			DeleteObject(brush);
			break;
		}
		break;
	default:
		break;
	}

}