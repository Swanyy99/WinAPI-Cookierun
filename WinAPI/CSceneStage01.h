#pragma once
#include "CScene.h"
#include "CUnderUI.h"

class CPlayer;
class CPet;
class CPet2;
class CPet3;
class CUnderUI;

class CSceneStage01 : public CScene
{
public:
	CSceneStage01();
	virtual ~CSceneStage01();

private:
	CPlayer* pPlayer;
	CPet* pPet;
	CPet2* pPet2;
	CPet3* pPet3;


	CImage* slideImage;
	CImage* jumpImage;

	CImage* JemAcquire;
	CImage* CoinAcquire;



	CUnderUI* CookierunTitle;
	CUnderUI* LoadingImage;
	CUnderUI* HPIcon;
	CUnderUI* HPBackBar;
	CUnderUI* HPBar;
	CUnderUI* HPProgressBar;
	CUnderUI* HPEffect;

	CImage* Tear;

	CButton* RetryButton;
	CButton* ResumeButton;
	CButton* QuitButton;

	CUnderUI* PauseImage;
	CUnderUI* FailImage;
	CUnderUI* SlideButtonImage;
	CUnderUI* JumpButtonImage;

	wstring ScreenJem;
	wstring ScreenCoin;

	float obstacleTimer;
	float HpTimer;

	CSound* pSound = RESOURCE->LoadSound(L"Stage1", L"Sound\\Stage1.wav");


public:



private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;

	//void SummonJelly1(float x, float y);
	//void SummonObstacle1(float x, float y);
	//void SummonObstacle2(float x, float y);
	//void SummonObstacle3(float x, float y);
	//void SummonObstacleSky(float x, float y);
	//void SummonDashItem(float x, float y);
	//void SummonHpItem(float x, float y);
	//void SummonMagnetItem(float x, float y);
	//void SummonJemBottle(float x, float y);
	//void SummonCoin(float x, float y);
};
