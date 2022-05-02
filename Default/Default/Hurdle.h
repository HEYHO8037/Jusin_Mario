#pragma once
#include "Obj.h"
class CHurdle
	:public CObj
{
public:
	CHurdle();
	CHurdle(TYPE e_Type);
	~CHurdle();

public:
	virtual void Initialize(void) override;
	virtual void Release(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;

public:
	bool GetIsMove() { return m_bIsMove; }
	void SetMove(bool bIsMove) { m_bIsMove = bIsMove; }

private:
	bool m_bIsMove;
};

