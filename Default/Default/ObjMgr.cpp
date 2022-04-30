#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "AbstractFactory.h"
#include "Item.h"
#include "Monster.h"
#include "CollisionMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Object(OBJID eID, CObj* pObj)
{
	if (pObj == nullptr) //���ڷ� ���� ��ü�� �����Ⱚ�̶�� �Լ�����
		return;
	m_ObjList[eID].push_back(pObj); // �ƴ϶�� ����Ʈ�� �߰�

	if (eID == OBJ_PLAYER)
	{
		//������ ����
		m_ObjList[OBJ_ITEM].push_back(CAbstractFactory<CItem>::Create(200.f, 200.f, TYPE_ITEM_GROW, pObj));
		m_ObjList[OBJ_ITEM].push_back(CAbstractFactory<CItem>::Create(200.f, 200.f, TYPE_ITEM_GROW, pObj));
	
		//���� ����
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(400.f, 600.f, TYPE_MONSTER_MOVE, pObj));
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(600.f, 700.f, TYPE_MONSTER_BULLET, pObj));

	}

}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJ_END; ++i) // ����Ʈ �迭�� ũ�⺸�� �۴ٸ� �ݺ�
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

	/*
	�������for��
	for(int i = 0; i < OBJ_END; ++i)
	{
	for(auto& iter : m_ObjList[i])
	{
	~~ ������� ������ �Ⱦ� ���� :
	c++11�� ���� �������� for-each���� �ſ� �����ϸ� �ݺ����� �߰��� �������
	�׸��� ������� ������ ������ ���� ����ü�̱� ������ �ּҰ������� �Ұ����ϴ�.
	}
	}
	*/

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


