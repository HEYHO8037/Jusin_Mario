#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static bool Check_Rect(CObj* pDest, CObj* pSour, float *pX, float *pY); // 객체 두개 충돌 확인용 함수
	static bool Check_Sphere(CObj* pDest, CObj* pSour); // ellipse 충돌 확인용 함수
	static void Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour); // 객체 충돌시 실행하는 함수
	static void Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour); // 객체 충돌시 실행하는 함수
	static void Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour); // ellipse로 만들어진 객체 충돌시 삭제하는 함수
};

