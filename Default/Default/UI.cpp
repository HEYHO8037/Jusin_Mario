#include "stdafx.h"
#include "UI.h"


CUI::CUI()
{
}


CUI::~CUI()
{
}

void CUI::Initialize(void)
{

}
void CUI::Release(void)
{

}
int CUI::Update(void)
{
	return 0;
}
void CUI::Late_Update(void)
{

}
void CUI::Render(HDC hDC)
{

}
// ��Ʈ ��� (���￹��)
//
//lstrcpy(m_szFPS, L"Hello");
//TextOut(m_hDC, 50, 50, m_szFPS, lstrlen(m_szFPS));
// 1. dc 2, 3. ����� ������ left, top ��ǥ, 4. ����� ���ڿ� 5. ���ڿ� ���� ũ��
//
//RECT rc{ 0, 0, 50, 50 };
//DrawText(m_hDC, m_szFPS, lstrlen(m_szFPS), &rc, DT_RIGHT);
// 1. dc 2. ����� ���ڿ� 3. ���ڿ� ���� ũ�� 4. ����� ��Ʈ �ּ�, 5. ��� �ɼ�
//
//TCHAR	szBuff[32] = L"";
// �Ҽ��� �ڸ� ����� �Ұ����ϴ�. winapi ���̺귯������ �����ϴ� �Լ�
//wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());
//
// visual c++ ���̺귯������ ����(��� ���� ���ڸ� ����)
//swprintf_s(szBuff, L"Bullet : %f", 3.14f);
//TextOut(m_hDC, 50, 50, szBuff, lstrlen(szBuff));