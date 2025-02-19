/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Author: Michal Kolodziej

Project: TutorialSeries

Purpose: Base structure for items. All items will derive from it.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/



#pragma once
#include <CryEntitySystem/IEntityComponent.h>
#include "ItemProperties.h"

struct SItemComponent : public IEntityComponent
{ 
public:
	
	SItemComponent() = default;
	virtual ~SItemComponent() {}

	virtual void Initialize() override;
	virtual Cry::Entity::EventFlags GetEventMask() const override;
	virtual void ProcessEvent(const SEntityEvent& event) override;
	static void ReflectType(Schematyc::CTypeDesc<SItemComponent>& desc);

	virtual void LoadGeometry();
	virtual void Physicalise();
	virtual SItemProperties* GetProperties()  { return  &m_sItemProperties; }
private:
	SItemProperties m_sItemProperties, m_sPrevItemProperties;

};