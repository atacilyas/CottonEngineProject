#include "TransformComponent.h"


TransformComponent::TransformComponent()
	:m_pParent(nullptr),
	m_Position(0, 0),
	m_WorldPosition(0,0),
	m_Scale(1,1),
	m_WorldScale(1,1),
	m_Rotation(0),
	m_WorldRotation(0)
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::SetParent(TransformComponent *parent)
{
	m_pParent = parent;
}

//position
void TransformComponent::Translate(float x, float y)
{
	m_Position = DOUBLE2(x, y);
	m_WorldPosition = m_Position;
}

void TransformComponent::Translate(const DOUBLE2& position)
{
	m_Position = position;
	m_WorldPosition = m_Position;
}

void TransformComponent::Move(float x, float y)
{
	m_Position += DOUBLE2(x, y);
	m_WorldPosition = m_Position;
}

void TransformComponent::Move(const DOUBLE2& move)
{
	m_Position += move;
	m_WorldPosition = m_Position;
}

//rotation
void TransformComponent::Rotate(float angle, bool isEuler)
{
	if (isEuler)
	{
		m_Rotation = angle;
	}
	else
	{
		m_Rotation = (angle * 180.0f) / (float)M_PI;
	}
	m_WorldRotation = m_Rotation;
}

//scale
void TransformComponent::Scale(float x, float y)
{
	m_Scale = DOUBLE2(x, y);
	m_WorldScale = m_Scale;
}

void TransformComponent::Scale(const DOUBLE2& scale)
{
	m_Scale = scale;
	m_WorldScale = m_Scale;
}

void TransformComponent::UpdateTransforms(float deltatime)
{
	UNREFERENCED_PARAMETER(deltatime);
	if (m_pParent != nullptr)
	{
		//rotation
		m_WorldRotation = m_Rotation + m_pParent->GetWorldRotation();

		//rotate position around parent position
		float x = (m_WorldRotation * (float)M_PI) / 180.0f;
		auto newX = m_Position.x * cos(x) - m_Position.y*sin(x);
		auto newY = m_Position.x * sin(x) + m_Position.y*cos(x);
		
		m_WorldPosition.x = newX;
		m_WorldPosition.y = newY;
		
		//position
		m_WorldPosition += m_pParent->GetWorldPosition();

		//scale
		m_WorldScale = m_Scale * m_pParent->GetWorldScale();
	}
}