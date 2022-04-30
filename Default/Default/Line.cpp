#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{
}

CLine::CLine(const LINE & _tLineInfo)
{
	m_tLineInfo = _tLineInfo;
}

CLine::CLine(const DotPoint & _tLeftPoint, const DotPoint & _tRightPoint)
{
	m_tLineInfo.LeftPoint = _tLeftPoint;
	m_tLineInfo.RightPoint = _tRightPoint;
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

	MoveToEx(hDC, (int)m_tLineInfo.LeftPoint.fX, (int)m_tLineInfo.LeftPoint.fY, nullptr);
	LineTo(hDC, (int)m_tLineInfo.RightPoint.fX, (int)m_tLineInfo.RightPoint.fY);
}
