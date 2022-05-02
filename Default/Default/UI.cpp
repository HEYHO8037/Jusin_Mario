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
// 폰트 출력 (지울예정)
//
//lstrcpy(m_szFPS, L"Hello");
//TextOut(m_hDC, 50, 50, m_szFPS, lstrlen(m_szFPS));
// 1. dc 2, 3. 출력할 윈도우 left, top 좌표, 4. 출력할 문자열 5. 문자열 버퍼 크기
//
//RECT rc{ 0, 0, 50, 50 };
//DrawText(m_hDC, m_szFPS, lstrlen(m_szFPS), &rc, DT_RIGHT);
// 1. dc 2. 출력할 문자열 3. 문자열 버퍼 크기 4. 출력할 렉트 주소, 5. 출력 옵션
//
//TCHAR	szBuff[32] = L"";
// 소수점 자리 출력이 불가능하다. winapi 라이브러리에서 제공하는 함수
//wsprintf(szBuff, L"Bullet : %d", m_ObjList[OBJ_BULLET].size());
//
// visual c++ 라이브러리에서 제공(모든 서식 문자를 지원)
//swprintf_s(szBuff, L"Bullet : %f", 3.14f);
//TextOut(m_hDC, 50, 50, szBuff, lstrlen(szBuff));