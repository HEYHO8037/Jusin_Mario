#include "stdafx.h"
#include "Item.h"
#include "ScrollMgr.h"

CItem::CItem()
{
}

CItem::CItem(TYPE _eType)
{
	m_tType = _eType;
}

CItem::~CItem()
{
	Release();
}

void CItem::Initialize(void)
{
	//성장 아이템
	if (m_tType == TYPE_ITEM_GROW)
	{
		m_tInfo.fCX = 30.f;
		m_tInfo.fCY = 30.f;

		m_tInfo.m_fSpeed = 4.f; //성장아이템만 속도추가
	}

	//총알 생성 아이템
	if (m_tType == TYPE_ITEM_BULLET)
	{
		m_tInfo.fCX = 30.f;
		m_tInfo.fCY = 50.f;
	}

}

void CItem::Release(void)
{
}

int CItem::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	//성장 아이템
	if (m_tType == TYPE_ITEM_GROW)
	{
		m_tInfo.m_fSpeed = 4.f; //성장아이템만 속도추가, 움직이게 만듦
		m_tInfo.fX -= m_tInfo.m_fSpeed;
	}

	if (m_tType == TYPE_ITEM_BULLET) // 총알 아이템
	{

	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CItem::Late_Update(void)
{

}

void CItem::Render(HDC hDC)
{
	HBRUSH	brush;
	HGDIOBJ h_old_brush;
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	switch (m_tType)
	{
	case TYPE_ITEM_GROW : //성장 아이템
		brush = CreateSolidBrush(RGB(255, 47, 47));
		h_old_brush = SelectObject(hDC, brush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		break;

	case TYPE_ITEM_BULLET: // 총알 아이템
		brush = CreateSolidBrush(RGB(0, 210, 0));
		h_old_brush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		break;

	default:
		break;
	}


}
