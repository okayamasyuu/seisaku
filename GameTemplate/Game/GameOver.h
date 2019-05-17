#pragma once
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();
	bool Start();
	prefab::CSpriteRender* m_sprite = nullptr;
};

