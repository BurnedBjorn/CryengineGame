#pragma once
#include "Components/ItemComponent.h"

class CInventoryComponent : public SItemComponent
{
public:
	CInventoryComponent()= default;
	~CInventoryComponent() { /*delete[] m_paInventory; delete[] m_paQuickAccess; */}
	virtual void Initialize() override;
	virtual Cry::Entity::EventFlags GetEventMask() const override;
	virtual void ProcessEvent(const SEntityEvent& event) override;
	//inventory system
	//std::vector<SItemComponent> m_vInventory;
	//std::vector<SItemComponent> m_vQuickAccess;
	
protected:
private:
	SItemComponent* m_paInventory[20] = { nullptr };
	SItemComponent* m_paQuickAccess[5] = { nullptr };
};

