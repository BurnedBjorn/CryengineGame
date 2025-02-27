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
	if (gEnv->pFlashUI)
	{
		m_pRedRectangle = gEnv->pFlashUI->GetUIElement("RedRectangle");
		m_pTestButton = gEnv->pFlashUI->GetUIElement("TestButton");
		if (m_pTestButton)
		{
			m_pTestButton->AddEventListener(&m_ButtonEventListener,"aa");
			
		}
		
	}
	
	
	m_pOwner = m_pEntity->GetComponent<CPlayerComponent>();

	
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
		if (m_pTestButton)
		{
			m_pTestButton->SetVisible(true);
			m_pTestButton->SetFlag(IUIElement::EFlashUIFlags::eFUI_HARDWARECURSOR, true);
			m_pTestButton->SetFlag(IUIElement::EFlashUIFlags::eFUI_MOUSEEVENTS, true);
		}
		//gEnv->pHardwareMouse->IncrementCounter();
		CryLog("GameplayStarted");
		
		
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

void CButtonEventListener::Switch(IUIElement* pTarget, bool state)
{
	pTarget->SetVisible(state);
	pTarget->SetFlag(IUIElement::EFlashUIFlags::eFUI_HARDWARECURSOR, state);
	pTarget->SetFlag(IUIElement::EFlashUIFlags::eFUI_MOUSEEVENTS, state);
}

void CButtonEventListener::OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args)
{
	
	const string Click = "Click";
	if (event.sDisplayName==Click)
	{
		Switch(pSender, false);
	}
	
}
