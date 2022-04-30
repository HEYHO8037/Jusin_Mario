#include "stdafx.h"
#include "Line.h"
#include "LineMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{

}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_pLineList)
		iter->Render(hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_pLineList.begin(), m_pLineList.end(), CDeleteObj());
	m_pLineList.clear();
}

bool CLineMgr::Collision_Line(float & _fX, float * pY)
{
	// 직선의 방정식

	// Y - y1 = ((y2 - y1) / (x2 - x1)) * X - x1
	// Y  = (((y2 - y1) / (x2 - x1)) * (X - x1)) + y1

	if (m_pLineList.empty())
		return false;

	CLine*		pTarget = nullptr;

	for (auto& iter : m_pLineList)
	{
		if (_fX >= iter->Get_LineInfo().tLPoint.fX &&
			_fX <= iter->Get_LineInfo().tRPoint.fX)
		{
			pTarget = iter;
		}
	}

	if (!pTarget)
		return false;

	float	x1 = pTarget->Get_LineInfo().tLPoint.fX;
	float	x2 = pTarget->Get_LineInfo().tRPoint.fX;

	float	y1 = pTarget->Get_LineInfo().tLPoint.fY;
	float	y2 = pTarget->Get_LineInfo().tRPoint.fY;

	*pY = (((y2 - y1) / (x2 - x1)) * (_fX - x1)) + y1;
	return true;
}

void CLineMgr::Create_Line(const CLine& Line)
{
	CLine* pLine = new CLine(Line);
	m_pLineList.push_back(pLine);
}

void CLineMgr::Create_Line(const LINEPOINT & tLeft, const LINEPOINT & tRight)
{
	CLine* pLine = new CLine(tLeft, tRight);
	m_pLineList.push_back(pLine);
}

void CLineMgr::Load_LineData()
{
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",			// 파일 경로와 이름 명시
		GENERIC_READ,				// 파일 접근 모드 (GENERIC_WRITE 쓰기 전용, GENERIC_READ 읽기 전용)
		NULL,						// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가, NULL인 경우 공유하지 않는다
		NULL,						// 보안 속성, 기본값	
		OPEN_EXISTING,				// 생성 방식, CREATE_ALWAYS는 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXISTING 파일이 있을 경우에면 열기
		FILE_ATTRIBUTE_NORMAL,		// 파일 속성(읽기 전용, 숨기 등), FILE_ATTRIBUTE_NORMAL 아무런 속성이 없는 일반 파일 생성
		NULL);						// 생성도리 파일의 속성을 제공할 템플릿 파일, 우리는 사용하지 않아서 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// 팝업 창을 출력해주는 기능의 함수
		// 1. 핸들 2. 팝업 창에 띄우고자하는 메시지 3. 팝업 창 이름 4. 버튼 속성
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. 파일 읽기

	DWORD		dwByte = 0;
	LINE		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)	// 더이상 읽을 데이터가 없을 경우
			break;

		m_pLineList.push_back(new CLine(tInfo));
	}


	// 3. 파일 소멸
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 완료"), _T("성공"), MB_OK);
}

void CLineMgr::Save_LineData()
{
	// 1. 파일 개방

	// CreateFile : api 파일 개방 함수, 개방 실패 시 INVALID_HANDLE_VALUE하기 때문에 null값으로 예외처리를 할 수 없다.

	HANDLE		hFile = CreateFile(L"../Data/Line.dat",			// 파일 경로와 이름 명시
		GENERIC_WRITE,				// 파일 접근 모드 (GENERIC_WRITE 쓰기 전용, GENERIC_READ 읽기 전용)
		NULL,						// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허용할 것인가, NULL인 경우 공유하지 않는다
		NULL,						// 보안 속성, 기본값	
		CREATE_ALWAYS,				// 생성 방식, CREATE_ALWAYS는 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXISTING 파일이 있을 경우에면 열기
		FILE_ATTRIBUTE_NORMAL,		// 파일 속성(읽기 전용, 숨기 등), FILE_ATTRIBUTE_NORMAL 아무런 속성이 없는 일반 파일 생성
		NULL);						// 생성도리 파일의 속성을 제공할 템플릿 파일, 우리는 사용하지 않아서 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// 팝업 창을 출력해주는 기능의 함수
		// 1. 핸들 2. 팝업 창에 띄우고자하는 메시지 3. 팝업 창 이름 4. 버튼 속성
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. 파일 쓰기

	DWORD		dwByte = 0;

	for (auto& iter : m_pLineList)
	{
		WriteFile(hFile, &iter->Get_LineInfo(), sizeof(LINE), &dwByte, nullptr);
	}


	// 3. 파일 소멸
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save 완료"), _T("성공"), MB_OK);
}
