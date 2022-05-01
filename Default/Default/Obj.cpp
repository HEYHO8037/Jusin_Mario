#include "stdafx.h"
#include "Obj.h"
#include "ScrollMgr.h"


CObj::CObj()
{
}


CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	int ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	m_tRect.left = LONG(m_tInfo.fX - m_tInfo.fCX * 0.5 + ScrollX);
	m_tRect.right = LONG(m_tInfo.fX + m_tInfo.fCX * 0.5 + ScrollX);
	m_tRect.top = LONG(m_tInfo.fY - m_tInfo.fCY * 0.5);
	m_tRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY * 0.5);
}

