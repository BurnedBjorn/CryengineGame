#include "StdAfx.h"
#include "Player.h"
#include "ItemComponent.h"

#define PICKUP_RANGE 3.f


void CPlayerComponent::UpdateMovementRequest(float frameTime)
{
	// Don't handle input if we are in air
	if (!m_pCharacterController->IsOnGround())
		return;

	Vec3 velocity = ZERO;

	const float moveSpeed = 20.5f;

	if (m_inputFlags & EInputFlag::MoveLeft)
	{
		velocity.x -= moveSpeed * frameTime;
	}
	if (m_inputFlags & EInputFlag::MoveRight)
	{
		velocity.x += moveSpeed * frameTime;
	}
	if (m_inputFlags & EInputFlag::MoveForward)
	{
		velocity.y += moveSpeed * frameTime;
	}
	if (m_inputFlags & EInputFlag::MoveBack)
	{
		velocity.y -= moveSpeed * frameTime;
	}

	m_pCharacterController->AddVelocity(GetEntity()->GetWorldRotation() * velocity);
}

void CPlayerComponent::UpdateLookDirectionRequest(float frameTime)
{
	const float rotationSpeed = 0.002f;
	const float rotationLimitsMinPitch = -0.84f;
	const float rotationLimitsMaxPitch = 1.5f;

	// Apply smoothing filter to the mouse input
	m_mouseDeltaRotation = m_mouseDeltaSmoothingFilter.Push(m_mouseDeltaRotation).Get();

	// Update angular velocity metrics
	m_horizontalAngularVelocity = (m_mouseDeltaRotation.x * rotationSpeed) / frameTime;
	m_averagedHorizontalAngularVelocity.Push(m_horizontalAngularVelocity);

	// Start with updating look orientation from the latest input
	Ang3 ypr = CCamera::CreateAnglesYPR(Matrix33(m_lookOrientation));

	// Yaw
	ypr.x += m_mouseDeltaRotation.x * rotationSpeed;

	// Pitch
	// TODO: Perform soft clamp here instead of hard wall, should reduce rot speed in this direction when close to limit.
	ypr.y = CLAMP(ypr.y + m_mouseDeltaRotation.y * rotationSpeed, rotationLimitsMinPitch, rotationLimitsMaxPitch);

	// Roll (skip)
	ypr.z = 0;

	m_lookOrientation = Quat(CCamera::CreateOrientationYPR(ypr));

	// Reset the mouse delta accumulator every frame
	m_mouseDeltaRotation = ZERO;
}

void CPlayerComponent::UpdateAnimation(float frameTime)
{
	const float angularVelocityTurningThreshold = 0.174; // [rad/s]

	// Update tags and motion parameters used for turning
	const bool isTurning = std::abs(m_averagedHorizontalAngularVelocity.Get()) > angularVelocityTurningThreshold;
	m_pAnimationComponent->SetTagWithId(m_rotateTagId, isTurning);
	if (isTurning)
	{
		// TODO: This is a very rough predictive estimation of eMotionParamID_TurnAngle that could easily be replaced with accurate reactive motion 
		// if we introduced IK look/aim setup to the character's model and decoupled entity's orientation from the look direction derived from mouse input.

		const float turnDuration = 1.0f; // Expect the turning motion to take approximately one second.
		m_pAnimationComponent->SetMotionParameter(eMotionParamID_TurnAngle, m_horizontalAngularVelocity * turnDuration);
	}

	// Update active fragment
	const FragmentID& desiredFragmentId = m_pCharacterController->IsWalking() ? m_walkFragmentId : m_idleFragmentId;
	if (m_activeFragmentId != desiredFragmentId)
	{
		m_activeFragmentId = desiredFragmentId;
		m_pAnimationComponent->QueueFragmentWithId(m_activeFragmentId);
	}

	// Update entity rotation as the player turns
	// We only want to affect Z-axis rotation, zero pitch and roll
	Ang3 ypr = CCamera::CreateAnglesYPR(Matrix33(m_lookOrientation));
	ypr.y = 0;
	ypr.z = 0;
	const Quat correctedOrientation = Quat(CCamera::CreateOrientationYPR(ypr));

	// Send updated transform to the entity, only orientation changes
	GetEntity()->SetPosRotScale(GetEntity()->GetWorldPos(), correctedOrientation, Vec3(1, 1, 1));
}

void CPlayerComponent::UpdateCamera(float frameTime)
{
	Ang3 ypr = CCamera::CreateAnglesYPR(Matrix33(m_lookOrientation));

	// Ignore z-axis rotation, that's set by CPlayerAnimations
	ypr.x = 0;

	// Start with changing view rotation to the requested mouse look orientation
	Matrix34 localTransform = IDENTITY;
	localTransform.SetRotation33(CCamera::CreateOrientationYPR(ypr));

	// Offset the player along the forward axis (normally back)
	// Also offset upwards
	const float viewOffsetForward = -1.5f;
	const float viewOffsetUp = 2.f;
	localTransform.SetTranslation(Vec3(0, viewOffsetForward, viewOffsetUp));

	m_pCameraComponent->SetTransformMatrix(localTransform);
	m_pAudioListenerComponent->SetOffset(localTransform.GetTranslation());
}

void CPlayerComponent::Update(float frameTime)
{
	ray_hit hit;
	Vec3 cameraDirection=gEnv->pSystem->GetViewCamera().GetViewdir();
	Vec3 cameraLocation = gEnv->pSystem->GetViewCamera().GetPosition()+cameraDirection;
	static const unsigned int rayFlags = rwi_stop_at_pierceable | rwi_colltype_any;
	if (gEnv->pPhysicalWorld->RayWorldIntersection(cameraLocation,(cameraDirection*PICKUP_RANGE),ent_all,rayFlags, &hit,1, m_pEntity->GetPhysicalEntity()))
	{
		gEnv->pRenderer->GetIRenderAuxGeom()->DrawLine(hit.pt - Vec3(0.f, 0.f, 1.0f), ColorB(255, 0, 0), hit.pt + Vec3(0.f, 0.f, 1.0f), ColorB(255, 0, 0), 6.0f);
		gEnv->pRenderer->GetIRenderAuxGeom()->DrawLine(hit.pt - Vec3(0.f, 1.0f, 0.f), ColorB(255, 0, 0), hit.pt + Vec3(0.f, 1.0f, 0.f), ColorB(255, 0, 0), 6.0f);
		gEnv->pRenderer->GetIRenderAuxGeom()->DrawLine(hit.pt - Vec3(1.0f, 0.f, 0.f), ColorB(255, 0, 0), hit.pt + Vec3(1.0f, 0.f, 0.f), ColorB(255, 0, 0), 6.0f);

		if (hit.pCollider)
		{
			if (IEntity* pColliderEntity= gEnv->pEntitySystem->GetEntityFromPhysics(hit.pCollider))
			{
				if (SItemComponent* pColliderItem=pColliderEntity->GetComponent<SItemComponent>())
				{
					ShowPickupMessage(pColliderItem->GetEntity()->GetName());
				}
			}
		}
	}

}

void CPlayerComponent::ShowPickupMessage(string ItemName)
{
	Vec2 screenMid={gEnv->pRenderer->GetWidth()/2.f, gEnv->pRenderer->GetHeight()/2.f};
	ColorF pfWhite = { 1.f,1.f,1.f,1.f };
	string sPickupMessage = "Pick up " + ItemName;
	gEnv->pRenderer->GetIRenderAuxGeom()->Draw2dLabel(screenMid.x, screenMid.y, 1.5f, pfWhite, true, sPickupMessage);
}


