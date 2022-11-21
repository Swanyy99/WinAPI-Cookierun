#pragma once
#include "CRenderManager.h"
#include "CImage.h"

class CImage;

class CUnderUI : public CUI
{
public:
	CUnderUI();
	virtual ~CUnderUI();

public:
	CImage* PauseImage;
	CImage* FailImage;
	CImage* SlideButtonImage;
	CImage* JumpButtonImage;
	CImage* Image;


	CImage* CookierunTitle;

	CImage* PrepareScene;

	CImage* slideImage;

	CImage* jumpImage;
	CImage* HPIcon;
	CImage* HPEffect;
	CImage* HPBar;
	CImage* HPBackBar;
	CImage* HPProgressBar;
	CImage* Loading;

	wstring ImageName;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	virtual void OnMouseEnter() override;
	virtual void OnMouseOver() override;
	virtual void OnMouseExit()override;
	virtual void OnMouseUp() override;
	virtual void OnMouseDown() override;
	virtual void OnMouseClicked() override;

public:
	CImage GetPauseImage();
	void SetPauseImage(CImage* target);
	void SetImageName(const wstring& name);


};


