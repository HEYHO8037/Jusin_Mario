#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
	:m_eMonsterType(TYPE_END)
{
}

CMonster::CMonster(TYPE _eType)
{
	m_eMonsterType = _eType;
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	//이동 몬스터
	if (m_eMonsterType == TYPE_MONSTER_MOVE)
	{
		m_tInfo.fCX = 35.f;
		m_tInfo.fCY = 35.f;

		m_tInfo.m_fSpeed = 5.f; //성장아이템만 속도추가
	}

	//총알 발사 몬스터
	if (m_eMonsterType == TYPE_MONSTER_BULLET)
	{
		m_tInfo.fCX = 50.f;
		m_tInfo.fCY = 70.f;

		m_tInfo.m_fSpeed = 3.f;
	}


}

void CMonster::Release(void)
{
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_eMonsterType == TYPE_MONSTER_MOVE)
	{
		m_tInfo.fX += m_tInfo.m_fSpeed;
	}

	//총알 발사 몬스터
	if (m_eMonsterType == TYPE_MONSTER_BULLET)
	{
		m_tInfo.fX += m_tInfo.m_fSpeed;
	}


	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	if (m_eMonsterType == TYPE_MONSTER_MOVE)
	{
		if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right)
		{
			m_tInfo.m_fSpeed *= -1.f;
		}
	}

	//총알 발사 몬스터
	if (m_eMonsterType == TYPE_MONSTER_BULLET)
	{
		if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right)
		{
			m_tInfo.m_fSpeed *= -1.f;
		}
	}
}

void CMonster::Render(HDC hDC)
{

	HBRUSH	brush;
	HGDIOBJ h_old_brush;

	switch (m_eMonsterType)
	{
	case TYPE_MONSTER_MOVE: //이동몬스터
		brush = CreateSolidBrush(RGB(255, 128, 64));
		h_old_brush = SelectObject(hDC, brush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);

		break;

	case TYPE_MONSTER_BULLET: // 쏘는 몬스터
		brush = CreateSolidBrush(RGB(64, 128, 128));
		h_old_brush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		break;

	default:
		break;
	}

}
