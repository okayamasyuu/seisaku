#pragma once
class Clear : public IGameObject
{
public:
	Clear();
	~Clear();
	bool Start();
	prefab::CSpriteRender* m_spriteRender = nullptr;
};

