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

	CButton* choosePet1;
	CButton* choosePet2;
	CButton* stage1Start;

	CImages* PrepareSceneBackgroundImages;


private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};

