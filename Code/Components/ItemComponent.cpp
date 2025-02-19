#include "StdAfx.h"
#include "ItemComponent.h"
#include <CrySchematyc/Env/Elements/EnvComponent.h>
#include "CryPhysics/physinterface.h"



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

namespace{
	static void RegisterItem(Schematyc::IEnvRegistrar& registar)
	{
		Schematyc::CEnvRegistrationScope scope = registar.Scope(IEntity::GetEntityScopeGUID());
		{
			Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(SItemComponent));
			{
			}
		}
	}
	CRY_STATIC_AUTO_REGISTER_FUNCTION(&RegisterItem)
}
void SItemComponent::Initialize()
{
	LoadGeometry();
	Physicalise();

}

Cry::Entity::EventFlags SItemComponent::GetEventMask() const
{
	return Cry::Entity::EEvent::EditorPropertyChanged;
}

void SItemComponent::ProcessEvent(const SEntityEvent& event)
{
	switch (event.event)
	{
	case Cry::Entity::EEvent::EditorPropertyChanged:
	{
		if (m_sItemProperties != m_sPrevItemProperties) {
			m_sPrevItemProperties = m_sItemProperties;

			LoadGeometry();
			Physicalise();
		}
	}
	break;
	default:
		break;
	}
}





void SItemComponent::ReflectType(Schematyc::CTypeDesc<SItemComponent>& desc)
{
	desc.SetGUID("{6CAA8B9A-8923-49B1-B620-FBCF089AAC8E}"_cry_guid);
	desc.SetLabel("ItemComponent");
	desc.SetDescription("Base Item Component");
	desc.AddMember(&SItemComponent::m_sItemProperties, 'itep', "ItemProperties", "Item Properties", "This Item's Properties",SItemProperties());
	desc.SetEditorCategory("Item");
	desc.SetComponentFlags(IEntityComponent::EFlags::Singleton);
}

void SItemComponent::LoadGeometry()
{
	string sGeomPath = GetProperties()->m_sRenderProperties.m_sGeomPath.value.c_str();
	if (sGeomPath.empty()) return;
	m_pEntity->LoadGeometry(GEOMETRY_SLOT, sGeomPath);

}

void SItemComponent::Physicalise()
{
	SEntityPhysicalizeParams physParams;
	physParams.mass = GetProperties()->m_sPhysicsProperties.m_fMass;
	physParams.type = PE_RIGID;
	m_pEntity->Physicalize(physParams);
}
