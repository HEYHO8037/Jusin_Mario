#include "stdafx.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "Hurdle.h"
#include "Monster.h"

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

bool CCollisionMgr::Check_Rect(CObj * pDest, CObj * pSour, float * pX, float * pY) //px?ï¿?pY??ì£¼ì?�Œê°’�?��??ï¿½ê²¨ì£¼ì?��???ï¿½ì??ê°???ï¿½ë?��?ï¿½ì?��??ë³??ï¿½ì?��??ï¿?ï¿½í?��?ê°?��?��?ê³?�ì†�??ï¿½ì???ï¿½ë?��?
{
	float fWidth = abs(pDest->Get_Info().fX - pSour->Get_Info().fX); // ??ì¤?��?��??x??ê¸¸ì´, ë°?��?��?
	float fHeight = abs(pDest->Get_Info().fY - pSour->Get_Info().fY); // ??ì¤?��?��??y??ê¸¸ì´, ?ï¿½ì´

	float fCX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f; // ê°ê°??ë°?ï¿½?ë¥¼ì??êµ¬í?��???ï¿½í?��?ï¿?x) 
	float fCY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f; // ê°ê°??ë°?ï¿½?ë¥¼ì??êµ¬í?��???ï¿½í?��?ï¿?y)

	if ((fCX > fWidth) && (fCY > fHeight)) // ?ï¿½ì  ?ï¿½ì´??ê±°ë¦¬ê°???ï¿½ê°ì²´ì? ë°?ï¿½?ë¦?��?��??ï¿½í?�œê°’ë³�???ï¿½ì?�„�?�€ï¿?ì¶©ëŒ
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight; // ?ï¿½ê°ì²´ì? ë°?ï¿½?ë¦?��?��??ï¿½í?�œê°’ì—�???ï¿½ì ?ï¿½ì´??ê±°ë¦¬ï¿?ë¹¼ì£¼ï¿?ì¶©ëŒ??ê±°ë¦¬, ê¸¸ì´ê°???ï¿½ì?¨??

		return true; // ì¶©ëŒ?ï¿½ì?�ê²½�?��?true ë°?í?��?
	}

	return false;
}

bool CCollisionMgr::Check_Sphere(CObj * pDest, CObj * pSour)
{
	// abs ?ï¿½ï¿½?ê°?�êµ�?ï¿½ëŠ???ï¿½ì?? f- float?ï¿½ï¿½?ï¿?ë¶?�ì—�???
	float fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX); //ë°?��?��?
	float fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY); //?ï¿½ì´

																	   //sqrt : ë£¨íŠ¸ï¿??ï¿½ì?�Œ�?�¼ëŠ�??ï¿½ì??
	float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight); //ë¹?��?��?

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f; // ???ï¿½ì? ë°?ï¿½?ï¿??ï¿½í?�œ�??

	return fRadius > fDiagonal; // ???ï¿½ì? ë°?ï¿½?ë¦?��?��??ï¿½í?�œê°’�?��???ê°ì²´?ï¿½ì´??ê¸¸ì´ë³´ë?��??ï¿½ë?��?= ì¶©ëŒ
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour) // obj?ï¿½ì¸???ï¿??ë¦¬ìŠ¤?ï¿½ì?��???ï¿½ëŠ????ê°ì²´ê°??ì¶©ëŒ?ï¿½ì???ì²?ë¦¬?ï¿½ëŠ???ï¿½ì??
{
	RECT rc{}; // ì¶©ëŒ??ë²?��?�„�???ï¿½ëŠ??ë³???

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


				//??ê°ì²´ê°??ì¶©ëŒ?ï¿½ì?��?ï¿½ë?��?trueï¿?ë°?í?��?ï¿½ë?��?
				//true???ï¿½í?œ = ??ê°ì²´ê°??ì¶©ëŒ?ï¿½ì?��?ï¿½ëŠ??ê²?ì???ï¿½ï¿½??ï¿½ï¿½?ï¿??ï¿½ë?��??ï¿½í?��???ï¿½ë????ï¿½ëŠ???ï¿½ì??ï¿??ï¿½ì?�´�?�¼ë©�?ï¿½ë?��?
				//ex) Set_Dead
			
			}
		}
	}

}
//ê³ ì ??ï¿½ì?��?ï¿½ëŠ??ë¬¼ì²´		//?ï¿½ì§???ë¬¼ì²´
void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto & Sour : _Sour)
		{
			float fX = 0.f, fY = 0.f; // ì¶©ëŒ??ê¸¸ì´ï¿??ï¿½ìš©??ë³???
			//Dest ?ï¿½ë ??ï¿½ì?��?Sour ëª¬ìŠ¤??
			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				//?ï¿½í?�˜�?�©ë�?
				if (fX > fY) // ì¶©ëŒ?ï¿½ì????ï¿½ì?¨ X??ê¸¸ì´ê°??Y??ê¸¸ì´ë³´ë?��?ê¸¸ë?�¤�???ï¿½í?�˜�?�©ë�?
				{
					if (Sour->Get_Rect().top <= Dest->Get_Rect().bottom) // ê³ ì ??ï¿½ì?��?ï¿½ëŠ?�ë�?��?��??y??ê°?��?��??ï¿½ì§???ë¬¼ì²´??y??ê°?�ë³�????ê²½ìš°, ??ì¶©ëŒ
					{
						//Dest->Set_PostY(fY);
						if (CTime + 300 < GetTickCount())
						{
							Sour->Set_HpMinus();
							static_cast<CPlayer*>(Dest)->Set_Jump();
							CTime = GetTickCount();
						}
						//Sour->Set_PosY(-fY); // ì¶©ëŒ??ê¸¸ì´ë§Œí¼ ?ï¿½ë¡œ ?ï¿½ë¼ê°????-fYê°?��?��??ï¿½ëŠ???
					}
					else //??ì¶©ëŒ
					{
						//Sour->Set_HpMinus();
						//Sour->Set_PosY(fY); // ì¶©ëŒ??ê¸¸ì´ë§Œí¼ ë°?��?�¼�???ï¿½ë ¤ê°????fYê°?��?��??ï¿½ëŠ???
					}
				}
				else // ì¢Œìš° sì¶©ëŒ fX < fY
				{
					if (Sour->Get_Info().fX > Dest->Get_Info().fX) // ì¢Œì¶©??ê³ ì ??ï¿½ë¬¼ì²´ï¿½? ?ï¿½ì§???ë¬¼ì²´??ì¤?��?�ë³´ë‹�??ï¿½ë¥¸ìª½ì?��??ï¿½ìœ¼ë¯????
					{	
						//Dest->Set_PostX(-fX);
						//return;
					}
					else // ??ì¶©ëŒ
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

void CCollisionMgr::Collision_Player_BossMonster()
{
	list<CObj*>::const_iterator iter = (*m_ObjList + OBJ_MONSTER)->begin();
	list<CObj*>::const_iterator iterEnd = (*m_ObjList + OBJ_MONSTER)->end();
	
	for (iter; iter != iterEnd; ++iter)
	{
		float fX, fY;

		if (Check_Rect(m_ObjList[OBJ_PLAYER]->front(), (*iter), &fX, &fY))
		{
			if ((*iter)->Get_Type() == TYPE_BOSS)
			{
				if (fX > fY) //ï¿½ï¿½ï¿½ï¿½ ï¿½æµ¹
				{
					if ((*iter)->Get_Info().fY > m_ObjList[OBJ_PLAYER]->front()->Get_Info().fY) // ï¿½Ã·ï¿½ï¿½Ì¾î°¡ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?
					{
						(*iter)->Set_HpMinus(); // ï¿½ï¿½ï¿½ï¿½ Ã¼ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
						
						static_cast<CPlayer*>(m_ObjList[OBJ_PLAYER]->front())->Set_Jump();
					}
					else
					{
						m_ObjList[OBJ_PLAYER]->front()->Set_HpMinus(); //ï¿½ï¿½ ï¿½ï¿½ ï¿½æµ¹ ï¿½Ã·ï¿½ï¿½Ì¾ï¿½ Ã¼ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
					}
				}
				else
				{
					if ((*iter)->Get_Info().fX > m_ObjList[OBJ_PLAYER]->front()->Get_Info().fX) 
					{
						m_ObjList[OBJ_PLAYER]->front()->Set_PostX(-fX);
						return;
					}
					else
					{
						m_ObjList[OBJ_PLAYER]->front()->Set_PostX(fX);
						return;
					}
				}
			}
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
	
			}
		}
	}
}

void CCollisionMgr::Collision_Player_Item()
{
	float fX, fY;
	TYPE eType;
	list<CObj*>::const_iterator iter = (*m_ObjList + OBJ_ITEM)->begin();
	list<CObj*>::const_iterator iterEnd = (*m_ObjList + OBJ_ITEM)->end();
	RECT rc{};

	for (iter; iter != iterEnd; ++iter)
	{
		if (IntersectRect(&rc, &((*iter)->Get_Rect()), &(m_ObjList[OBJ_PLAYER]->front()->Get_Rect())))
		{
			eType = (*iter)->Get_Type(); // ?�이???�???�어?�기
			if (eType == TYPE_ITEM_GROW) //?�레?�어 ?�장 ?�수
			{				
				if (m_ObjList[OBJ_PLAYER]->front()->Get_Hp() <= 2)
				{
					m_ObjList[OBJ_PLAYER]->front()->Set_HpPlus();
					(*iter)->Set_Dead();
				}

			}
			else if (eType == TYPE_ITEM_BULLET)//총알?�는 ?�수				
			{
				dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER]->front())->Equip_Weapon();
				(*iter)->Set_Dead();
			}

		}

	}
}



void CCollisionMgr::Collision_Player_Huddle()
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
			{
				if (fX > fY)
				{
					if ((*iter)->Get_Info().fY >= m_ObjList[OBJ_PLAYER]->front()->Get_Info().fY)
					{
						if ((*iter)->Get_Rect().left <= m_ObjList[OBJ_PLAYER]->front()->Get_Info().fX &&
							(*iter)->Get_Rect().right >= m_ObjList[OBJ_PLAYER]->front()->Get_Info().fX)
						{
							dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER]->front())->Set_PosY((*iter)->Get_Rect().top);
						}
					}
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
						m_ObjList[OBJ_PLAYER]->front()->Set_PostX(-fX);
					}
				}
				break;
			}
			case TYPE_HUR_FLOAT:
			{
				Collision_RectEx_Push();
				break;
			}
			case TYPE_HUR_ITEM:
				break;
			case TYPE_HUR_STACK:
				if (fX > fY)
				{	//�÷� ��������
					if ((*iter)->Get_Info().fY >= m_ObjList[OBJ_PLAYER]->front()->Get_Info().fY)
					{
						if ((*iter)->Get_Rect().left <= m_ObjList[OBJ_PLAYER]->front()->Get_Info().fX &&
							(*iter)->Get_Rect().right >= m_ObjList[OBJ_PLAYER]->front()->Get_Info().fX)
						{
							dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER]->front())->Set_PosY((*iter)->Get_Rect().top);
						}
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
						m_ObjList[OBJ_PLAYER]->front()->Set_PostX(fX);
					}
				}
				break;
				break;
			}
		}

	}
}

void CCollisionMgr::Collision_Bullet_Huddle()
{

	float fX, fY;
	
	list<CObj*>::const_iterator iter = (*m_ObjList + OBJ_BULLET)->begin();
	list<CObj*>::const_iterator iterEnd = (*m_ObjList + OBJ_BULLET)->end();
	RECT rc{};

	for (iter; iter != iterEnd; ++iter)
	{
		list<CObj*>::const_iterator Biter = (*m_ObjList + OBJ_HURDLE)->begin();
		list<CObj*>::const_iterator BiterEnd = (*m_ObjList + OBJ_HURDLE)->end();

		for (Biter; Biter != BiterEnd; ++Biter)
		{
			if (IntersectRect(&rc, &((*iter)->Get_Rect()), &((*Biter)->Get_Rect())))
				(*iter)->Set_Dead();
		}
	}

}

void CCollisionMgr::Collision_Monster_Huddle(list<CObj*> _Dest, list<CObj*> _Sour)
{
	TYPE eType;

	for (auto& Dest : _Dest)
	{
		for (auto & Sour : _Sour)
		{
			float fX = 0.f, fY = 0.f; 
			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				if (Sour->Get_Type() == TYPE_BOSS)
				{
					continue;
				}

				if (fX < fY) //�¿��浹�� �ʿ�
				{
					//sour- monster, dest- hurdle
				
					eType = Sour->Get_Type();

					if (eType == TYPE_MONSTER_MOVE)
					{				
						dynamic_cast<CMonster*>(Sour)->Set_Reverse(); // ï¿½æµ¹ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ù²ï¿½ï¿½Ö±ï¿½
					}
					
					if (eType == TYPE_MONSTER_TURTLE && 2 <= Sour->Get_Info().m_iHp)
					{
						//���浹
						if (Dest->Get_Info().fX > Sour->Get_Info().fX)
							Sour->Set_PostX(-fX);

						// �� �浹
						else
							Sour->Set_PostX(fX);
					}


					if(eType == TYPE_MONSTER_TURTLE && 1 >= Sour->Get_Info().m_iHp)
					{
						Sour->Set_HpMinus();
					}
				}
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx_Push()
{

	for (auto& Dest : (*m_ObjList[OBJ_PLAYER]))
	{
		list<CObj*>::const_iterator iter = (*m_ObjList + OBJ_HURDLE)->begin();
		list<CObj*>::const_iterator iterEnd = (*m_ObjList + OBJ_HURDLE)->end();

		for (iter; iter != iterEnd; ++iter)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(Dest, (*iter), &fX, &fY))
			{
				
				if (fY >= fX)
				{
					// ÁÂ Ãæµ¹
					if (Dest->Get_Info().fX > (*iter)->Get_Info().fX)
						(*iter)->Set_PosX((*iter)->Get_Info().fX - fX);

					// ¿ì Ãæµ¹
					else
					{
						if (!dynamic_cast<CHurdle*>(*iter)->GetIsMove())
						{
							Dest->Set_PosX(Dest->Get_Info().fX - fX);
							return;
						}

						(*iter)->Set_PosX((*iter)->Get_Info().fX + fX);
					}
				}
				else
				{
					if (Dest->Get_Info().fY <= (*iter)->Get_Info().fY && dynamic_cast<CPlayer*>(Dest)->Get_Jump())
						Dest->Set_PosY((*iter)->Get_Info().fY - fY);

					else
						Dest->Set_PosY((*iter)->Get_Info().fY + fY);
				}

			}
		}
	}
}

void CCollisionMgr::Collision_Huddle_Huddle()
{
	float fX, fY;

	list<CObj*>::const_iterator iter = (*m_ObjList + OBJ_HURDLE)->begin();
	list<CObj*>::const_iterator iterEnd = (*m_ObjList + OBJ_HURDLE)->end();

	for (iter; iter != iterEnd; ++iter)
	{
		list<CObj*>::const_iterator iterSec = (*m_ObjList + OBJ_HURDLE)->begin();
		list<CObj*>::const_iterator iterSecEnd = (*m_ObjList + OBJ_HURDLE)->end();

		for (iterSec; iterSec != iterSecEnd; ++iterSec)
		{
			if ((*iter) == (*iterSec))
			{
				continue;
			}
			else
			{
				if (Check_Rect((*iter), (*iterSec), &fX, &fY) && (*iter)->Get_Type() == TYPE_HUR_FLOAT)
				{
					if (fX <= fY)
					{
						if ((*iter)->Get_Info().fX <= (*iterSec)->Get_Info().fX)
						{
							(*iter)->Set_PosX((*iter)->Get_Info().fX - fX);
							dynamic_cast<CHurdle*>((*iter))->SetMove();
							return;
						}
						else
						{
							(*iter)->Set_PosX((*iter)->Get_Info().fX + fX);
							dynamic_cast<CHurdle*>((*iter))->SetMove();
							return;
						}
					}
				}
			}
		}
	}
}

