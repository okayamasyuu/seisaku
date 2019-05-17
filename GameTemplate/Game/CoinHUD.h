#pragma once
#include "Game.h"
class CoinHUD : public IGameObject
{
public:
	CoinHUD();
	~CoinHUD();
	bool  Start();
	void Update();
	prefab::CFontRender* Cfont = nullptr;
	Game* ga = nullptr;
};

