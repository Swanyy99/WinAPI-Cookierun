#pragma once
#include "CScene.h"
#include "CImages.h"
class CImages;

class CScenePrepare : public CScene
{
public:
	CScenePrepare();
	virtual ~CScenePrepare();

private:
	CImage* PrepareSceneBackgroundImage;
	CImage* PrepareScenePetChoiceImage;
	CImage* ChoosedImage;
	CImage* Price5000;
	CImage* NoPetWarning;
	CImage* NoMoneyWarning;

	CButton* choosePet1;
	CButton* purchasePet1;
	CButton* choosePet2;
	CButton* purchasePet2;
	CButton* choosePet3;
	CButton* purchasePet3;
	CButton* stage1Start;
	CButton* purchaseDisable;

	CImages* PrepareSceneBackgroundImages;

	float NoMoneyWordTimer;
	float NoPetWordTimer;


private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};

