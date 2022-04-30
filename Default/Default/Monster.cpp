#include "stdafx.h"
#include "Monster.h"
#include "ScrollMgr.h"

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

	//총알 발사 몬스터, 플레이어와의 거리가 일정 수치에 들어서면 추격
	if (m_eMonsterType == TYPE_MONSTER_BULLET)
	{

		float fWidth = m_tTarget->Get_Info().fX - m_tInfo.fX; // 두 중점사이의 밑변
		float fHeight = m_tTarget->Get_Info().fY - m_tInfo.fY; // 두 중점사이의 높이

		float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight); // 빗변

		float fRadian = acosf(fWidth / fDiagonal); //라디안 구하기, 각도 계속 구해오기위함
		
		if (600.f > fDiagonal && 200.f <= fDiagonal) // 두 점 사이의 거리가 400이하일때 몬스터가 움직임
		{
			m_tInfo.fX -= m_tInfo.m_fSpeed;

			if (500 >= m_tInfo.fX || 700 < m_tInfo.fX)
			{
				m_tInfo.m_fSpeed *= -1.f;

			}
		}
		
		if( 200.f > fDiagonal)
			m_tInfo.fX += m_tInfo.m_fSpeed * cosf(fRadian); // 두점 사이의 거리가 200 미만일때 플레이어 쫓아다니도록

	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	//이동몬스터 자기 중점에서 100이내로 움직이게 설정
	if (m_eMonsterType == TYPE_MONSTER_MOVE)
	{
		//몬스터 생성시 인자값으로 넣어준 f, X값에서 - 100, +100
		if ( 200 >= m_tRect.left || 600 <= m_tRect.right)
		{
			m_tInfo.m_fSpeed *= -1.f;
		}
	}

	//총알 발사 몬스터
	if (m_eMonsterType == TYPE_MONSTER_BULLET)
	{
	
	}
}

void CMonster::Render(HDC hDC)
{

	HBRUSH	brush;
	HGDIOBJ h_old_brush;

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	switch (m_eMonsterType)
	{
	case TYPE_MONSTER_MOVE: //이동몬스터
		brush = CreateSolidBrush(RGB(255, 128, 64));
		h_old_brush = SelectObject(hDC, brush);
		Ellipse(hDC, m_tRect.left+iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		break;

	case TYPE_MONSTER_BULLET: // 쏘는 몬스터
		brush = CreateSolidBrush(RGB(64, 128, 128));
		h_old_brush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left + iScrollX, m_tRect.top, m_tRect.right + iScrollX, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		break;

	default:
		break;
	}

}
