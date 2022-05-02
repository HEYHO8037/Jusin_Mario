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
	m_tInfo.fY = float(600) - m_tInfo.fCY*0.5;
	

	m_tInfo.m_iHp = 3;
	m_tInfo.m_fSpeed = 5.f;
	m_tInfo.m_fAngle = 0.f;
	m_tType = TYPE_PLAYER;

	m_bWeapon = false;
	m_bDead = false;
	m_bJump = false;
	m_fTime = 0.f;
	m_mTime = 0.f;
	m_fPower = 5.f;
	int Level = 1;
	PTime = GetTickCount();
	m_fGroundPoint = float(600) - m_tInfo.fCY*0.5;

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
	Falling();
	MJump();
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
	Rectangle(hDC, m_tRect.left + (m_tInfo.m_iHp - 1) * 2, m_tRect.top - (m_tInfo.m_iHp-1)*15, m_tRect.right - (m_tInfo.m_iHp - 1) * 2, m_tRect.bottom);

	Draw_Character(hDC);
}

void CPlayer::Draw_Character(HDC hDC)
{
	int SCrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	if (m_tInfo.m_iHp == 3)
	{
		MoveToEx(hDC, m_tInfo.fX + SCrollX, m_tInfo.fY, nullptr);
		LineTo(hDC, (m_tInfo.fX + SCrollX) - 15, m_tInfo.fY + 27);
		MoveToEx(hDC, m_tInfo.fX + SCrollX, m_tInfo.fY, nullptr);
		LineTo(hDC, (m_tInfo.fX + SCrollX) + 15, m_tInfo.fY + 27);
		MoveToEx(hDC, m_tInfo.fX + SCrollX, m_tInfo.fY, nullptr);
		LineTo(hDC, (m_tInfo.fX + SCrollX) - 27, m_tInfo.fY + 18);
		MoveToEx(hDC, m_tInfo.fX + SCrollX, m_tInfo.fY, nullptr);
		LineTo(hDC, (m_tInfo.fX + SCrollX) + 18, m_tInfo.fY - 18);
		MoveToEx(hDC, m_tInfo.fX + SCrollX, m_tInfo.fY, nullptr);
		LineTo(hDC, (m_tInfo.fX + SCrollX), m_tInfo.fY - 15);
		Ellipse(hDC, (m_tInfo.fX + SCrollX) - 15, m_tInfo.fY - 45, (m_tInfo.fX + SCrollX) + 15, (m_tInfo.fY - 15));
	}

	if (m_tInfo.m_iHp == 2)
	{
		MoveToEx(hDC, m_tInfo.fX + SCrollX, m_tInfo.fY, nullptr);
		LineTo(hDC, (m_tInfo.fX + SCrollX) - 15, m_tInfo.fY + 27);
		MoveToEx(hDC, m_tInfo.fX + SCrollX, m_tInfo.fY, nullptr);
		LineTo(hDC, (m_tInfo.fX + SCrollX) + 15, m_tInfo.fY + 27);
		MoveToEx(hDC, m_tInfo.fX + SCrollX, m_tInfo.fY, nullptr);
		LineTo(hDC, (m_tInfo.fX + SCrollX) - 27, m_tInfo.fY + 18);
		MoveToEx(hDC, m_tInfo.fX + SCrollX, m_tInfo.fY, nullptr);
		LineTo(hDC, (m_tInfo.fX + SCrollX) + 18, m_tInfo.fY - 18);
		MoveToEx(hDC, m_tInfo.fX + SCrollX, m_tInfo.fY, nullptr);
		LineTo(hDC, (m_tInfo.fX + SCrollX), m_tInfo.fY - 15);
		Ellipse(hDC, (m_tInfo.fX + SCrollX) - 15, m_tInfo.fY - 45, (m_tInfo.fX + SCrollX) + 15, (m_tInfo.fY - 15));
	}


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
		if (PTime + 200 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, TYPE_PBULLET));
			PTime = GetTickCount();
		}
	}
	
}

void CPlayer::Jumping(void)
{
	if (m_bJump)
	{
		m_tInfo.fY -= m_fPower * m_fTime - 2.f * m_fTime * m_fTime * 0.5f;
		m_fTime += 0.2f;


		if (m_tInfo.fY > m_fGroundPoint)
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = m_fGroundPoint;
			m_fPower = 5.f;
		}
	}
}

void CPlayer::MJump(void)
{
	if (m_mJump)
	{
		m_tInfo.fY -= m_fPower * m_mTime - 2.f * m_mTime * m_mTime * 0.5f;
		m_mTime += 0.2f;

		if (m_tInfo.fY > m_fGroundPoint)
		{
			m_mJump = false;
			m_mTime = 0.f;
			m_bJump = true;
			
		}
	}
	else
	{
		m_fPower = 5.f;
	}
}

void CPlayer::Falling()
{
	if (m_bIsFalling)
	{
		m_tInfo.fY += m_fPower * m_fTime * 0.5f;
		m_fTime += 0.2f;


		if (m_tInfo.fY > m_fGroundPoint)
		{
			m_fTime = 0.f;
			m_tInfo.fY = m_fGroundPoint;
			m_bIsFalling = false;
		}
	}
}

void CPlayer::OffSet(void)
{
	int iOffSet = WINCX >> 1;
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	

	if (iOffSet - 100 > m_tInfo.fX + iScrollX)
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(m_tInfo.m_fSpeed);
	}
	else if (iOffSet + 100 < m_tInfo.fX + iScrollX)
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_tInfo.m_fSpeed);
	}
}