#pragma once
#include "Obj.h"
class CUI
	:public CObj
{
public:
	CUI();
	~CUI();

public:
	virtual void Initialize(void) override;
	virtual void Release(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;



};

