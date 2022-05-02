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
	

	m_tInfo.m_iHp = 1;
	m_tInfo.m_fSpeed = 5.f;
	m_tInfo.m_fAngle = 0.f;

	m_tWeapon = TYPE_NO_WEAPON;
	m_bDead = false;
	m_bJump = false;
	m_fTime = 0.f;
	m_mTime = 0.f;
	m_fPower = 5.f;
	int Level = 1;
	PTime = GetTickCount();

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
	HBRUSH   brush;
	HGDIOBJ h_old_brush;

	if (m_tWeapon == TYPE_NO_WEAPON)
	{
		brush = CreateSolidBrush(RGB(0, 0, 0));
		h_old_brush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left + (m_tInfo.m_iHp - 1) * 2, m_tRect.top - (m_tInfo.m_iHp - 1) * 15, m_tRect.right - (m_tInfo.m_iHp - 1) * 2, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
	}
	else if (m_tWeapon == TYPE_GUN_WEAPON)
	{
		brush = CreateSolidBrush(RGB(255, 0, 0));
		h_old_brush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left + (m_tInfo.m_iHp - 1) * 2, m_tRect.top - (m_tInfo.m_iHp - 1) * 15, m_tRect.right - (m_tInfo.m_iHp - 1) * 2, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
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
		if (m_tWeapon == TYPE_GUN_WEAPON)
		{
			if (PTime + 200 < GetTickCount())
			{
				CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, TYPE_PBULLET));
				PTime = GetTickCount();
			}
		}
	}
	
}

void CPlayer::Jumping(void)
{
	if (m_bJump)
	{
		m_tInfo.fY -= m_fPower * m_fTime - 2.f * m_fTime * m_fTime * 0.5f;
		m_fTime += 0.2f;

		if (m_tInfo.fY > float(600)-m_tInfo.fCY*0.5)
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = 600 - m_tInfo.fCY*0.5;
		}
	}
}

void CPlayer::MJump(void)
{
	
	if (m_mJump)
	{
		m_tInfo.fY -= m_fPower * m_mTime - 2.f * m_mTime * m_mTime * 0.5f;
		m_mTime += 0.2f;

		if (m_tInfo.fY > float(600) - m_tInfo.fCY*0.5)
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

void CPlayer::OffSet(void)
{
	int iOffSet = WINCX >> 1;
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	

	if (iOffSet - 200 > m_tInfo.fX + iScrollX)
	{
		//CScrollMgr::Get_Instance()->Set_ScrollX(m_tInfo.m_fSpeed);
	}
	else if (iOffSet + 20 < m_tInfo.fX + iScrollX)
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_tInfo.m_fSpeed);
	}
	



}





