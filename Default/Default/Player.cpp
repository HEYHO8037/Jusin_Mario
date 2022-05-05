#include "stdafx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "BmpMgr.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(void)
{
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_tInfo.fX = 100.f;
	m_tInfo.fY = float(600) - m_tInfo.fCY*0.5;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/PlayerR.bmp", L"PlayerR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/PlayerL.bmp", L"PlayerL");

	m_tInfo.m_iHp = 1;
	m_tInfo.m_fSpeed = 5.f;
	m_tInfo.m_fAngle = 0.f;
	m_tType = TYPE_PLAYER;

	m_tWeapon = TYPE_NO_WEAPON;
	m_bDead = false;
	m_bJump = false;
	m_fTime = 0.f;
	m_mTime = 0.f;
	m_fPower = 5.f;
	m_bRight = true;
	int Level = 1;
	PTime = GetTickCount();
	m_fGroundPoint = float(600) - m_tInfo.fCY*0.5;

}

void CPlayer::Release(void)
{
	CBmpMgr::Get_Instance()->Destroy_Instance();
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
	HBRUSH   brush;
	HGDIOBJ h_old_brush;
	if (m_bRight)
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerR");

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top),
			int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hMemDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(0, 255, 0));			// 제거하고자 하는 색상
	}
	else
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerL");

		GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
			int(m_tRect.top),
			int(m_tInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
			int(m_tInfo.fCY),
			hMemDC,							// 비트맵을 가지고 있는 DC
			0,								// 비트맵 출력 시작 좌표, X,Y
			0,
			(int)m_tInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
			(int)m_tInfo.fCY,
			RGB(0, 255, 0));			// 제거하고자 하는 색상
	}

	/*if (m_tWeapon == TYPE_NO_WEAPON)
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
	}*/

	 //되는지확인해주세여 . .  
	if (0==m_tInfo.m_iHp )
	{
		lstrcpy(m_szFPS, L"GAMEOVER!");
		TextOut(hDC, WINCX >> 1, WINCY >> 1, m_szFPS, lstrlen(m_szFPS));
	}
}



void CPlayer::Key_Update(void)
{
	
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_tInfo.m_fSpeed;
		m_bRight = false;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_tInfo.m_fSpeed;
		m_bRight = true;
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
		m_tInfo.fY -= m_fPower * m_fTime - 1.5f * m_fTime * m_fTime * 0.5f;
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
		m_bJump = false;
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
	

	if (iOffSet - 200 > m_tInfo.fX + iScrollX)
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(m_tInfo.m_fSpeed);
	}
	else if (iOffSet + 20 < m_tInfo.fX + iScrollX)
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(-m_tInfo.m_fSpeed);
	}

}

