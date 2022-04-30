#include "stdafx.h"
#include "Hurdle.h"


CHurdle::CHurdle()
{
}
CHurdle::CHurdle(HURDLETYPE e_Type) 
{
	m_eType = e_Type;

}
CHurdle::~CHurdle()
{
	Release();
}

void CHurdle::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	/*switch (m_eType)
	{
	case HUR_FIXED:	
		break;
	case HUR_FLOAT:
		break;
	case HUR_ITEM:
		break;
	}*/
}

void CHurdle::Update(void)
{
  /*switch (m_eType)
	{
	case HUR_FIXED:
		break;
	case HUR_FLOAT:
		break;
	case HUR_ITEM:
		break;
	*/	
}

void CHurdle::Late_Update(void)
{
	/*switch (m_eType)
	{
	case HUR_FIXED:
		break;
	case HUR_FLOAT:
		break;
	case HUR_ITEM:
		break;
	}*/
}

void CHurdle::Render(HDC hDC)
{
	HBRUSH   brush;
	HGDIOBJ h_old_brush;

	switch (m_eType)
	{
	case HUR_FIXED://고정-갈색
		brush = CreateSolidBrush(RGB(128, 64, 0));	//배경색
		h_old_brush = SelectObject(hDC, brush);		
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);//도형
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
	break;

	case HUR_FLOAT://움직임-검은색
		brush = CreateSolidBrush(RGB(0, 0, 0));
		h_old_brush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
	break;
	
	case HUR_ITEM://아이템-노란색
		brush = CreateSolidBrush(RGB(255, 255, 0));
		h_old_brush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
	break;
	}
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
void CHurdle::Release(void)
{

}

//void CHurdle::Moving_Hurdle(void)
//{
//}
