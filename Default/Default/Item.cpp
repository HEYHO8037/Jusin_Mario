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
	//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	if (m_tType == TYPE_ITEM_GROW)
	{
		m_tInfo.fCX = 49.f;
		m_tInfo.fCY = 47.f;	
		
		m_bDead = false;
		 //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Û¸ï¿?ï¿½Óµï¿½ï¿½ß°ï¿½
		


	}

	//ï¿½Ñ¾ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
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


	//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	if (m_tType == TYPE_ITEM_GROW)
	{
		 //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Û¸ï¿?ï¿½Óµï¿½ï¿½ß°ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½Ì°ï¿½ ï¿½ï¿½ï¿½ï¿½
		//m_tInfo.fX -= m_tInfo.m_fSpeed;
	}

	if (m_tType == TYPE_ITEM_BULLET) // ï¿½Ñ¾ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
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
	case TYPE_ITEM_GROW : //ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"GrowItem");

		GdiTransparentBlt(hDC, 					// º¹»ç ¹ŞÀ», ÃÖÁ¾ÀûÀ¸·Î ±×¸²À» ±×¸± DC
			int(m_tRect.left),	// 2,3 ÀÎÀÚ :  º¹»ç¹ŞÀ» À§Ä¡ X, Y
			int(m_tRect.top),
			int(m_tInfo.fCX),				// 4,5 ÀÎÀÚ : º¹»ç¹ŞÀ» °¡·Î, ¼¼·Î ±æÀÌ
			int(m_tInfo.fCY),
			hMemDC,							// ºñÆ®¸ÊÀ» °¡Áö°í ÀÖ´Â DC
			0,								// ºñÆ®¸Ê Ãâ·Â ½ÃÀÛ ÁÂÇ¥, X,Y
			0,
			(int)m_tInfo.fCX,				// º¹»çÇÒ ºñÆ®¸ÊÀÇ °¡·Î, ¼¼·Î ±æÀÌ
			(int)m_tInfo.fCY,
			RGB(0, 0, 255));			// Á¦°ÅÇÏ°íÀÚ ÇÏ´Â »ö»ó
	}
		break;

	case TYPE_ITEM_BULLET: // ï¿½Ñ¾ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BulletItem");

		GdiTransparentBlt(hDC, 					// º¹»ç ¹ŞÀ», ÃÖÁ¾ÀûÀ¸·Î ±×¸²À» ±×¸± DC
			int(m_tRect.left),	// 2,3 ÀÎÀÚ :  º¹»ç¹ŞÀ» À§Ä¡ X, Y
			int(m_tRect.top),
			int(m_tInfo.fCX),				// 4,5 ÀÎÀÚ : º¹»ç¹ŞÀ» °¡·Î, ¼¼·Î ±æÀÌ
			int(m_tInfo.fCY),
			hMemDC,							// ºñÆ®¸ÊÀ» °¡Áö°í ÀÖ´Â DC
			0,								// ºñÆ®¸Ê Ãâ·Â ½ÃÀÛ ÁÂÇ¥, X,Y
			0,
			(int)m_tInfo.fCX,				// º¹»çÇÒ ºñÆ®¸ÊÀÇ °¡·Î, ¼¼·Î ±æÀÌ
			(int)m_tInfo.fCY,
			RGB(0, 0, 255));			// Á¦°ÅÇÏ°íÀÚ ÇÏ´Â »ö»ó
	}
		break;

	case TYPE_ITEM_STAR: //ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ItemStar");

		GdiTransparentBlt(hDC, 					// º¹»ç ¹ŞÀ», ÃÖÁ¾ÀûÀ¸·Î ±×¸²À» ±×¸± DC
			int(m_tRect.left),	// 2,3 ÀÎÀÚ :  º¹»ç¹ŞÀ» À§Ä¡ X, Y
			int(m_tRect.top),
			int(m_tInfo.fCX),				// 4,5 ÀÎÀÚ : º¹»ç¹ŞÀ» °¡·Î, ¼¼·Î ±æÀÌ
			int(m_tInfo.fCY),
			hMemDC,							// ºñÆ®¸ÊÀ» °¡Áö°í ÀÖ´Â DC
			0,								// ºñÆ®¸Ê Ãâ·Â ½ÃÀÛ ÁÂÇ¥, X,Y
			0,
			(int)m_tInfo.fCX,				// º¹»çÇÒ ºñÆ®¸ÊÀÇ °¡·Î, ¼¼·Î ±æÀÌ
			(int)m_tInfo.fCY,
			RGB(0, 0, 255));			// Á¦°ÅÇÏ°íÀÚ ÇÏ´Â »ö»ó
	}
	break;

	default:
		break;
	}


}
