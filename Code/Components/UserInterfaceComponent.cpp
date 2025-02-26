#include "UserInterfaceComponent.h"






static void RegisterPlayerUI(Schematyc::IEnvRegistrar& registar)
{
	Schematyc::CEnvRegistrationScope scope = registar.Scope(IEntity::GetEntityScopeGUID());
	{
		Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CPlayerUI));
		{
		}
	}
}
CRY_STATIC_AUTO_REGISTER_FUNCTION(&RegisterPlayerUI)





void CPlayerUI::Initialize()
{
	m_pRedRectangle = gEnv->pFlashUI->GetUIElement("RedRectangle");
}

Cry::Entity::EventFlags CPlayerUI::GetEventMask() const
{
	return Cry::Entity::EEvent::Update | Cry::Entity::EEvent::GameplayStarted;
}

void CPlayerUI::ProcessEvent(const SEntityEvent& event)
{
	switch (event.event)
	{
	case Cry::Entity::EEvent::GameplayStarted:
	{
		m_pRedRectangle->SetVisible(true);
		if (m_pRedRectangle->IsVisible())
		{
			CryLog("Visible");
		}
		else
		{
			CryLog("notVisible");
		}
	}
	break;
	default:
		break;
	}
}

void CPlayerUI::ReflectType(Schematyc::CTypeDesc<CPlayerUI>& desc)
{
	desc.SetGUID("{935A42CF-F92C-4CB3-8FB2-289C194D7A0C}"_cry_guid);
	desc.SetEditorCategory("UI");
	desc.SetLabel("Player UI");
}


