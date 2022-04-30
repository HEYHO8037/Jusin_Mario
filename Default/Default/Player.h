#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void);
	virtual void Release(void);
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);

private:
	void OffSet();
	void Key_Update(void);
	void Jumping(void);
	bool m_bJump;
	bool m_bDoubleJump;
	float m_fTime;
	float m_fPower;
};

