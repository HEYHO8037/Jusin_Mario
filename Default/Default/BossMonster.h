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
		Enter, // �غ�
		Execute, // ����
		Exit // ����
	};

	enum State {
		Pattern1,		// �Ѿ� �߻�
		Pattern2,		// ������ �Ѿ� �߻�
		Pattern3,		// �÷��̾� ����.
		Return,			// ���� ����
		None,			// �ƹ����µ� �ƴ�
	};

	LARGE_INTEGER timer;
	LARGE_INTEGER start;
	LARGE_INTEGER end;


	POINT originPosition; //���� ��ġ
	POINT targetPosition; // Ÿ�� ��ġ

	Behavior behaviorState; // ���� ����
	State currentState; // ���� ���� ���λ���
	int iStatus;


};

