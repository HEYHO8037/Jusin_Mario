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
	//�浹ó���� ���ؼ� ���Ÿ���� ��ȯ����
	TYPE Get_type(void) { return m_eHurdleType; }

private:
	TYPE m_eHurdleType;



};

