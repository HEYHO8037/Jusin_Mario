#include "stdafx.h"
#include "Item.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

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
	//���� ������
	if (m_tType == TYPE_ITEM_GROW)
	{
		m_tInfo.fCX = 49.f;
		m_tInfo.fCY = 47.f;	
		
		m_bDead = false;
		 //��������۸�?�ӵ��߰�
		


	}

	//�Ѿ� ���� ������
	if (m_tType == TYPE_ITEM_BULLET)
	{
		m_tInfo.fCX = 48.f;
		m_tInfo.fCY = 53.f;
	
		m_bDead = false;
		
	}

	if (m_tType == TYPE_ITEM_STAR)
	{
		m_tInfo.fCX = 250.f;
		m_tInfo.fCY = 250.f;

		m_bDead = false;
	}

}

void CItem::Release(void)
{
}

int CItem::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	//���� ������
	if (m_tType == TYPE_ITEM_GROW)
	{
		 //��������۸�?�ӵ��߰�, �����̰� ����
		//m_tInfo.fX -= m_tInfo.m_fSpeed;
	}

	if (m_tType == TYPE_ITEM_BULLET) // �Ѿ� ������
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
	
	
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	
	switch (m_tType)
	{
	case TYPE_ITEM_GROW : //���� ������
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"GrowItem");

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top),
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(0, 0, 255));			// �����ϰ��� �ϴ� ����
	}
		break;

	case TYPE_ITEM_BULLET: // �Ѿ� ������
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BulletItem");

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top),
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(0, 0, 255));			// �����ϰ��� �ϴ� ����
	}
		break;

	case TYPE_ITEM_STAR: //���� ������
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ItemStar");

		GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top),
			int(m_tInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
			int(m_tInfo.fCY),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(0, 0, 255));			// �����ϰ��� �ϴ� ����
	}
	break;

	default:
		break;
	}


}
