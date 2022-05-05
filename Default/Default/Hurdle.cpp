#include "stdafx.h"
#include "Hurdle.h"
#include "BmpMgr.h"


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
	
	
	switch (m_tType)
	{
	case TYPE_HUR_FIXED:
		m_bIsMove = false;
		m_bIsItem = false;
		m_tInfo.fCX = 60.f;
		m_tInfo.fCY = 60.f;
		
		break;
	case TYPE_HUR_FLOAT:
		m_bIsMove = true;
		m_bIsItem = false;
		m_tInfo.fCX = 60.f;
		m_tInfo.fCY = 60.f;
		
		break;
	case TYPE_HUR_ITEM:
		m_bIsMove = true;
		m_bIsItem = false;
		m_tInfo.fCX = 60.f;
		m_tInfo.fCY = 60.f;
		
		break;
	case TYPE_HUR_STACKL:
		m_bIsMove = true;
		m_bIsItem = false;
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 200.f;
		break;
	case TYPE_HUR_STACKR:
		m_bIsMove = true;
		m_bIsItem = false;
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 200.f;
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
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"FixHurdle");
		GdiTransparentBlt(hDC, 				// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top),
			int(60),				// 4,5 ���� : ������� ����, ���� ����
			int(60),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
	}
		break;

	case TYPE_HUR_FLOAT://������-��������
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"FloatHurdle");
		GdiTransparentBlt(hDC, 				// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top),
			int(60),				// 4,5 ���� : ������� ����, ���� ����
			int(60),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(0, 255, 255));
	}
		break;
	
	case TYPE_HUR_ITEM://������-�����
		
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ItemHurdle");
		GdiTransparentBlt(hDC, 				// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top),
			int(60),				// 4,5 ���� : ������� ����, ���� ����
			int(60),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(0, 255, 255));
	}


		break;

	case TYPE_HUR_STACKL://����-�ʷϻ�
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"LOpenDoor");
		GdiTransparentBlt(hDC, 				// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top),
			int(100),				// 4,5 ���� : ������� ����, ���� ����
			int(200),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
		break;
	case TYPE_HUR_STACKR://����-�ʷϻ�
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ROpenDoor");
		GdiTransparentBlt(hDC, 				// ���� ����, ���������� �׸��� �׸� DC
			int(m_tRect.left),	// 2,3 ���� :  ������� ��ġ X, Y
			int(m_tRect.top),
			int(100),				// 4,5 ���� : ������� ����, ���� ����
			int(200),
			hMemDC,							// ��Ʈ���� ������ �ִ� DC
			0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
			0,
			(int)m_tInfo.fCX,				// ������ ��Ʈ���� ����, ���� ����
			(int)m_tInfo.fCY,
			RGB(255, 0, 255));
	}
	break;
		
	}
}
void CHurdle::Release(void)
{

}

//void CHurdle::Moving_Hurdle(void)
//{
//}
