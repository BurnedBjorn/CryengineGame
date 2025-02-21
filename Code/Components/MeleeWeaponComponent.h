/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Author: Michal Kolodziej

Project: TutorialSeries

Purpose: Melee weapon base class

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


#pragma once
#include <CryEntitySystem/IEntityComponent.h>
#include "MeleeWeaponProperties.h"
#include "ItemComponent.h"


class CMeleeWeaponComponent : public SItemComponent
{
public:
	CMeleeWeaponComponent ()= default;
	virtual  ~CMeleeWeaponComponent() {}

	virtual void InitializeClass() override;
	
	virtual void ProcessEventClass(const SEntityEvent& event) override;
	static void ReflectType(Schematyc::CTypeDesc<CMeleeWeaponComponent>& desc);

protected:
private:

};

