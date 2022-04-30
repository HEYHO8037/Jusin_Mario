#include "stdafx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Bullet.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	m_tInfo.fX = 100.f;
	m_tInfo.fY = float(WINCY) - m_tInfo.fCY*0.5;
	

	m_tInfo.m_iHp = 3;
	m_tInfo.m_fSpeed = 5.f;
	m_tInfo.m_fAngle = 0.f;

	m_bWeapon = false;
	m_bDead = false;
	m_bJump = false;
	m_fTime = 0.f;
	m_fPower = 5.f;

}

void CPlayer::Release(void)
{
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	OffSet();
	Key_Update();
	Jumping();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	if (m_tInfo.m_iHp <= 0)
	{
		Set_Dead();
	}
}

void CPlayer::Render(HDC hDC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hDC, m_tRect.left+iScrollX, m_tRect.top, m_tRect.right+iScrollX, m_tRect.bottom);

	Rectangle(hDC, 600+iScrollX, 200, 800+iScrollX, 300);
}

void CPlayer::Key_Update(void)
{
	

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_tInfo.m_fSpeed;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_tInfo.m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bJump = true;
		return;
	}
	m_tInfo.m_fSpeed = 5.f;
	if (CKeyMgr::Get_Instance()->Key_Pressing('Z'))
	{
		m_tInfo.m_fSpeed = 10.f;	
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('X'))
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_tInfo.fX,m_tInfo.fY,TYPE_PBULLET));
	}
	
}

void CPlayer::Jumping(void)
{
	if (m_bJump)
	{
		m_tInfo.fY -= m_fPower * m_fTime - 2.f * m_fTime * m_fTime * 0.5f;
		m_fTime += 0.2f;

		if (m_tInfo.fY > float(WINCY)-m_tInfo.fCY*0.5)
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = WINCY - m_tInfo.fCY*0.5;
		}
	}
}

void CPlayer::OffSet(void)
{
	int iOffSet = WINCX >> 1;
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	

	if (iOffSet > m_tInfo.fX + iScrollX)
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(m_tInfo.m_fSpeed);
	}
	if (iOffSet < m_tInfo.fX + iScrollX)
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_tInfo.m_fSpeed);
	}


}

