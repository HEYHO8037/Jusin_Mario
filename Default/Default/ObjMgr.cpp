#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include"Hurdle.h"
#include "AbstractFactory.h"
#include "Item.h"
#include "Monster.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "BossMonster.h"



CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
	CCollisionMgr::Get_Instance()->SetObjList(&m_ObjList);
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Object(OBJID eID, CObj* pObj)

{
	if (pObj == nullptr) 
		return;
	m_ObjList[eID].push_back(pObj);
	OTime = GetTickCount();
	if (eID == OBJ_PLAYER)
	{
		//ITEM CREATE
		m_ObjList[OBJ_ITEM].push_back(CAbstractFactory<CItem>::Create(200.f, 580.f, TYPE_ITEM_GROW, pObj));
		m_ObjList[OBJ_ITEM].push_back(CAbstractFactory<CItem>::Create(350.f, 580.f, TYPE_ITEM_BULLET, pObj));
	
		//MONSTER CREATE
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(400.f, 575.f, TYPE_MONSTER_MOVE, pObj));
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(1000.f, 566.f, TYPE_MONSTER_TURTLE, pObj));
    
	    //HURDLE CREATE
		//움직이는 허들
		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(1480.f, 575.f, TYPE_HUR_FLOAT, pObj));

		//움직이는 허들을 통해 점프하기
    	m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(1730.f, 525.f, TYPE_HUR_FIXED, pObj));
		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(1730.f, 575.f, TYPE_HUR_FIXED, pObj));
		
		//아이템 허들과 안움직이는 허들 ( 아이템 먹기 )
		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(1980.f, 425.f, TYPE_HUR_FIXED, pObj));
		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(2030.f, 425.f, TYPE_HUR_ITEM, pObj));
		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(2080.f, 425.f, TYPE_HUR_FIXED, pObj));

		//안움직이는 허들
		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(2480.f, 525.f, TYPE_HUR_FIXED, pObj));
		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(2480.f, 575.f, TYPE_HUR_FIXED, pObj));
		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(2480.f, 475.f, TYPE_HUR_FIXED, pObj));

		//거북이(허들 사이에 움직임)
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(2605.f, 566.f, TYPE_MONSTER_TURTLE, pObj));

		//안움직이는 허들
		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(2730.f, 525.f, TYPE_HUR_FIXED, pObj));
		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(2730.f, 575.f, TYPE_HUR_FIXED, pObj));
		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(2730.f, 475.f, TYPE_HUR_FIXED, pObj));
		
		//굴뚝(임시)
		//m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(2030.f, 575.f, TYPE_HUR_STACK, pObj));
		//보스(임시)
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CBossMonster>::Create(600.f, 575.f, TYPE_BOSS, pObj));

	}

}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJ_END; ++i) 
	{
		for (auto& iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{

			Safe_Delete<CObj*>(*iter);
			iter = m_ObjList[i].erase(iter);
		}

	}
}

void CObjMgr::Update()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{
			int Result = (*iter)->Update();

			if (Result == OBJ_DEAD)
			{
				Safe_Delete(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
			++iter;
		}
	}
	
}

void CObjMgr::Late_Update()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{
			(*iter)->Late_Update();
			++iter;
		}
	}
  
	//CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);

	if (OTime + 30 < GetTickCount())
	{
		CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
		CCollisionMgr::Collision_RectEx(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
		CCollisionMgr::Collision_Monster_Huddle(m_ObjList[OBJ_HURDLE], m_ObjList[OBJ_MONSTER]);
		CCollisionMgr::Get_Instance()->Collision_Player_BossMonster();
		//CCollisionMgr::Get_Instance()->Collision_Player_FixedHuddle();
		CCollisionMgr::Get_Instance()->Collision_Player_FloatHuddle();

		CCollisionMgr::Get_Instance()->Collision_Player_Item();
		CCollisionMgr::Get_Instance()->Collision_Bullet_Huddle();
		CCollisionMgr::Get_Instance()->Collision_Huddle_Huddle();
		OTime = GetTickCount();
	}
	
	
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{
			(*iter)->Render(hDC);
			++iter;
		}
	}
}


