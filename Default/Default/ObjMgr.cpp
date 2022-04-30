#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::AddObject(OBJID eID, CObj* pObj)
{
	if (pObj == nullptr) //���ڷ� ���� ��ü�� �����Ⱚ�̶�� �Լ�����
		return;
	m_ObjList[eID].push_back(pObj); // �ƴ϶�� ����Ʈ�� �߰�

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

int CObjMgr::Update()
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
	(*iter)->Update();
	++iter;
	}
	}
	return 0;
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


