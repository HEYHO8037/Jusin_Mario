#pragma once
#include "Obj.h"

/*�̱��� ������ ����

���� �θ� ��ӹ޴� Ŭ������ 5���� �ִٰ� �����ϸ�
������ Ŭ������ ������ �� ��ü�� �����ؼ� ��ü�� 5���� �ȴ�. << �ſ� ��ȿ����
������ ���� �θ� ��ӹ޴� Ŭ������ �������ִ� Ŭ������ ���� �ϳ��� Ŭ������ �����ϴ� ����

�����ڸ� ȣ������ �� ������ Ŭ������ �ΰ��̶�� �޸𸮸� �Ҵ��Ѵ�.
������ �����ڰ� ���� ���� ȣ��Ǵ��� ���ʿ� ������ ��ü�� ��ȯ�Ѵ�

�����ڸ� private�� �ϴ� ������
���� �ν��Ͻ��� �������� ���ÿ� ������ �� �ֱ⶧���� �̱��������� ���信 ������ �����.
������ Get_Instance() �Լ��� ���ؼ��� �ν��Ͻ��� ����/���� �� �� �ִ�.

*/
class CObjMgr
{
private:
CObjMgr();
~CObjMgr();

public: // �ɹ� �Լ�
void AddObject(OBJID eID, CObj* pObj); // ���ڷ� ���� ��ü�� Ÿ�Կ����� ����Ʈ�� �߰����ִ� �Լ�
void Release();
int Update();
void Late_Update();
void Render(HDC hDC);
public: // ���� �Լ�
static CObjMgr* Get_Instance() // �ν��Ͻ� ������ ���´�.
{
if (!m_pInstance)
m_pInstance = new CObjMgr;
return m_pInstance;
}

static	void	Destroy_Instance(void) // �ν��Ͻ� ������ �����Ѵ�.
{
if (m_pInstance)
{
delete m_pInstance;
m_pInstance = nullptr;
}
}

private: // �ɹ� ����
list<CObj*> m_ObjList[OBJ_END]; //CObj�� ��ӹ޴� ��ü���� �����ϴ� ����Ʈ

private: // ���� ����
static CObjMgr* m_pInstance; // CObjMgr �ν��Ͻ�

};

