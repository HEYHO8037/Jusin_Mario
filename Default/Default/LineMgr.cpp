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
	LINEPOINT	tLine[4]
	{
		//Tutorial>Stagemap
		{0.f,600.f},
		{1280.f,600.f},
		//Bossmap
		{ 5120.f,1320.f },
		{ 6400.f,1320.f },
	};
	
	m_pLineList.push_back(new CLine(tLine[0], tLine[1]));
	m_pLineList.push_back(new CLine(tLine[2], tLine[3]));
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
	//Y��ǥ �����ְ� ���� -(m_tInfo*0.5) �����߰��ϱ�
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
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",			// ���� ��ο� �̸� ���
		GENERIC_READ,				// ���� ���� ��� (GENERIC_WRITE ���� ����, GENERIC_READ �б� ����)
		NULL,						// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�, NULL�� ��� �������� �ʴ´�
		NULL,						// ���� �Ӽ�, �⺻��	
		OPEN_EXISTING,				// ���� ���, CREATE_ALWAYS�� ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXISTING ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,		// ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ� ���� ����
		NULL);						// �������� ������ �Ӽ��� ������ ���ø� ����, �츮�� ������� �ʾƼ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// �˾� â�� ������ִ� ����� �Լ�
		// 1. �ڵ� 2. �˾� â�� �������ϴ� �޽��� 3. �˾� â �̸� 4. ��ư �Ӽ�
		MessageBox(g_hWnd, _T("Load File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. ���� �б�

	DWORD		dwByte = 0;
	LINE		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)	// ���̻� ���� �����Ͱ� ���� ���
			break;

		m_pLineList.push_back(new CLine(tInfo));
	}


	// 3. ���� �Ҹ�
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load �Ϸ�"), _T("����"), MB_OK);
}

void CLineMgr::Save_LineData()
{
	// 1. ���� ����

	// CreateFile : api ���� ���� �Լ�, ���� ���� �� INVALID_HANDLE_VALUE�ϱ� ������ null������ ����ó���� �� �� ����.

	HANDLE		hFile = CreateFile(L"../Data/Line.dat",			// ���� ��ο� �̸� ���
		GENERIC_WRITE,				// ���� ���� ��� (GENERIC_WRITE ���� ����, GENERIC_READ �б� ����)
		NULL,						// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ������ �� ����� ���ΰ�, NULL�� ��� �������� �ʴ´�
		NULL,						// ���� �Ӽ�, �⺻��	
		CREATE_ALWAYS,				// ���� ���, CREATE_ALWAYS�� ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXISTING ������ ���� ��쿡�� ����
		FILE_ATTRIBUTE_NORMAL,		// ���� �Ӽ�(�б� ����, ���� ��), FILE_ATTRIBUTE_NORMAL �ƹ��� �Ӽ��� ���� �Ϲ� ���� ����
		NULL);						// �������� ������ �Ӽ��� ������ ���ø� ����, �츮�� ������� �ʾƼ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// �˾� â�� ������ִ� ����� �Լ�
		// 1. �ڵ� 2. �˾� â�� �������ϴ� �޽��� 3. �˾� â �̸� 4. ��ư �Ӽ�
		MessageBox(g_hWnd, _T("Save File"), _T("Fail"), MB_OK);
		return;
	}

	// 2. ���� ����

	DWORD		dwByte = 0;

	for (auto& iter : m_pLineList)
	{
		WriteFile(hFile, &iter->Get_LineInfo(), sizeof(LINE), &dwByte, nullptr);
	}


	// 3. ���� �Ҹ�
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save �Ϸ�"), _T("����"), MB_OK);
}
