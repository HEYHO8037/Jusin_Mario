#include "stdafx.h"
#include "BossMonster.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"


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
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;

	m_tInfo.m_fSpeed = 10.f;
	m_tInfo.m_iHp = 1000;
	currentState = None;
	behaviorState = Exit;

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


	BehaviorUpdate();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossMonster::Late_Update(void)
{


}

void CBossMonster::Render(HDC hDC)
{
	HBRUSH	brush;
	HGDIOBJ h_old_brush;

	brush = CreateSolidBrush(RGB(100, 100, 100));
	h_old_brush = SelectObject(hDC, brush);

	int ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	Rectangle(hDC, m_tRect.left + ScrollX, m_tRect.top, m_tRect.right + ScrollX, m_tRect.bottom);
	
	SelectObject(hDC, h_old_brush);
	DeleteObject(brush);
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

	case Return:
		targetPosition.x = originPosition.x;
		targetPosition.y = originPosition.y;
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
	case Return:
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
	case Return:
		RandomPattern();
		currentState = None;
		break;

	case Pattern3:
		currentState = Return;
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

	m_tInfo.fX += (distX / distance) * m_tInfo.m_fSpeed;
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
		targetPosition.y = m_tTarget->Get_Info().fY;
	}
	else 
	{
		targetPosition.x = originPosition.x;
		targetPosition.y = originPosition.y;
	}
}
