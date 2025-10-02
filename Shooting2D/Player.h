#pragma once
#include <unordered_map>
#include "enums.h"
#include "Actor.h"

class Player : public Actor
{
public:
	Player() = delete;
	Player(ResourceID InID) : Actor(InID) {};

	virtual void OnInitialize() override;
	virtual void OnTick(float InDeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;
	virtual void OnOverlap(Actor* InOther) override;

	void HandleKeyState(WPARAM InKey, bool InIsPressed);

	inline float GetSpeed() const { return Speed; }
	inline void SetSpeed(float InSpeed) { Speed = InSpeed; }

private:
	// �÷��̾��� �̵� �ӵ�
	float Speed = 200.0f;

	// �÷��̾� Ű �Է� ����
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;
};