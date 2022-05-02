#include "stdafx.h"
#include "BossMonster.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Player.h"


CBossMonster::CBossMonster()
{
}

CBossMonster::CBossMonster(TYPE eType)
{
	m_tType = eType;
}

CBossMonster::~CBossMonster()
{
}

void CBossMonster::Initialize(void)
{
	m_tInfo.fCX = 268.f;
	m_tInfo.fCY = 255.f;

	MTime = GetTickCount();

	m_bSearch = false;

	m_tInfo.m_fSpeed = 10.f;
	m_tInfo.m_iHp = 30;
	currentState = None;
	behaviorState = Exit;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BossR.bmp", L"BossR");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BossL.bmp", L"BossL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MoveL.bmp", L"MoveL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/AttackL.bmp", L"AttackL");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Die.bmp", L"Die");
	QueryPerformanceFrequency(&timer);
	QueryPerformanceCounter(&start);
}

void CBossMonster::Release(void)
{
}

int CBossMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	

	if (m_bSearch)
	{
		if (MTime + 200 < GetTickCount())
		{
			BehaviorUpdate();
			MTime = GetTickCount();
		}
		
	}
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBossMonster::Late_Update(void)
{
	if (m_tInfo.m_iHp <= 10)
	{
		m_bSearch = false;
	}
	if (m_tInfo.m_iHp == 0)
	{
		static_cast<CPlayer*>(m_tTarget)->Set_Kill();
		Set_Dead();
	}
	int ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	if (ScrollX < -5100 && m_tInfo.m_iHp >= 14)
	{
		m_bSearch = true;
	}

	
}

void CBossMonster::Render(HDC hDC)
{
	if (m_tInfo.m_iHp < 15)
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Die");

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
			RGB(255, 255, 255));			// 제거하고자 하는 색상
	}
	else
	{
		switch (currentState)
		{
		case Pattern3:
		{
			HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MoveL");

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
				RGB(255, 255, 255));			// 제거하고자 하는 색상
		}
		break;
		case Pattern2:
		{
			HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BossL");

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
				RGB(255, 255, 255));			// 제거하고자 하는 색상
		}
		break;
		case Pattern1:
		{
			HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"AttackL");

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
				RGB(255, 255, 255));			// 제거하고자 하는 색상
		}
		break;
		case None:
		{
			HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MoveL");

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
				RGB(255, 255, 255));			// 제거하고자 하는 색상
		}
		break;
		}
	}
		
	
	/*HBRUSH	brush;
	HGDIOBJ h_old_brush;

	brush = CreateSolidBrush(RGB(100, 100, 100));
	h_old_brush = SelectObject(hDC, brush);

	int ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);*/
}

void CBossMonster::BehaviorUpdate() {

	switch (behaviorState)
	{
	case Enter:
		BehaviorEnter();
		break;

	case Execute:
		BehaviorExecute();
		break;

	case Exit:
		BehaviorExit();
		break;
	}
}

void CBossMonster::RandomPattern()
{
	srand(unsigned(time(nullptr)));

	currentState = State((rand() % None));
}

void CBossMonster::BehaviorEnter()
{
	if (!m_tTarget)
		return;

	switch (currentState)
	{

	case Pattern2:
		if (m_tTarget)
		{
			targetPosition.x = m_tTarget->Get_Info().fX;
			targetPosition.y = m_tTarget->Get_Info().fY;
		}
		else {
			targetPosition.x = originPosition.x;
			targetPosition.y = originPosition.y;
		}

		break;
	}
	

	behaviorState = Execute;
}

void CBossMonster::BehaviorExecute()
{
	float m_fDeltaTime;

	switch (currentState)
	{
	case Pattern3:
	
		if (TargetMove()) {
			behaviorState = Exit;
			return;
		}
		break;

	case Pattern1:
		QueryPerformanceCounter(&end);
		m_fDeltaTime = (end.QuadPart - start.QuadPart) / (float)timer.QuadPart;

		if ((int)m_fDeltaTime / 2 > 0)
		{
			PatternNormalShot();
			QueryPerformanceCounter(&start);
		}
		break;
	case Pattern2:
		QueryPerformanceCounter(&end);
		m_fDeltaTime = (end.QuadPart - start.QuadPart) / (float)timer.QuadPart;

		if ((int)m_fDeltaTime % 2 > 0)
		{
			PatternWideShot();
			QueryPerformanceCounter(&start);
		}
		break;
	}

	behaviorState = Exit;

}

void CBossMonster::BehaviorExit()
{

	switch (currentState) 
	{
	case Pattern1:
	case Pattern2:
		RandomPattern();
		currentState = None;
		break;

	case Pattern3:
		currentState = Pattern2;
		break;

	case None:
		RandomPattern();
		break;
	}

	behaviorState = Enter;
}

bool CBossMonster::TargetMove()
{
	float distX = targetPosition.x - m_tInfo.fX;
	float distY = targetPosition.y - m_tInfo.fY;

	float distance = sqrtf(distX * distX + distY * distY);

	if (distance < 5)
	{
		return true;
	}
	if (rand() % 2 == 0)	
		m_tInfo.fX += (distX / distance) * m_tInfo.m_fSpeed;
	else
		m_tInfo.fX -= (distX / distance) * m_tInfo.m_fSpeed;
	//m_tInfo.fY += (distY / distance) * m_tInfo.m_fSpeed;

	return false;
}

void CBossMonster::PatternNormalShot()
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create();
	pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CBullet*>(pBullet)->Set_Type(TYPE_MONSTER_BULLET);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBullet);
}

void CBossMonster::PatternWideShot()
{
	int degree = 0;

	while (degree < 360)
	{
		CObj* pBullet = CAbstractFactory<CBullet>::Create();
		pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		dynamic_cast<CBullet*>(pBullet)->Set_Type(TYPE_MONSTER_BULLET);
		dynamic_cast<CBullet*>(pBullet)->Set_Dir(cosf(degree * PI / 180.f), sinf(degree * PI / 180.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBullet);
		degree += 10;
	}

}

void CBossMonster::PatternMoveToPlayer()
{
	if (m_tTarget) 
	{
		targetPosition.x = m_tTarget->Get_Info().fX;
		//targetPosition.y = m_tTarget->Get_Info().fY;
	}
	else 
	{
		targetPosition.x = originPosition.x;
		//targetPosition.y = originPosition.y;
	}
}
