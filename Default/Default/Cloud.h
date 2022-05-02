#pragma once
#include "Obj.h"
class CCloud :
	public CObj
{
public:
	CCloud();
	CCloud(TYPE _eType);
	virtual ~CCloud();

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Late_Update(void);
	virtual void Render(HDC hDC);
	virtual void Release(void);
};