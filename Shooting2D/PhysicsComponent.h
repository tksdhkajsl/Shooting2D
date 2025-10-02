#pragma once
#include "Component.h"
#include "enums.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(Actor* InOwner, CollisionType InType = CollisionType::Circle, PhysicsLayer InLayer = PhysicsLayer::None)
		:Component(InOwner), Collision(InType), Layer(InLayer)
	{
	}

	bool IsCollision(PhysicsComponent* InOther) const;

	inline float GetRadius() const { return Data1; }	// ���� �浹�� ������ ��ȯ
	inline float GetWidth() const { return Data1; }		// �簢�� �浹�� �ʺ� ��ȯ
	inline float GetHeight() const { return Data2; }	// �簢�� �浹�� ���� ��ȯ
	inline CollisionType GetCollisionType() const { return Collision; } // �浹 Ÿ�� ��ȯ
	inline PhysicsLayer GetLayer() const { return Layer; } // ���� ���̾� ��ȯ

	inline void SetRadius(float radius) { Data1 = radius; } // ���� �浹�� ������ ����
	inline void SetWidth(float width) { Data1 = width; }	// �簢�� �浹�� �ʺ� ����
	inline void SetHeight(float height) { Data1 = height; } // �簢�� �浹�� ���� ����

private:
	static bool CheckCircltToCircleCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo);
	static bool CheckRectToRectCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo);
	static bool CheckCircleToRectCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo);

	CollisionType Collision = CollisionType::Circle;
	PhysicsLayer Layer = PhysicsLayer::None;
	float Data1 = 0.0f;
	float Data2 = 0.0f;
};

