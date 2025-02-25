#include "InventoryComponent.h"

void CInventoryComponent::Initialize()
{
}

Cry::Entity::EventFlags CInventoryComponent::GetEventMask() const
{
	return Cry::Entity::EventFlags();
}

void CInventoryComponent::ProcessEvent(const SEntityEvent& event)
{
}
