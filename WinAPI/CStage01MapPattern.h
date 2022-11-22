#pragma once
class CStage01MapPattern : public CGameObject
{
public:
	CStage01MapPattern();
	virtual ~CStage01MapPattern();

public:
	void Stage01MapPattern01();
	void Stage01MapPattern02();
	void Stage01MapPattern03();
	void Stage01MapPattern04();
	void Stage01MapPattern05();
	void Stage01MapPattern06();
	void Stage01MapPattern07();
	void Stage01MapPattern08();
	void Stage01MapPattern09();

	void SummonJelly1(float x, float y);
	void SummonObstacle1(float x, float y);
	void SummonObstacle2(float x, float y);
	void SummonObstacle3(float x, float y);
	void SummonObstacleSky(float x, float y);
	void SummonDashItem(float x, float y);
	void SummonHpItem(float x, float y);
	void SummonMagnetItem(float x, float y);
	void SummonJemBottle(float x, float y);
	void SummonCoin(float x, float y);






};

