#pragma once

#include "Include.h"

class CLine
{

public:
	CLine();
	CLine(const LINE& _tLineInfo); // ���� ���� ����
	CLine(const DotPoint& _tLeftPoint, const DotPoint& _tRightPoint); // �� �ΰ��� ���� ����
	~CLine();

public:
	const LINE& Get_LineInfo() const; // ���� ���� ��������

public:
	void	Render(HDC hDC); // ���� ���


private:
	LINE m_tLineInfo; // ����(�� ���� ������ ����)
};