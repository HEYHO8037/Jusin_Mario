#pragma once
#include "Obj.h"

/*싱글톤 패턴의 개념

같은 부모를 상속받는 클래스가 5개가 있다고 가정하면
각각의 클래스를 접근할 때 객체를 생성해서 객체가 5개가 된다. << 매우 비효율적
때문에 같은 부모를 상속받는 클래스면 관리해주는 클래스를 만들어서 하나의 클래스로 관리하는 개념

생성자를 호출했을 때 관리자 클래스가 널값이라면 메모리를 할당한다.
때문에 생성자가 여러 차례 호출되더라도 최초에 생성한 객체를 반환한다

생성자를 private로 하는 이유는
만약 인스턴스가 여러개면 동시에 접근할 수 있기때문에 싱글톤패턴의 개념에 문제가 생긴다.
때문에 Get_Instance() 함수를 통해서만 인스턴스를 생성/접근 할 수 있다.

*/
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public: // 맴버 함수
	void Add_Object(OBJID eID, CObj* pObj); // 인자로 받은 객체의 타입에따라 리스트에 추가해주는 함수
	void Release();
	void Update();
	void Late_Update();
	void Render(HDC hDC);

public: // 전역 함수
	static CObjMgr* Get_Instance() // 인스턴스 정보를 얻어온다.
	{
		if (!m_pInstance)
		m_pInstance = new CObjMgr;
		return m_pInstance;
	}

	static	void	Destroy_Instance(void) // 인스턴스 정보를 삭제한다.
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private: // 맴버 변수
	list<CObj*> m_ObjList[OBJ_END]; //CObj를 상속받는 객체들을 저장하는 리스트

private: // 전역 변수
	static CObjMgr* m_pInstance; // CObjMgr 인스턴스

};

