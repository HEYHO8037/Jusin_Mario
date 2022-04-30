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
	TYPE Get_type(void) { return m_eMonsterType; }

private :
	TYPE m_eMonsterType;
	float m_fTemp;
};

