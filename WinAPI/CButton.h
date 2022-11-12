#pragma once
#include "CUI.h"

class CImage;

// 함수포인터 : 함수를 가리키는 포인터 변수로 함수의 시작주소를 저장하는 변수
// 반환형 (*함수포인터 이름)(매개변수들...)
// ex) void (*FuncPointer)(int);
// 가리키고 있는 함수를 호출하기 위해서는 함수포인터 이름을 통해서 진행
// ex) FuncPointer(10);
typedef void(*CallbackFunc)(DWORD_PTR, DWORD_PTR);

class CButton : public CUI
{
public:
	CButton();
	virtual ~CButton();

private:
	CallbackFunc	m_pCallback;
	DWORD_PTR		m_pParam1;
	DWORD_PTR		m_pParam2;

	wstring			m_strText;
	float			m_iSizeText;
	Color			m_colorText;
	CImage*			m_buttonImage;
	CImage*			m_buttonImageMouseOver;
	wstring			m_strImageName;
	
	bool			isMouseOver;

public:
	void SetClickedCallback(CallbackFunc pCallback, DWORD_PTR pParam1, DWORD_PTR pParam2);

	void SetText(const wstring& text, float fontSize = 12, Color color = Color(0, 0, 0, 1));

	void SetImage(const wstring& image, const wstring& mouseOverImage);

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	// final : 더이상 자식이 재정의 할수 없도록 막음
	// 부모의 고유의 기능만을 사용하도록 제한
	// 버튼의 경우 클릭하여 반응하기 위한 용도로만 사용
	void OnMouseEnter() final;
	void OnMouseOver() final;
	void OnMouseExit() final;
	void OnMouseUp() final;
	void OnMouseDown() final;
	void OnMouseClicked() final;

	// delete : 더이상 해당함수를 사용 할수 없도록 막음
	// 부모에서 정의한 기능을 자식은 사용하지 않기를 바랄경우 사용
	void AddChildUI(CUI* pChildUI) = delete;
};
