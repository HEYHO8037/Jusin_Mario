#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static bool Check_Rect(CObj* pDest, CObj* pSour, float *pX, float *pY); // ��ü �ΰ� �浹 Ȯ�ο� �Լ�
	static bool Check_Sphere(CObj* pDest, CObj* pSour); // ellipse �浹 Ȯ�ο� �Լ�
	static void Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour); // ��ü �浹�� �����ϴ� �Լ�
	static void Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour); // ��ü �浹�� �����ϴ� �Լ�
	static void Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour); // ellipse�� ������� ��ü �浹�� �����ϴ� �Լ�
};

