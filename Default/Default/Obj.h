#pragma once

#include "stdafx.h"
#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize(void) PURE;
	virtual void Release(void) PURE;
	virtual int Update(void) PURE;
	virtual void Late_Update(void) PURE;
	virtual void Render(HDC hDC) PURE;
	void Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX, m_tInfo.fY = _fY; }
	
	const INFO& Get_Info() { return m_tInfo; }
	const RECT& Get_Rect() { return m_tRect; }
	void Set_Dead() { m_bDead = true; }

protected:
	void Update_Rect();
protected:
	INFO m_tInfo;
	RECT m_tRect;
	CObj* m_tTarget;
	bool m_bDead;

};