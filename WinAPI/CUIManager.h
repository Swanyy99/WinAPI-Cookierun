#pragma once

class CCore;
class CUI;

class CUIManager : public SingleTon<CUIManager>
{
	friend SingleTon<CUIManager>;
	friend CCore;
private:
	CUIManager();
	virtual ~CUIManager();

private:
	CUI* m_pFocusedUI;
	bool m_pMouseOnUI;

private:
	CUI* GetTopUI();
	CUI* GetTopChildUI(CUI* pUI);

	void MouseEvent(CUI* pUI, CUI* pTopChildUI);

public:
	CUI* GetFocusedUI();
	void SetFocusedUI(CUI* pUI);

	bool GetMouseOnUI();

private:
	void Init();
	void Update();
	void Release();
};

#define UI	CUIManager::GetInstance()
