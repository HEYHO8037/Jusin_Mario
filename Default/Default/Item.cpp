#include "stdafx.h"
#include "Item.h"


CItem::CItem()
	:m_ItemType(TYPE_END)
{
}

CItem::CItem(TYPE _eType)
{
	m_ItemType = _eType;
}

CItem::~CItem()
{
	Release();
}

void CItem::Initialize(void)
{
	//���� ������
	if (m_ItemType == TYPE_ITEM_GROW)
	{
		m_tInfo.fCX = 30.f;
		m_tInfo.fCY = 30.f;

		m_tInfo.m_fSpeed = 4.f; //��������۸� �ӵ��߰�
	}

	//�Ѿ� ���� ������
	if (m_ItemType == TYPE_ITEM_BULLET)
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

	switch (m_ItemType)
	{
	case TYPE_ITEM_GROW : //���� ������
		brush = CreateSolidBrush(RGB(255, 47, 47));
		h_old_brush = SelectObject(hDC, brush);
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, h_old_brush);
		DeleteObject(brush);
		break;

	case TYPE_ITEM_BULLET: // �Ѿ� ������
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