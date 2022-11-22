#include "framework.h"
#include "CStage01MapPattern.h"
#include "CJelly1.h"
#include "CObstacle.h"
#include "CObstacle2.h"
#include "CObstacle3.h"
#include "CObstacleSky.h"
#include "CDashItem.h"
#include "CHeartItem.h"
#include "CMagnetItem.h"
#include "CJemBottle.h"
#include "CCoin.h"

CStage01MapPattern::CStage01MapPattern()
{
}
CStage01MapPattern::~CStage01MapPattern()
{
}

void CStage01MapPattern::Stage01MapPattern01()
{
	SummonCoin(WINSIZEX, WINSIZEY * 0.5);
	SummonObstacle1(WINSIZEX, WINSIZEY * 0.79);
	SummonJelly1(WINSIZEX, WINSIZEY * 0.65);
	SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.75);
	SummonObstacleSky(WINSIZEX + 300, WINSIZEY * 0.3);
	SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.77);
	SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.7);
}

void CStage01MapPattern::Stage01MapPattern02()
{
	SummonObstacle1(WINSIZEX, WINSIZEY * 0.79);
	SummonJelly1(WINSIZEX, WINSIZEY * 0.65);
	SummonDashItem(WINSIZEX, WINSIZEY * 0.5);
	SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.77);
	SummonObstacleSky(WINSIZEX + 300, WINSIZEY * 0.3);
	SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.7);
}

void CStage01MapPattern::Stage01MapPattern03()
{
	SummonObstacle1(WINSIZEX, WINSIZEY * 0.79);
	SummonJelly1(WINSIZEX, WINSIZEY * 0.65);
	SummonMagnetItem(WINSIZEX, WINSIZEY * 0.5);
	SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.77);
	SummonObstacleSky(WINSIZEX + 300, WINSIZEY * 0.3);
	SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.6);
	SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.6);
	SummonJelly1(WINSIZEX + 600, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 600, WINSIZEY * 0.6);
	SummonJelly1(WINSIZEX + 700, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 700, WINSIZEY * 0.6);
	SummonJelly1(WINSIZEX + 800, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 800, WINSIZEY * 0.6);
}

void CStage01MapPattern::Stage01MapPattern04()
{
	SummonObstacleSky(WINSIZEX + 100, WINSIZEY * 0.3);
	SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.77);
	SummonJelly1(WINSIZEX + 175, WINSIZEY * 0.77);
	SummonObstacleSky(WINSIZEX + 250, WINSIZEY * 0.3);
	SummonJelly1(WINSIZEX + 255, WINSIZEY * 0.77);
	SummonJelly1(WINSIZEX + 325, WINSIZEY * 0.77);
	SummonObstacleSky(WINSIZEX + 400, WINSIZEY * 0.3);
	SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.77);
	SummonJelly1(WINSIZEX + 475, WINSIZEY * 0.77);
	SummonObstacleSky(WINSIZEX + 550, WINSIZEY * 0.3);
	SummonJelly1(WINSIZEX + 550, WINSIZEY * 0.77);
	SummonJelly1(WINSIZEX + 650, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 750, WINSIZEY * 0.7);
}

void CStage01MapPattern::Stage01MapPattern05()
{
	SummonObstacle1(WINSIZEX, WINSIZEY * 0.79);
	SummonObstacle1(WINSIZEX + 20, WINSIZEY * 0.79);
	SummonHpItem(WINSIZEX + 10, WINSIZEY * 0.35);
	SummonJelly1(WINSIZEX + 10, WINSIZEY * 0.5);
	SummonJelly1(WINSIZEX + 10, WINSIZEY * 0.62);
	SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.77);
	SummonObstacleSky(WINSIZEX + 300, WINSIZEY * 0.3);
	SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 600, WINSIZEY * 0.7);
}

void CStage01MapPattern::Stage01MapPattern06()
{
	SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.51);
	SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.63);
	SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.51);
	SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.63);
	SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.51);
	SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.63);
	SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.51);
	SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.63);
	SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.51);
	SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.63);
	SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.75);
	SummonJelly1(WINSIZEX + 600, WINSIZEY * 0.51);
	SummonJelly1(WINSIZEX + 600, WINSIZEY * 0.63);
	SummonJelly1(WINSIZEX + 600, WINSIZEY * 0.75);

	SummonCoin(WINSIZEX + 100, WINSIZEY * 0.4);
	SummonCoin(WINSIZEX + 200, WINSIZEY * 0.4);
	SummonCoin(WINSIZEX + 300, WINSIZEY * 0.4);
	SummonCoin(WINSIZEX + 400, WINSIZEY * 0.4);
	SummonCoin(WINSIZEX + 500, WINSIZEY * 0.4);
	SummonCoin(WINSIZEX + 600, WINSIZEY * 0.4);
}

void CStage01MapPattern::Stage01MapPattern07()
{
	SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 600, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 640, WINSIZEY * 0.5);
	SummonJelly1(WINSIZEX + 790, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 890, WINSIZEY * 0.7);
	SummonCoin(WINSIZEX + 790, WINSIZEY * 0.55);
	SummonCoin(WINSIZEX + 890, WINSIZEY * 0.55);
	SummonObstacle2(WINSIZEX + 1000, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 1040, WINSIZEY * 0.5);
	SummonJelly1(WINSIZEX + 1190, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 1290, WINSIZEY * 0.7);
	SummonCoin(WINSIZEX + 1190, WINSIZEY * 0.55);
	SummonCoin(WINSIZEX + 1290, WINSIZEY * 0.55);
	SummonObstacle2(WINSIZEX + 1400, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 1440, WINSIZEY * 0.5);
	SummonJelly1(WINSIZEX + 1590, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 1690, WINSIZEY * 0.7);
	SummonCoin(WINSIZEX + 1590, WINSIZEY * 0.55);
	SummonCoin(WINSIZEX + 1690, WINSIZEY * 0.55);
	SummonObstacle2(WINSIZEX + 1800, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 1840, WINSIZEY * 0.5);
	SummonJelly1(WINSIZEX + 1990, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 2090, WINSIZEY * 0.7);
	SummonCoin(WINSIZEX + 1990, WINSIZEY * 0.55);
	SummonCoin(WINSIZEX + 2090, WINSIZEY * 0.55);
	SummonObstacle2(WINSIZEX + 2200, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 2240, WINSIZEY * 0.5);
	SummonJelly1(WINSIZEX + 2390, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 2490, WINSIZEY * 0.7);
	SummonCoin(WINSIZEX + 2390, WINSIZEY * 0.55);
	SummonCoin(WINSIZEX + 2490, WINSIZEY * 0.55);
}

void CStage01MapPattern::Stage01MapPattern08()
{
	SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.7);

	SummonCoin(WINSIZEX + 100, WINSIZEY * 0.55);
	SummonCoin(WINSIZEX + 200, WINSIZEY * 0.55);
	SummonCoin(WINSIZEX + 300, WINSIZEY * 0.55);
	SummonCoin(WINSIZEX + 400, WINSIZEY * 0.55);

	SummonDashItem(WINSIZEX + 500, WINSIZEY * 0.7);
	SummonMagnetItem(WINSIZEX + 500, WINSIZEY * 0.6);
	SummonObstacle2(WINSIZEX + 600, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 700, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 800, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 900, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 1000, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 1100, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 1200, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 1300, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 1400, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 1500, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 1600, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 1700, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 1800, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 1900, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 2000, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 2100, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 2200, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 2300, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 2400, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 2500, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 2600, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 2700, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 2800, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 2900, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 3000, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 3100, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 3200, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 3300, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 3400, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 3500, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 3600, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 3700, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 3800, WINSIZEY * 0.7);
	SummonObstacle2(WINSIZEX + 3900, WINSIZEY * 0.7);

	SummonJelly1(WINSIZEX + 600, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 700, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 800, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 900, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 1000, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 1100, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 1200, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 1300, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 1400, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 1500, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 1600, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 1700, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 1800, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 1900, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 2000, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 2100, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 2200, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 2300, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 2400, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 2500, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 2600, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 2700, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 2800, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 2900, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 3000, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 3100, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 3200, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 3300, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 3400, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 3500, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 3600, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 3700, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 3800, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 3900, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 4000, WINSIZEY * 0.53);
	SummonJelly1(WINSIZEX + 4100, WINSIZEY * 0.6);
	SummonJelly1(WINSIZEX + 4200, WINSIZEY * 0.65);
	SummonJelly1(WINSIZEX + 4300, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 4400, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 4500, WINSIZEY * 0.7);
	SummonJelly1(WINSIZEX + 4600, WINSIZEY * 0.7);
}

void CStage01MapPattern::Stage01MapPattern09()
{
	SummonObstacle3(WINSIZEX, WINSIZEY * 0.75);
}

void CStage01MapPattern::SummonJelly1(float x, float y)
{
	CJelly1* J1 = new CJelly1();
	J1->SetPos(x, y);
	ADDOBJECT(J1);
}

void CStage01MapPattern::SummonObstacle1(float x, float y)
{
	CObstacle* O1 = new CObstacle();
	O1->SetPos(x, y);
	ADDOBJECT(O1);
}

void CStage01MapPattern::SummonObstacle2(float x, float y)
{
	CObstacle2* O2 = new CObstacle2();
	O2->SetPos(x, y);
	ADDOBJECT(O2);
}

void CStage01MapPattern::SummonObstacle3(float x, float y)
{
	CObstacle3* O3 = new CObstacle3();
	O3->SetPos(x, y);
	ADDOBJECT(O3);
}

void CStage01MapPattern::SummonObstacleSky(float x, float y)
{
	CObstacleSky* OS = new CObstacleSky();
	OS->SetPos(x, y);
	ADDOBJECT(OS);
}

void CStage01MapPattern::SummonDashItem(float x, float y)
{
	CDashItem* DI = new CDashItem();
	DI->SetPos(x, y);
	ADDOBJECT(DI);
}

void CStage01MapPattern::SummonHpItem(float x, float y)
{
	CHeartItem* HI = new CHeartItem();
	HI->SetPos(x, y);
	ADDOBJECT(HI);
}

void CStage01MapPattern::SummonMagnetItem(float x, float y)
{
	CMagnetItem* MI = new CMagnetItem();
	MI->SetPos(x, y);
	ADDOBJECT(MI);
}

void CStage01MapPattern::SummonJemBottle(float x, float y)
{
	CJemBottle* JB = new CJemBottle();
	JB->SetPos(x, y);
	ADDOBJECT(JB);
}

void CStage01MapPattern::SummonCoin(float x, float y)
{
	CCoin* C = new CCoin();
	C->SetPos(x, y);
	ADDOBJECT(C);
}