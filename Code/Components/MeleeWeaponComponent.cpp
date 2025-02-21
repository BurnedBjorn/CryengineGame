#include "StdAfx.h"
#include "MeleeWeaponComponent.h"


#include <CrySchematyc/Reflection/TypeDesc.h>
#include <CrySchematyc/Utils/EnumFlags.h>
#include <CrySchematyc/Env/IEnvRegistry.h>
#include <CrySchematyc/Env/IEnvRegistrar.h>
#include <CrySchematyc/Env/Elements/EnvFunction.h>
#include <CrySchematyc/Env/Elements/EnvSignal.h>
#include <CrySchematyc/ResourceTypes.h>
#include <CrySchematyc/MathTypes.h>
#include <CrySchematyc/Utils/SharedString.h>
#include <CryCore/StaticInstanceList.h>
static void RegisterMeleeWeapon(Schematyc::IEnvRegistrar& registar)
{
	Schematyc::CEnvRegistrationScope scope = registar.Scope(IEntity::GetEntityScopeGUID());
	{
		Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CMeleeWeaponComponent));
		{
		}
	}
}
CRY_STATIC_AUTO_REGISTER_FUNCTION(&RegisterMeleeWeapon)

void CMeleeWeaponComponent::InitializeClass()
{
}





void CMeleeWeaponComponent::ProcessEventClass(const SEntityEvent& event)
{
}

void CMeleeWeaponComponent::ReflectType(Schematyc::CTypeDesc<CMeleeWeaponComponent>& desc)
{
	desc.SetGUID("{2DCF992D-8BD7-49FD-B608-36E05FC05B65}"_cry_guid);
	desc.AddBase<SItemComponent>();
	desc.SetLabel("Melee Weapon Component");
	desc.SetDescription("Melee Weapon Base Class");
	desc.AddMember(&CMeleeWeaponComponent::m_sItemProperties, 'itep', "WeaponProperties", "Weapon Properties", "This Weapon's Properties", SItemProperties());
	desc.SetEditorCategory("Items/Weapons/Melee");
}
