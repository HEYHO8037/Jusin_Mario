#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include"Hurdle.h"
#include "AbstractFactory.h"
#include "Item.h"
#include "Monster.h"
#include "CollisionMgr.h"
#include "Player.h"


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

	if (eID == OBJ_PLAYER)
	{
		//ITEM CREATE
		m_ObjList[OBJ_ITEM].push_back(CAbstractFactory<CItem>::Create(200.f, 200.f, TYPE_ITEM_GROW, pObj));
		m_ObjList[OBJ_ITEM].push_back(CAbstractFactory<CItem>::Create(200.f, 200.f, TYPE_ITEM_GROW, pObj));
	
		//MONSTER CREATE
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(400.f, 600.f, TYPE_MONSTER_MOVE, pObj));
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(600.f, 700.f, TYPE_MONSTER_TURTLE, pObj));
    
	    //HURDLE CREATE
    	m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(200.f, 375.f, TYPE_HUR_FIXED, pObj));
		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(50.f, 575.f, TYPE_HUR_FIXED, pObj));

		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(100.f, 575.f, TYPE_HUR_FLOAT, pObj));
		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(400.f, 375.f, TYPE_HUR_ITEM, pObj));
		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(600.f, 575.f, TYPE_HUR_STACK, pObj));
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

	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Get_Instance()->Collision_Player_Huddle();

	
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


