#include "stdafx.h"
#include "CollisionMgr.h"
#include "Player.h"

CCollisionMgr* CCollisionMgr::m_pInstance = nullptr;
DWORD CCollisionMgr::CTime = 0;
CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::SetObjList(const list<CObj*> (*pObjList)[OBJ_END])
{
	m_ObjList = pObjList;
}

bool CCollisionMgr::Check_Rect(CObj * pDest, CObj * pSour, float * pX, float * pY) //px?� pY??주소값을 ?�겨주어???�수가 ?�난?�에??변?�에 ?�?�한 값을 계속 ?�수?�다
{
	float fWidth = abs(pDest->Get_Info().fX - pSour->Get_Info().fX); // ??중점�?x??길이, 밑�?
	float fHeight = abs(pDest->Get_Info().fY - pSour->Get_Info().fY); // ??중점�?y??길이, ?�이

	float fCX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f; // 각각??반�?를을 구한???�한 �?x) 
	float fCY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f; // 각각??반�?를을 구한???�한 �?y)

	if ((fCX > fWidth) && (fCY > fHeight)) // ?�점 ?�이??거리가 ?�객체의 반�?름을 ?�한값보???�아지�?충돌
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight; // ?�객체의 반�?름을 ?�한값에???�점?�이??거리�?빼주�?충돌??거리, 길이가 ?�온??

		return true; // 충돌?�을경우 true 반환
	}

	return false;
}

bool CCollisionMgr::Check_Sphere(CObj * pDest, CObj * pSour)
{
	// abs ?��?값구?�는 ?�수 f- float?��?�?붙여�?
	float fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX); //밑�?
	float fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY); //?�이

																	   //sqrt : 루트�??�워주는 ?�수
	float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight); //빗�?

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f; // ???�의 반�?�??�한�?

	return fRadius > fDiagonal; // ???�의 반�?름을 ?�한값이 ??객체?�이??길이보다 ?�다 = 충돌
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour) // obj?�인???�??리스?�안???�는 ??객체가 충돌?�을??처리?�는 ?�수
{
	RECT rc{}; // 충돌??범위�??�는 변??

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				if (Sour->Get_Type() == TYPE_PBULLET)
				{
					Dest->Set_HpMinus();
					Sour->Set_HpMinus();
				}


				//??객체가 충돌?�었?�때 true�?반환?�다
				//true???�태 = ??객체가 충돌?�었?�는 것을 ?��??��?�??�때 ?�하???�동???�는 ?�수�??�어주면?�다
				//ex) Set_Dead
			
			}
		}
	}

}
//고정?�어?�는 물체		//?�직이??물체
void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto & Sour : _Sour)
		{
			float fX = 0.f, fY = 0.f; // 충돌??길이�??�용??변??
			//Dest ?�레?�어 Sour 몬스??
			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				//?�하충돌
				if (fX > fY) // 충돌?�을???�온 X??길이가 Y??길이보다 길다�??�하충돌 
				{
					if (Sour->Get_Rect().top < Dest->Get_Rect().bottom) // 고정?�어?�는물체??y??값이 ?�직이??물체??y??값보????경우, ??충돌
					{
						//Dest->Set_PostY(fY);
						if (CTime + 300 < GetTickCount())
						{
							Sour->Set_HpMinus();
							static_cast<CPlayer*>(Dest)->Set_Jump();
							CTime = GetTickCount();
						}
						//Sour->Set_PosY(-fY); // 충돌??길이만큼 ?�로 ?�라가�?-fY값을 ?�는??
					}
					else //??충돌
					{
						//Sour->Set_HpMinus();
						//Sour->Set_PosY(fY); // 충돌??길이만큼 밑으�??�려가�?fY값을 ?�는??
					}
				}
				else // 좌우 s충돌 fX < fY
				{
					if (Sour->Get_Info().fX > Dest->Get_Info().fX) // 좌충??고정?�물체�? ?�직이??물체??중점보다 ?�른쪽에 ?�으므�?
					{	
						//Dest->Set_PostX(-fX);
						//return;
					}
					else // ??충돌
					{
						//Dest->Set_PostX(fX);
						//return;
					}
				}
			}
		}
	}

}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				/*Dest->Set_Dead();
				Sour->Set_Dead();*/
			}
		}
	}
}

void CCollisionMgr::Collision_Player_Monster()
{
	float fX, fY;

	list<CObj*>::const_iterator iter = m_ObjList[OBJ_MONSTER]->begin();
	list<CObj*>::const_iterator iterEnd = m_ObjList[OBJ_MONSTER]->end();
	for (iter; iter != iterEnd; ++iter)
	{
		if (Check_Rect(m_ObjList[OBJ_PLAYER]->front(), (*iter), &fX, &fY))
		{

		}
	}
}

void CCollisionMgr::Collision_Player_Bullet()
{
	float fX, fY;

	list<CObj*>::const_iterator iter = m_ObjList[OBJ_BULLET]->begin();
	list<CObj*>::const_iterator iterEnd = m_ObjList[OBJ_BULLET]->end();
	for (iter; iter != iterEnd; ++iter)
	{
		if (Check_Rect(m_ObjList[OBJ_PLAYER]->front(), (*iter), &fX, &fY))
		{
			//충돌처리
		}
	}
}

void CCollisionMgr::Collision_Monster_Bullet()
{
	float fX, fY;

	list<CObj*>::const_iterator iter = m_ObjList[OBJ_MONSTER]->begin();
	list<CObj*>::const_iterator iterEnd = m_ObjList[OBJ_MONSTER]->end();
	
	for (iter; iter != iterEnd; ++iter)
	{
		list<CObj*>::const_iterator Biter = m_ObjList[OBJ_BULLET]->begin();
		list<CObj*>::const_iterator BiterEnd = m_ObjList[OBJ_BULLET]->end();
		
		for (Biter; Biter != BiterEnd; ++Biter)
		{
			if (Check_Rect((*iter), (*Biter),&fX, &fY))
			{
				//충돌처리
			}
		}
	}
}

void CCollisionMgr::Collision_Player_Item()
{
	float fX, fY;

	list<CObj*>::const_iterator iter = m_ObjList[OBJ_ITEM]->begin();
	list<CObj*>::const_iterator iterEnd = m_ObjList[OBJ_ITEM]->end();
	
	for (iter; iter != iterEnd; ++iter)
	{
		if (Check_Rect(m_ObjList[OBJ_PLAYER]->front(), (*iter), &fX, &fY))
		{
			//충돌처리
		}
	}
}

void CCollisionMgr::Collision_Player_Huddle()//?��?추�?
{
	float fX, fY;
	TYPE	eType;

	list<CObj*>::const_iterator iter = (*m_ObjList + OBJ_HURDLE)->begin();
	list<CObj*>::const_iterator iterEnd = (*m_ObjList + OBJ_HURDLE)->end();
	
	for (iter; iter != iterEnd; ++iter)
	{
		if (Check_Rect(m_ObjList[OBJ_PLAYER]->front(), (*iter), &fX, &fY))
		{
			eType = (*iter)->Get_Type();
			switch (eType)
			{
			case TYPE_HUR_FIXED:

				if (fX > fY)  
				{	
					//���浹
					if ((*iter)->Get_Info().fY > m_ObjList[OBJ_PLAYER]->front()->Get_Info().fY)
					{
						if((*iter)->Get_Rect().left<=m_ObjList[OBJ_PLAYER]->front()->Get_Info().fX&&
							(*iter)->Get_Rect().right>= m_ObjList[OBJ_PLAYER]->front()->Get_Info().fX)
						{
							dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER]->front())->Set_PosY((*iter)->Get_Rect().top);
						}
					}
					//���浹
					else					
					{
						dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER]->front())->Set_Power(0.f);
					}
				}
				else 
				{
					if ((*iter)->Get_Info().fX > m_ObjList[OBJ_PLAYER]->front()->Get_Info().fX)
					{
						m_ObjList[OBJ_PLAYER]->front()->Set_PostX(-fX);
					}
					else 
					{
						//(*iter)->Set_PostX(fX);
					}
				}
				break;
			case TYPE_HUR_FLOAT:
				Collision_RectEx_Push(*m_ObjList[OBJ_PLAYER], *m_ObjList[OBJ_HURDLE]);
				break;
			case TYPE_HUR_ITEM:
				break;
			case TYPE_HUR_STACK:
				break;
			}
		}

	}
}

void CCollisionMgr::Collision_Monster_Huddle()
{
	float fX, fY;

	list<CObj*>::const_iterator iter = m_ObjList[OBJ_MONSTER]->begin();
	list<CObj*>::const_iterator iterEnd = m_ObjList[OBJ_MONSTER]->end();

	for (iter; iter != iterEnd; ++iter)
	{
		list<CObj*>::const_iterator Biter = m_ObjList[OBJ_HURDLE]->begin();
		list<CObj*>::const_iterator BiterEnd = m_ObjList[OBJ_HURDLE]->end();

		for (Biter; Biter != BiterEnd; ++Biter)
		{
			if (Check_Rect((*iter), (*Biter), &fX, &fY))
			{
				//충돌처리
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx_Push(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				
				if (fY > fX)
				{
					// �� �浹
					if (Dest->Get_Info().fX > Sour->Get_Info().fX)
						Sour->Set_PosX(-fX);

					// �� �浹
					else
						Sour->Set_PosX(fX);
				}

			}
		}
	}
}

