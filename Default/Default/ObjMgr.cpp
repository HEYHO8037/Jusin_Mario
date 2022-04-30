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

void CObjMgr::Add_Object(OBJID eID, CObj* pObj)
{
	if (pObj == nullptr) //인자로 들어온 객체가 쓰레기값이라면 함수종료
		return;
	m_ObjList[eID].push_back(pObj); // 아니라면 리스트에 추가

}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJ_END; ++i) // 리스트 배열의 크기보다 작다면 반복
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
	범위기반for문
	for(int i = 0; i < OBJ_END; ++i)
	{
	for(auto& iter : m_ObjList[i])
	{
	~~ 범위기반 포문을 안쓴 이유 :
	c++11에 나온 문법으로 for-each문과 매우 흡사하며 반복도중 중간에 못멈춘다
	그리고 범위기반 포문의 변수는 원소 그자체이기 때문에 주소값접근이 불가능하다.
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


