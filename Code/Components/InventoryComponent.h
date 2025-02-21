#pragma once
#include "Components/ItemComponent.h"

class CInventoryComponent : public SItemComponent
{
public:
	CInventoryComponent()= default;
	~CInventoryComponent() {}
	virtual void InitializeClass() override;
protected:
private:

};

