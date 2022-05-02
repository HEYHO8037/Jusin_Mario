#include "stdafx.h"
#include "Cloud.h"


CCloud::CCloud()
{
}

CCloud::CCloud(TYPE _eType)
{
	m_tType = _eType;
}


CCloud::~CCloud()
{
	Release();
}

void CCloud::Initialize(void)
{
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 40.f;

	m_tInfo.m_fSpeed = 2.f;
}

int CCloud::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX -= m_tInfo.m_fSpeed;

	srand(unsigned(time(nullptr)));

	if (0 > m_tRect.right)
	{
		m_tInfo.fX = float((rand() % 400 + 1300.f)) + float((rand() % 400 + 100.f)) + 800.f;
		m_tInfo.fY = float((rand() % 30 + 100)) + float((rand() % 60 + 50));

	}
	Update_Rect();
	return OBJ_NOEVENT;
}

void CCloud::Late_Update(void)
{


}

void CCloud::Render(HDC hDC)
{



	HBRUSH	brush = CreateSolidBrush(RGB(255, 255, 255));
	HGDIOBJ h_old_brush = SelectObject(hDC, brush);
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	HGDIOBJ h_old_pen = SelectObject(hDC, pen);

	Ellipse(hDC, m_tRect.left, m_tRect.top + 20, m_tRect.right - 20, m_tRect.bottom + 20);
	Ellipse(hDC, m_tRect.left + 30, m_tRect.top + 20, m_tRect.right + 20, m_tRect.bottom + 20);
	Ellipse(hDC, m_tRect.left - 20, m_tRect.top + 10, m_tRect.right, m_tRect.bottom + 10);
	Ellipse(hDC, m_tRect.left + 40, m_tRect.top + 10, m_tRect.right + 40, m_tRect.bottom + 10);
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right + 20, m_tRect.bottom + 15);

	SelectObject(hDC, h_old_brush);
	SelectObject(hDC, h_old_pen);

	DeleteObject(brush);
	DeleteObject(pen);

}

void CCloud::Release(void)
{
}