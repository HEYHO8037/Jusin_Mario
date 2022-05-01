#pragma once

#include "Obj.h"

class CCollisionMgr
{
private:
	CCollisionMgr();
	~CCollisionMgr();

public:
	void SetObjList(const list<CObj*>(*pObjList)[OBJ_END]);

public:
	static CCollisionMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CCollisionMgr;
			
		}

		return m_pInstance;
	}

	static void Delete_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

	static bool Check_Rect(CObj* pDest, CObj* pSour, float *pX, float *pY); // ��ü �ΰ� �浹 Ȯ�ο� �Լ�
	static bool Check_Sphere(CObj* pDest, CObj* pSour); // ellipse �浹 Ȯ�ο� �Լ�
	static void Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour); // ��ü �浹�� �����ϴ� �Լ�
	static void Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour); // ��ü �浹�� �����ϴ� �Լ�
	static void Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour); // ellipse�� ������� ��ü �浹�� �����ϴ� �Լ�
	
public:
	void Collision_Player_Monster();
	void Collision_Player_Bullet();
	void Collision_Monster_Bullet();
	void Collision_Player_Item();
	void Collision_Player_Huddle();
	void Collision_Monster_Huddle();


private:
	static CCollisionMgr* m_pInstance;
	static DWORD CTime;
	const list<CObj*> (*m_ObjList)[OBJ_END];
};

