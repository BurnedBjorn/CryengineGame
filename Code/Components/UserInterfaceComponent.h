#pragma once
#include <FlashUI/FlashUI.h>
#include <CryEntitySystem/IEntityComponent.h>

class CPlayerUI : public IEntityComponent
{
public:
	CPlayerUI() = default;
	virtual ~CPlayerUI() {};
	virtual void Initialize() override;
	virtual Cry::Entity::EventFlags GetEventMask() const override;
	virtual void ProcessEvent(const SEntityEvent& event) override;

	static void ReflectType(Schematyc::CTypeDesc<CPlayerUI>& desc);

	void TurnOn();
protected:
private:
	IUIElement* m_pRedRectangle = nullptr;
	bool m_bTurnedOn = false;

};