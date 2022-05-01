#pragma once
#include "Obj.h"
class CBossMonster :
	public CObj
{
public:
	CBossMonster();
	virtual ~CBossMonster();

public:
	virtual void Initialize(void) override;
	virtual void Release(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;

public:
	void SetPlayerInfo(const CObj* pPlayer);

private:
	void PatternNormalShot();
	void PatternWideShot();
	void PatternMoveToPlayer();

private:
	LARGE_INTEGER timer;
	LARGE_INTEGER start;
	LARGE_INTEGER end;

	const CObj* m_pPlayer;


};

