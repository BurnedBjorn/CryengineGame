#pragma once
#include <StdAfx.h>

#include <CrySchematyc/ResourceTypes.h>
#include <CrySchematyc/Reflection/TypeDesc.h>

enum ItemGeometrySlot
{
	GEOMETRY_SLOT = 0
};


// Render properties
struct SRenderProperties
{
	inline bool operator==(const SRenderProperties& rhs) const { return 0 == memcmp(this, &rhs, sizeof(rhs)); }
	inline bool operator!=(const SRenderProperties& rhs) const { return 0 != memcmp(this, &rhs, sizeof(rhs)); }

	Schematyc::GeomFileName m_sGeomPath;
	Schematyc::MaterialFileName m_sMaterial;
};
static void ReflectType(Schematyc::CTypeDesc<SRenderProperties>& desc) 
{
	desc.SetGUID("{F993FAD7-B354-4CDC-B643-1053C88579DF}"_cry_guid);
	desc.SetLabel("Render properties");
	desc.SetDescription("Render properties");
	desc.AddMember(&SRenderProperties::m_sGeomPath, 'geom', "GeometryPath", "Geometry Path", "Path to geometry file of this item", "");
	desc.AddMember(&SRenderProperties::m_sMaterial, 'smat', "MaterialPath", "Material Path", "Path to material file of this item", "");
}


//Physics properties
struct SPhysicsProperties
{
	inline bool operator==(const SPhysicsProperties& rhs) const { return 0 == memcmp(this, &rhs, sizeof(rhs)); }
	inline bool operator!=(const SPhysicsProperties& rhs) const { return 0 != memcmp(this, &rhs, sizeof(rhs)); }

	float m_fMass;
};
static void ReflectType(Schematyc::CTypeDesc<SPhysicsProperties>& desc)
{
	desc.SetGUID("{1C7F557C-7848-4210-A867-D4FDF69C3103}"_cry_guid);
	desc.SetLabel("Physics properties");
	desc.SetDescription("Physics properties");
	desc.AddMember(&SPhysicsProperties::m_fMass, 'mass', "Mass", "Mass", "Mass of the item for physics", ZERO);

}


//MAIN PROPERTY STRUCTURE
struct SItemProperties
{
	inline bool operator==(const SItemProperties& rhs) const { return 0 == memcmp(this, &rhs, sizeof(rhs)); }
	inline bool operator!=(const SItemProperties& rhs) const { return 0 != memcmp(this, &rhs, sizeof(rhs)); }

	SRenderProperties m_sRenderProperties, m_sPrevRenderProperties;
	SPhysicsProperties m_sPhysicsProperties;
};
static void ReflectType(Schematyc::CTypeDesc<SItemProperties>& desc)
{
	desc.SetGUID("{DBB552AF-3FD7-4718-9BE9-C4563890B64F}"_cry_guid);
	desc.SetLabel("Item properties");
	desc.SetDescription("Item properties");
	desc.AddMember(&SItemProperties::m_sRenderProperties, 'rprs', "RenderProperties", "Render Settings", "Render settings of this item", SRenderProperties());
	desc.AddMember(&SItemProperties::m_sPhysicsProperties, 'pspr', "PhysicsProperties", "Physics Settings", "Physics settings of this item", SPhysicsProperties());
}

