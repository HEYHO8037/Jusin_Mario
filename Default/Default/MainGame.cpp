#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "Item.h"
#include "Monster.h"
#include "Player.h"
#include "Hurdle.h"
#include "BossMonster.h"
#include "BmpMgr.h"


CMainGame::CMainGame()
	: m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 64);
	m_iFPS = 0;
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

	CLineMgr::Get_Instance()->Initialize();
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/YoshiHouse.bmp", L"YoshiHouse");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BossStage.bmp", L"BossStage");
}

void CMainGame::Update(void)
{
	CObjMgr::Get_Instance()->Update();		
}

void CMainGame::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{

	int ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	if (ScrollX > 2000)
	{
		HDC		backHDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");
		HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"YoshiHouse");

		BitBlt(m_hDC, 0, 0, WINCX, WINCY, backHDC, 0, 0, SRCCOPY);

		BitBlt(backHDC, 0, 0, WINCX, WINCY, hGroundMemDC, 0, 0, SRCCOPY);
		 
		CLineMgr::Get_Instance()->Render(backHDC);
		CObjMgr::Get_Instance()->Render(backHDC);
		
	}

	else if (ScrollX < 2000 && ScrollX > -4400)
	{

		HBITMAP backBitmap = NULL;
		HBITMAP backBitmapStage = NULL;
		HDC backHDC = CreateCompatibleDC(m_hDC);
		backBitmap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
		backBitmapStage = (HBITMAP)SelectObject(backHDC, backBitmap);

		HBRUSH	brush;
		HGDIOBJ h_old_brush;

		brush = CreateSolidBrush(RGB(170, 233, 255));
		h_old_brush = SelectObject(backHDC, brush);
		Rectangle(backHDC, 0, 0, WINCX, WINCY);
		SelectObject(backHDC, h_old_brush);
		DeleteObject(brush);

		brush = CreateSolidBrush(RGB(113, 206, 77));
		h_old_brush = SelectObject(backHDC, brush);
		Rectangle(backHDC, 0, 600, WINCX, WINCY);
		SelectObject(backHDC, h_old_brush);
		DeleteObject(brush);


		brush = CreateSolidBrush(RGB(28, 19, 19));
		h_old_brush = SelectObject(backHDC, brush);
		Rectangle(backHDC, 0, 720, WINCX, 1440);
		SelectObject(backHDC, h_old_brush);
		DeleteObject(brush);

		brush = CreateSolidBrush(RGB(72, 89, 138));
		h_old_brush = SelectObject(backHDC, brush);
		Rectangle(backHDC, 0, 1320, WINCX, 1440);
		SelectObject(backHDC, h_old_brush);
		DeleteObject(brush);

		CLineMgr::Get_Instance()->Render(backHDC);
		CObjMgr::Get_Instance()->Render(backHDC);

		++m_iFPS;

		if (m_dwTime + 1000 < GetTickCount())
		{
			swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
			SetWindowText(g_hWnd, m_szFPS);

			m_iFPS = 0;
			m_dwTime = GetTickCount();
		}
		BitBlt(m_hDC, 0, 0, WINCX, WINCY, backHDC, 0, 0, SRCCOPY);
		DeleteObject(SelectObject(backHDC, backBitmapStage));
		DeleteDC(backHDC);

	}
	
	else if (ScrollX < -4400)
	{
		HDC		backHDC = CBmpMgr::Get_Instance()->Find_Image(L"Ground");
		HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BossStage");

		BitBlt(m_hDC, 0, 0, WINCX, WINCY, backHDC, 0, 0, SRCCOPY);

		BitBlt(backHDC, 0, 0, WINCX, WINCY, hGroundMemDC, 0, 0, SRCCOPY);

		CLineMgr::Get_Instance()->Render(backHDC);
		CObjMgr::Get_Instance()->Render(backHDC);
	}

	
}

void CMainGame::Release(void)
{
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);	
}


