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

	static bool Check_Rect(CObj* pDest, CObj* pSour, float *pX, float *pY); // ï¿½ï¿½Ã¼ ï¿½Î°ï¿½ ï¿½æµ¹ È®ï¿½Î¿ï¿½ ï¿½Ô¼ï¿½
	static bool Check_Sphere(CObj* pDest, CObj* pSour); // ellipse ï¿½æµ¹ È®ï¿½Î¿ï¿½ ï¿½Ô¼ï¿½
	static void Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour); // ï¿½ï¿½Ã¼ ï¿½æµ¹ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï´ï¿½ ï¿½Ô¼ï¿½
	static void Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour); // ï¿½ï¿½Ã¼ ï¿½æµ¹ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï´ï¿½ ï¿½Ô¼ï¿½
	static void Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour); // ellipseï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½Ã¼ ï¿½æµ¹ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï´ï¿½ ï¿½Ô¼ï¿½
	static void Collision_Monster_Huddle(list<CObj*> _Dest, list<CObj*> _Sour);
	
public:
	void Collision_Player_BossMonster();
	void Collision_Player_Bullet();
	void Collision_Monster_Bullet();
	void Collision_Player_Item();
	void Collision_Player_FixedHuddle();
	void Collision_Player_FloatHuddle();
	void Collision_Player_Huddle();
	void Collision_Bullet_Huddle();
	void Collision_Huddle_Huddle();



private:
	static CCollisionMgr* m_pInstance;
	static DWORD CTime;
	const list<CObj*> (*m_ObjList)[OBJ_END];
	CObj* m_pSaveObj;
};

