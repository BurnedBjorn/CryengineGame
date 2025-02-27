#pragma once
#include <FlashUI/FlashUI.h>
#include <CryEntitySystem/IEntityComponent.h>

#include "Player.h"

class CButtonEventListener : public IUIElementEventListener
{
public:
	virtual void OnUIEvent(IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args);
	void Switch(IUIElement* pTarget, bool state);
};


class CPlayerUI : public IEntityComponent
{
public:
	
	CPlayerUI() = default;
	virtual ~CPlayerUI() {};
	virtual void Initialize() override;
	virtual Cry::Entity::EventFlags GetEventMask() const override;
	virtual void ProcessEvent(const SEntityEvent& event) override;

	static void ReflectType(Schematyc::CTypeDesc<CPlayerUI>& desc);


	

	
protected:
private:
	IUIElement* m_pRedRectangle = nullptr;
	bool m_bTurnedOn = false;

	IUIElement* m_pTestButton = nullptr;


	CPlayerComponent* m_pOwner = nullptr;

	CButtonEventListener m_ButtonEventListener;

};