#pragma once
#include "CRenderManager.h"
#include "CImage.h"

class CImage;

class CImages : public CGameObject
{
public:
	CImages();
	virtual ~CImages();

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

	wstring ImageName;

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

public:
	CImage GetPauseImage();
	void SetPauseImage(CImage* target);
	void SetImageName(const wstring& name);
};


#define GETPAUSEIMAGE