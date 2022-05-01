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

//	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	
	//������ ����
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create(200.f, 200.f, TYPE_ITEM_GROW));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CItem>::Create(250.f, 200.f, TYPE_ITEM_BULLET));
	//���� ����
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::Create(400.f, 600.f, TYPE_MONSTER_MOVE));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CBossMonster>::Create(450.f, 600.f, NULL));

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
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	CLineMgr::Get_Instance()->Render(m_hDC);
	CObjMgr::Get_Instance()->Render(m_hDC);

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

}

void CMainGame::Release(void)
{
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CLineMgr::Get_Instance()->Destroy_Instance();
	CObjMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);	
}


