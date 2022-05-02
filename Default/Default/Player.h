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

	void Update_PRect();
	float Get_Power() { return m_fPower; }
	float Get_GroundPoint() { return m_fGroundPoint;  }
	void Set_GroundPoint(float fPoint) { m_fGroundPoint = fPoint; }
	void Set_Falling(bool bIsFalling) { m_bIsFalling = bIsFalling; }
	void Falling();
	bool Get_Jump() { return m_bJump;  }
	bool Get_m_bRight() { return m_bRight; }
	void Set_Size();
	void Set_Kill() { m_bBossKill = true; }
	bool Get_Kill() { return m_bBossKill; }
	void Set_Star() { m_bStar = true; }
	bool Get_Star() { return m_bStar; }

private:
	void OffSet();
	void Key_Update(void);
	void Jumping(void);
	bool m_bJump;
	bool m_mJump;
	bool m_bIsFalling;
	float m_fTime;
	float m_mTime;
	float m_fPower;
	bool m_bRight;
	bool m_bBoss;
	bool m_bBossKill;
	bool m_bStar;
	TYPE m_tWeapon;
	DWORD PTime;
	float m_fGroundPoint;
	TCHAR m_szFPS[64];

};

