#include "stdafx.h"
#include "CollisionMgr.h"

CCollisionMgr* CCollisionMgr::m_pInstance = nullptr;

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::SetObjList(const list<CObj*>(*pObjList)[OBJ_END])
{
	m_ObjList = pObjList;
}

bool CCollisionMgr::Check_Rect(CObj * pDest, CObj * pSour, float * pX, float * pY) //px�� pY�� �ּҰ��� �Ѱ��־�� �Լ��� �����Ŀ��� ������ ������ ���� ��� �����ִ�
{
	float fWidth = abs(pDest->Get_Info().fX - pSour->Get_Info().fX); // �� ������ x�� ����, �غ�
	float fHeight = abs(pDest->Get_Info().fY - pSour->Get_Info().fY); // �� ������ y�� ����, ����

	float fCX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f; // ������ �������� ���ѵ� ���� ��(x) 
	float fCY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f; // ������ �������� ���ѵ� ���� ��(y)

	if ((fCX > fWidth) && (fCY > fHeight)) // ���� ������ �Ÿ��� �ΰ�ü�� �������� ���Ѱ����� �۾����� �浹
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight; // �ΰ�ü�� �������� ���Ѱ����� ���������� �Ÿ��� ���ָ� �浹�� �Ÿ�, ���̰� ���´�

		return true; // �浹������� true ��ȯ
	}

	return false;
}

bool CCollisionMgr::Check_Sphere(CObj * pDest, CObj * pSour)
{
	// abs ���밪���ϴ� �Լ� f- float�̹Ƿ� �ٿ���
	float fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX); //�غ�
	float fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY); //����

																	   //sqrt : ��Ʈ�� �����ִ� �Լ�
	float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight); //����

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f; // �� ���� ������ ���Ѱ�

	return fRadius > fDiagonal; // �� ���� �������� ���Ѱ��� �� ��ü������ ���̺��� ũ�� = �浹
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour) // obj������ Ÿ�� ����Ʈ�ȿ� �ִ� �� ��ü�� �浹������ ó���ϴ� �Լ�
{
	RECT rc{}; // �浹�� ������ ��� ���� 

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				//�� ��ü�� �浹�Ǿ����� true�� ��ȯ�Ѵ�
				//true�� ���� = �� ��ü�� �浹�Ǿ��ٴ� ���� �ǹ��ϹǷ� �̶� ���ϴ� �ൿ�� �ϴ� �Լ��� �־��ָ�ȴ�
				//ex) Set_Dead
			}
		}
	}

}
//�����Ǿ��ִ� ��ü		//�����̴� ��ü
void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto & Sour : _Sour)
		{
			float fX = 0.f, fY = 0.f; // �浹�� ���̷� ����� ����

			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				//�����浹
				if (fX > fY) // �浹������ ���� X�� ���̰� Y�� ���̺��� ��ٸ� �����浹 
				{
					if (Dest->Get_Info().fY > Sour->Get_Info().fY) // �����Ǿ��ִ¹�ü�� y�� ���� �����̴� ��ü�� y�� ������ ū ���, �� �浹
					{
						//Sour->Set_PosY(-fY); // �浹�� ���̸�ŭ ���� �ö󰡰� -fY���� �ִ´�
					}
					else //�� �浹
					{
						//Sour->Set_PosY(fY); // �浹�� ���̸�ŭ ������ �������� fY���� �ִ´�
					}
				}
				else // �¿� s�浹 fX < fY
				{
					if (Dest->Get_Info().fX > Sour->Get_Info().fX) // ���浹(�����ȹ�ü�� �����̴� ��ü�� �������� �����ʿ� �����Ƿ�)
					{
						//Sour->Set_PostX(-fX);
					}
					else // �� �浹
					{
						//Sour->Set_PostX(fX);
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
			//�浹ó��
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
				//�浹ó��
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
			//�浹ó��
		}
	}
}

void CCollisionMgr::Collision_Player_Huddle()
{
	float fX, fY;

	list<CObj*>::const_iterator iter = m_ObjList[OBJ_HUDDLE]->begin();
	list<CObj*>::const_iterator iterEnd = m_ObjList[OBJ_HUDDLE]->end();
	
	for (iter; iter != iterEnd; ++iter)
	{
		if (Check_Rect(m_ObjList[OBJ_PLAYER]->front(), (*iter), &fX, &fY))
		{
			//�浹ó��
		}
	}
}
