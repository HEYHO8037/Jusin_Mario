#include "stdafx.h"
#include "BossMonster.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"


CBossMonster::CBossMonster()
{
}


CBossMonster::~CBossMonster()
{
}

void CBossMonster::Initialize(void)
{
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;
	m_tInfo.m_fAngle = -1;

	m_tInfo.m_fSpeed = 10.f;
	m_tInfo.m_iHp = 1000;
	QueryPerformanceFrequency(&timer);
}

void CBossMonster::Release(void)
{
}

int CBossMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	srand(time(NULL));

	int i = rand() % 4;
	switch (i)
	{
	case 0:
		PatternNormalShot();
		break;
	case 1:
		PatternWideShot();
		break;
	case 2:
		break;
	case 3:
		break;

	}



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

void CBossMonster::SetPlayerInfo(const CObj * pPlayer)
{
	m_pPlayer = pPlayer;
}

void CBossMonster::PatternNormalShot()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, TYPE_MONSTER_TURTLE));
}

void CBossMonster::PatternWideShot()
{
	float fDeltaTime = 0.f;
	int degree = 0;

	while (degree < 360)
	{
		CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, TYPE_MONSTER_TURTLE);
		dynamic_cast<CBullet*>(pBullet)->Set_Dir(cosf(degree * PI / 180.f), sinf(degree * PI / 180.f));
		CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBullet);

		degree += 10;
	}

}

void CBossMonster::PatternMoveToPlayer()
{

}
