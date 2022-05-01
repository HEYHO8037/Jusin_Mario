#pragma once

#include "Obj.h"

class CBullet : public CObj
{
public:
	CBullet();
	CBullet(TYPE eType);
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Set_Angle(float fAngle);
	void Set_Dir(float fX, float fY);

private:
	INFO m_tDir;
	
};