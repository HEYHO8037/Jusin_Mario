#include "stdafx.h"
#include "Hurdle.h"


CHurdle::CHurdle()
{
}
CHurdle::CHurdle(TYPE e_Type) 
{
	m_tType = e_Type;

}
CHurdle::~CHurdle()
{
	Release();
}

void CHurdle::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	switch (m_tType)
	{
	case TYPE_HUR_FIXED:
		m_bIsMove = false;
		break;
	case TYPE_HUR_FLOAT:
		m_bIsMove = true;
		break;
	case TYPE_HUR_ITEM:
		m_bIsMove = true;
		break;
	case TYPE_HUR_STACK:
		m_bIsMove = true;
		break;
	}
}

int CHurdle::Update(void)
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

	Update_Rect();

	return OBJ_NOEVENT;
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

	switch (m_tType)
	{
	case TYPE_HUR_FIXED://����-����
		brush = CreateSolidBrush(RGB(128, 64, 0));	//����
		h_old_brush = SelectObject(hDC, brush);		
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);//����
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		break;

	case TYPE_HUR_FLOAT://������-��������
		brush = CreateSolidBrush(RGB(193, 113, 17));
		h_old_brush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		break;
	
	case TYPE_HUR_ITEM://������-�����
		brush = CreateSolidBrush(RGB(255, 255, 0));
		h_old_brush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		break;

	case TYPE_HUR_STACK://����-�ʷϻ�
		brush = CreateSolidBrush(RGB(0, 128, 0));
		h_old_brush = SelectObject(hDC, brush);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		break;
		
	}
}
void CHurdle::Release(void)
{

}

//void CHurdle::Moving_Hurdle(void)
//{
//}
