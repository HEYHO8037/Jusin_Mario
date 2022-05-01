#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	CMonster(TYPE _eType);
	virtual ~CMonster();

public:
	virtual void Initialize(void) override;
	virtual void Release(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;

public:
	void Set_Minus_Hp(void) { m_tInfo.m_iHp -= 1; }
	void Set_Reverse(void) { m_tInfo.m_fSpeed *= -1.f; }
};

