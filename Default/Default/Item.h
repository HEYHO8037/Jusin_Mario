#pragma once
#include "Obj.h"
class CItem :
	public CObj
{
public:
	CItem();
	CItem(TYPE _eType);
	virtual ~CItem();

public:
	virtual void Initialize(void) override;
	virtual void Release(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
public :
	TYPE Get_Itme_Type() const { return m_ItemType; }

private :
	TYPE m_ItemType; // 아이템 타입 구분 변수
};

