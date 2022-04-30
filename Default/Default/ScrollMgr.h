#pragma once

#include "Include.h"
/*
스크롤 개념
누구를 중심으로 오브젝트들을 움직일거냐를 우선 정한다.
플레이어를 중심으로 움직인다고 가정하면
모든 오브젝트들은 플레이어의 속도만큼 움직여야한다.
예를 들어 플레이어의 속도가 5라고 가정하면
플레이어가 설정한 OffSet(일정 선)을 넘어갔을 때
우측에 있으면 스크롤 좌표를 플레이어의 속도만큼 더하고
좌측에 있으면 스크롤 좌표를 플레이어의 속도만큼 뺀후
기존 좌표에 스크롤좌표를 더한 좌표에 그림을 그려주면 플레이어 속도만큼 이동하는것 처럼 보인다.


좌표에 대한 제한이 없는 이유는
해상도의 사이즈가 800x600 이라고 가정했을 때
플레이어의 좌표를 스크롤 좌표만큼 더해주다보면 해상도의 크기를 벗어나지만
랜더링 할 때 스크롤 좌표만큼 더해준 범위에 그리기 때문에 상관이 없다.
예를들어 계속 더해주다가 플레이어의 X축좌표가 10000이 되었다고 해도
랜더링할 때 10000좌표에 랜더링이 된다.
*/

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float Get_ScrollX(void) { return m_fScrollX; }
	void Set_ScrollX(float _fX) { m_fScrollX += _fX; }
	
	float Get_ScrollY(void) { return m_fScrollY; }
	void Set_ScrollY(float _fY) { m_fScrollY -= _fY; }

public:
	static CScrollMgr* Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;
	
			return m_pInstance;
	}

	static void Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CScrollMgr* m_pInstance;
	float m_fScrollX = 0.f;
	float m_fScrollY = 0.f;
};





