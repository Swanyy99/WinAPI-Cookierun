#pragma once

#include "resource.h"

//========================================
//##    ��������(�ν��Ͻ�, ������ �ڵ�)	##
//========================================

extern HINSTANCE hInst;
extern HWND hWnd;

//========================================
//##			������ ����				##
//========================================

#define WINSTARTX   100
#define WINSTARTY   100
#define WINSIZEX	1280
#define	WINSIZEY	720
#define WINSTYLE	WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

//========================================
//##			���Ӿ� �׷�				##
//========================================

enum class GroupScene
{
	Title,

	TileTool,

	PrePare,

	Stage01,

	Size,
};

//========================================
//##				���̾�				##
//========================================

enum class Layer
{
	Default,
	Tile,
	GroundTile,
	BackGround,
	OverBackGround,
	Floor,
	BottomBackGround,
	Obstacle,
	Jelly,
	Coin,
	HeartItem,
	DashItem,
	MagnetItem,
	ObstacleBoomEffect,
	JellyEatEffect,
	DashEffect,
	Player,
	RespawnEffect,
	Pet,
	PetMissile,
	PetMissileEatHp,
	Missile,
	Monster,
	OverlayBackGround,
	UnderUi,
	Ui,

	Size,
};

//========================================
//##				Ÿ��					##
//========================================

enum class TypeTile
{
	None,
	Ground,
	Platform,
	Wall,

	Size,
};