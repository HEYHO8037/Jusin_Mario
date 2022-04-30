#pragma once
#include "Obj.h"
class CHurdle
	:public CObj
{
public:
	CHurdle();
	CHurdle(HURDLETYPE e_Type);
	~CHurdle();

public:
	void	Initialize(void);
	void	Update(void);
	void	Late_Update(void);
	void	Render(HDC hDC);
	void	Release(void);
public:
	//void	Moving_Hurdle(void);

private:
	//enum TYPE으로 병합 
	HURDLETYPE	m_eType;



};

