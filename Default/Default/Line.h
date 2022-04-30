#pragma once

#include "Include.h"

class CLine
{

public:
	CLine();
	CLine(const LINE& _tLineInfo); // 라인 복사 생성
	CLine(const DotPoint& _tLeftPoint, const DotPoint& _tRightPoint); // 점 두개로 라인 생성
	~CLine();

public:
	const LINE& Get_LineInfo() const; // 라인 정보 가져오기

public:
	void	Render(HDC hDC); // 라인 출력


private:
	LINE m_tLineInfo; // 라인(두 점의 정보를 가짐)
};