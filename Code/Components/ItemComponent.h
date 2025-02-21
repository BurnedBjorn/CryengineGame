/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Author: Michal Kolodziej

Project: TutorialSeries

Purpose: Base structure for items. All items will derive from it.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

class CPlayerComponent; //Change later if want to allow npc to wield the item ?

#pragma once
#include <CryEntitySystem/IEntityComponent.h>
#include "ItemProperties.h"

struct SItemComponent : public IEntityComponent
{ 
public:
	
	SItemComponent() = default;
	virtual ~SItemComponent() {}

	virtual void Initialize() override;
	virtual void InitializeClass() = 0;
	virtual Cry::Entity::EventFlags GetEventMask() const override;
	virtual void ProcessEvent(const SEntityEvent& event) override;
	virtual void ProcessEventClass(const SEntityEvent& event) = 0;
	static void ReflectType(Schematyc::CTypeDesc<SItemComponent>& desc);

	virtual void LoadGeometry();
	virtual void Physicalise();
	virtual SItemProperties* GetProperties()  { return  &m_sItemProperties; }

	virtual void PickUp(CPlayerComponent* pNewOwner);
	virtual bool IsPickable();
protected:
	SItemProperties m_sItemProperties, m_sPrevItemProperties;

	CPlayerComponent* m_pOwner = nullptr;
};