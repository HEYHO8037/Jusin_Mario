#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include"Hurdle.h"
#include"AbstractFactory.h"



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
		
		m_ObjList[OBJ_HURDLE].push_back(CAbstractFactory<CHurdle>::Create(200.f, 575.f, TYPE_HUR_FIXED));
		//�ؿ��ʿ��ؿ�
		//CObjMgr::Get_Instance()->Add_Object(OBJ_HURDLE, CAbstractFactory<CHurdle>::Create(250.f, 575.f, TYPE_HUR_FLOAT));
		//CObjMgr::Get_Instance()->Add_Object(OBJ_HURDLE, CAbstractFactory<CHurdle>::Create(400.f, 375.f, TYPE_HUR_ITEM));
		//CObjMgr::Get_Instance()->Add_Object(OBJ_HURDLE, CAbstractFactory<CHurdle>::Create(450.f, 575.f, TYPE_HUR_STACK));

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
	c++11�� ���� �������� for-each���� �ſ� ����ϸ� �ݺ����� �߰��� �������
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


