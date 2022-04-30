#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{
}

CLine::CLine(const LINE & _tLineInfo)
{
	m_tLineInfo = _tLineInfo;
}

CLine::CLine(const LINEPOINT & _tLeftPoint, const LINEPOINT & _tRightPoint)
{
	m_tLineInfo.tLPoint = _tLeftPoint;
	m_tLineInfo.tRPoint = _tRightPoint;
}

CLine::~CLine()
{
}

const LINE & CLine::Get_LineInfo() const
{
	return m_tLineInfo;
}

void CLine::Render(HDC hDC)
{
	//int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	MoveToEx(hDC, (int)m_tLineInfo.tLPoint.fX, (int)m_tLineInfo.tLPoint.fY, nullptr);
	LineTo(hDC, (int)m_tLineInfo.tRPoint.fX, (int)m_tLineInfo.tRPoint.fY);
}
