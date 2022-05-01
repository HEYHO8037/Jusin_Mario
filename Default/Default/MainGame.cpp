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

	HBITMAP backBitmap = NULL;
	HBITMAP backBitmapStage = NULL;
	HDC backHDC = CreateCompatibleDC(m_hDC);
	backBitmap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY );
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

void CMainGame::Release(void)
{
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);	
}


