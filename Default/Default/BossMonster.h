#pragma once
#include "Obj.h"
class CBossMonster :
	public CObj
{
public:
	CBossMonster();
	CBossMonster(TYPE eType);
	virtual ~CBossMonster();

public:
	virtual void Initialize(void) override;
	virtual void Release(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;

private:
	void RandomPattern();
	bool TargetMove();
	void BehaviorUpdate();

	void BehaviorEnter();
	void BehaviorExecute();
	void BehaviorExit();

	void PatternNormalShot();
	void PatternWideShot();
	void PatternMoveToPlayer();

private:
	enum Behavior {
		Enter, // 준비
		Execute, // 실행
		Exit // 종료
	};

	enum State {
		Pattern1,		// 총알 발사
		Pattern2,		// 전방향 총알 발사
		Pattern3,		// 플레이어 돌진.
		Return,			// 돌진 복귀
		None,			// 아무상태도 아님
	};

	LARGE_INTEGER timer;
	LARGE_INTEGER start;
	LARGE_INTEGER end;


	POINT originPosition; //현재 위치
	POINT targetPosition; // 타겟 위치

	Behavior behaviorState; // 보스 상태
	State currentState; // 현재 보스 세부상태
	int iStatus;


};

