#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
{
}


CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left = LONG(m_tInfo.fX - m_tInfo.fCX * 0.5);
	m_tRect.right = LONG(m_tInfo.fX + m_tInfo.fCX * 0.5);
	m_tRect.top = LONG(m_tInfo.fY - m_tInfo.fCY * 0.5);
	m_tRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY * 0.5);
}

