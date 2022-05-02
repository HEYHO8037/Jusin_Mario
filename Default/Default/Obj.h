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
	void Set_Target(CObj* _pObj) { m_tTarget = _pObj; }
	const INFO& Get_Info() { return m_tInfo; }
	const RECT& Get_Rect() { return m_tRect; }
	
	void Set_Dead() { m_bDead = true; }
	bool Get_Dead() { return m_bDead; }

	const int& Get_Hp() { return m_tInfo.m_iHp; }
	void Set_HpPlus() { m_tInfo.m_iHp += 1; }
	void Set_HpMinus() { m_tInfo.m_iHp -= 1; }
	
	void Set_PostX(float _fX) { m_tInfo.fX += _fX; }
	void Set_PostY(float _fY) { m_tInfo.fY += _fY; }
	void Set_PosX(float _fX) { m_tInfo.fX = _fX; }
	void Set_PosY(float _fY) { m_tInfo.fY = _fY; }
	const TYPE Get_Type() { return m_tType; }

protected:
	void Update_Rect();
protected:
	INFO m_tInfo;
	RECT m_tRect;
	CObj* m_tTarget;
	TYPE m_tType;
	bool m_bDead;

};