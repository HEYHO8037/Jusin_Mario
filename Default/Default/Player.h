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

public:
	void Equip_Weapon() 
	{ 
		m_tWeapon = TYPE_GUN_WEAPON;
	}

	void UnEquip_Weapon()
	{
		m_tWeapon = TYPE_NO_WEAPON;
	}


public:
	void Set_Power(float fPower) { m_fPower = fPower; }
	void MJump();
	void Set_Jump() { m_mJump = true;
	m_bJump = false;
	}

private:
	void OffSet();
	void Key_Update(void);
	void Jumping(void);
	bool m_bJump;
	bool m_mJump;
	float m_fTime;
	float m_mTime;
	float m_fPower;
	TYPE m_tWeapon;
	DWORD PTime;
};

