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
	m_tRect.left = m_tInfo.fX - m_tInfo.fCX * 0.5;
	m_tRect.right = m_tInfo.fX + m_tInfo.fCX * 0.5;
	m_tRect.top = m_tInfo.fY - m_tInfo.fCY * 0.5;
	m_tRect.bottom = m_tInfo.fY + m_tInfo.fCY * 0.5;
}

*/