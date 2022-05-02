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

//	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	switch (m_tType)
	{
	case TYPE_MONSTER_MOVE:
		brush = CreateSolidBrush(RGB(240, 219, 202));
		h_old_brush = SelectObject(hDC, brush);
		Ellipse(hDC, m_tRect.left +10, m_tRect.top+30, m_tRect.right-10, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		brush = CreateSolidBrush(RGB(255, 74, 6));
		h_old_brush = SelectObject(hDC, brush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom -10);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		break;

	case TYPE_MONSTER_TURTLE:
		if (3 == m_tInfo.m_iHp)
		{
		
			if (m_tTarget->Get_Rect().right < m_tRect.left)
    			{
				brush = CreateSolidBrush(RGB(63, 107, 69));
				h_old_brush = SelectObject(hDC, brush);
				Ellipse(hDC, m_tRect.left, m_tRect.top + 20, m_tRect.right, m_tRect.bottom - 10);
				SelectObject(hDC, h_old_brush);
				DeleteObject(brush);
				brush = CreateSolidBrush(RGB(251, 230, 204));
				h_old_brush = SelectObject(hDC, brush);
				Ellipse(hDC, m_tRect.left + 8, m_tRect.top + 55, m_tRect.right - 22, m_tRect.bottom);
				Ellipse(hDC, m_tRect.left + 16, m_tRect.top + 55, m_tRect.right - 15, m_tRect.bottom);
				Ellipse(hDC, m_tRect.left, m_tRect.top +20, m_tRect.right-12, m_tRect.bottom-10);
				Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right - 15, m_tRect.bottom - 45);
				SelectObject(hDC, h_old_brush);
				DeleteObject(brush);
			}
			else
			{
		  		brush = CreateSolidBrush(RGB(63, 107, 69));
				h_old_brush = SelectObject(hDC, brush);
				Ellipse(hDC, m_tRect.left, m_tRect.top + 20, m_tRect.right, m_tRect.bottom - 10);
				SelectObject(hDC, h_old_brush);
				DeleteObject(brush);
				brush = CreateSolidBrush(RGB(251, 230, 204));
				h_old_brush = SelectObject(hDC, brush);
				Ellipse(hDC, m_tRect.left + 20, m_tRect.  top + 55, m_tRect.right - 7, m_tRect.bottom);
				Ellipse(hDC, m_tRect.left + 30, m_tRect.top + 55, m_tRect.right - 2, m_tRect.bottom);
				Ellipse(hDC, m_tRect.left+15, m_tRect.top + 20, m_tRect.right, m_tRect.bottom - 10);
				Ellipse(hDC, m_tRect.left+15, m_tRect.top, m_tRect.right, m_tRect.bottom - 45);
				SelectObject(hDC, h_old_brush);
				DeleteObject(brush);
			}
			break;
		}
		else if (3 > m_tInfo.m_iHp)
		{
			brush = CreateSolidBrush(RGB(251, 230, 204));
			h_old_brush = SelectObject(hDC, brush);
			Ellipse(hDC, m_tRect.left, m_tRect.top + 40, m_tRect.right, m_tRect.bottom);
			SelectObject(hDC, h_old_brush);
			DeleteObject(brush);

			brush = CreateSolidBrush(RGB(63, 107, 69));
			h_old_brush = SelectObject(hDC, brush);
			Ellipse(hDC, m_tRect.left, m_tRect.top + 40, m_tRect.right, m_tRect.bottom -5);
			SelectObject(hDC, h_old_brush);
			DeleteObject(brush);
			
			break;
		}
		break;
	default:
		break;
	}

}