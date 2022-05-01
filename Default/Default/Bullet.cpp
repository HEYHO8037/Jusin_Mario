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
	m_tInfo.m_iHp = 1;
	m_bDead = false;
}

int CBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += m_tInfo.m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
	if (m_tInfo.m_iHp == 0)
	{
		Set_Dead();
	}
}

void CBullet::Render(HDC hDC)
{
	int ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release(void)
{
	m_tInfo.m_fSpeed = 0.f;
}