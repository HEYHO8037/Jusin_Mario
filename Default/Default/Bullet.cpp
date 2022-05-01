#include "stdafx.h"
#include "Bullet.h"
#include "ScrollMgr.h"

CBullet::CBullet()
{
}

CBullet::CBullet(TYPE eType)
{
	m_tType = eType;
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_tInfo.m_fSpeed = 5.f;
}

int CBullet::Update(void)
{
	if (m_tInfo.m_fAngle == -1)
	{
		m_tInfo.fX += m_tInfo.m_fSpeed;
	}
	else
	{
		m_tInfo.fX += m_tDir.fX * m_tInfo.m_fSpeed;
		m_tInfo.fY += m_tDir.fY * m_tInfo.m_fSpeed;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
	//if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right ||
	//100 >= m_tRect.top || WINCY - 100 <= m_tRect.bottom)
	//m_bDead = true; 
}

void CBullet::Render(HDC hDC)
{
	int ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Ellipse(hDC, m_tRect.left+ScrollX, m_tRect.top, m_tRect.right+ScrollX, m_tRect.bottom);
}

void CBullet::Release(void)
{
	m_tInfo.m_fSpeed = 0.f;
}

void CBullet::Set_Angle(float fAngle)
{
	m_tInfo.m_fAngle = fAngle;
}

void CBullet::Set_Dir(float fX, float fY)
{
	m_tDir.fX = fX;
	m_tDir.fY = fY;
}
