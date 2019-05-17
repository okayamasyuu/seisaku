#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
#include "block.h"
#include "Coin.h"
#include "hata.h"

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	//block* m_blo[5] = { nullptr };
	int C_count = 0; //ÉRÉCÉìÇÃêî
	bool Clear_flag = false;
	int m_timer = 0;
	hata* ha = nullptr;
	CLevel m_level;
	prefab::CDirectionLight* m_dirLig = nullptr;
};

