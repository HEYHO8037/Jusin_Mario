#include "stdafx.h"
#include "Bullet.h"
#include "ScrollMgr.h"
#include "Player.h"
#include "BmpMgr.h"

CBullet::CBullet()
{
}

CBullet::CBullet(TYPE eType, bool _right)
{
	m_tType = eType;
	m_bRight = _right;
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 15.f;
	m_tInfo.m_fSpeed = 8.f;
	m_tInfo.m_iHp = 1;
	m_tInfo.m_fAngle = -1;

	m_bDead = false;

}

int CBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	
	if (m_tType == TYPE_PBULLET)
	{
		if (m_bRight)
			m_tInfo.fX += m_tInfo.m_fSpeed;	
		else
			m_tInfo.fX -= m_tInfo.m_fSpeed;

	}

	if (m_tType == TYPE_MONSTER_BULLET && !m_tDir.fX)
	{
		m_tInfo.fX -= m_tInfo.m_fSpeed;
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
	if (m_tInfo.m_iHp == 0)
	{
		Set_Dead();
	}
}

void CBullet::Render(HDC hDC)
{
	if (m_bRight)
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BulletR");
		GdiTransparentBlt(hDC, 				// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top),
			int(30),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(15),
			hMemDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));			// 제거하고자 하는 색상
	}
	else
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BulletL");
		GdiTransparentBlt(hDC, 				// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top),
			int(32),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(15),
			hMemDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));			// 제거하고자 하는 색상
	}
}

void CBullet::Release(void)
{
	m_tInfo.m_fSpeed = 0.f;
}

void CBullet::Set_Angle(float fAngle)
{
	m_tInfo.m_fAngle = fAngle;
}

void CBullet::Set_Type(TYPE eType)
{
	m_tType = eType;
}

void CBullet::Set_Dir(float fX, float fY)
{
	m_tDir.fX = fX;
	m_tDir.fY = fY;
}
