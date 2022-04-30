#include "stdafx.h"
#include "Bullet.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;
}

void CBullet::Update(void)
{
	m_tInfo.fX += m_fSpeed;

	Update_Rect();

}

void CBullet::Late_Update(void)
{
	//if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right ||
	//100 >= m_tRect.top || WINCY - 100 <= m_tRect.bottom)
	//m_bDead = true; 

}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release(void)
{
	m_fSpeed = 0.f;
}