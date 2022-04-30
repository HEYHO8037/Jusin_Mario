#pragma once
\
#include "Obj.h"

class CBullet : public CObj
{
public:
	CBullet();
	CBullet(float fX, float fY, BULLET_TYPE eType);
	CBullet(BULLET_TYPE eType);
	virtual ~CBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void Late_Update(void);
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	BULLET_TYPE m_eType;
	
};