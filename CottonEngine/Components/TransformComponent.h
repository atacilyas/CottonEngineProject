#pragma once

#include "../stdafx.h"
class TransformComponent
{
public:
	TransformComponent();
	virtual ~TransformComponent();

	void SetParent(TransformComponent *parent);

	//position
	const DOUBLE2& GetPosition() const { return m_Position; }
	const DOUBLE2& GetWorldPosition() const { return m_WorldPosition; }
	void Translate(float x, float y);
	void Translate(const DOUBLE2& position);
	void Move(const DOUBLE2& move);
	void Move(float x, float y);

	//rotation
	const float& GetRotation() const { return m_Rotation; }
	const float& GetWorldRotation() const { return m_WorldRotation; }
	void Rotate(float x, bool isEuler = true);

	//scale
	const DOUBLE2& GetScale() const { return m_Scale; }
	const DOUBLE2& GetWorldScale() const { return m_WorldScale; }
	void Scale(float x, float y);
	void Scale(const DOUBLE2& scale);

	void UpdateTransforms(float deltatime);

private:
	TransformComponent *m_pParent;
	DOUBLE2 m_Position, m_WorldPosition, m_Scale, m_WorldScale;
	float m_Rotation, m_WorldRotation;
};

