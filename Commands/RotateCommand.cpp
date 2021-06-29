#include "GrifolsInstructor.h"
#include "RotateCommand.h"
#include "diUpdateParam.h"
diRotateCommand::diRotateCommand()
{
	m_ActorSceneComponent = nullptr;	
	m_InitialQuat = FQuat::Identity;
	m_DestQuat = FQuat::Identity;
	m_AnimTime = 0.0f;
	m_TimeElapsed = 0.0f;
	m_CommandState = kIdle;
}

diRotateCommand::diRotateCommand(USceneComponent* ActorSceneComponent, float AnimTime,const FQuat& DestQuat)
{
	diRotateCommand();
	Init(ActorSceneComponent, AnimTime);
	SetRotation(DestQuat);
}

diRotateCommand::diRotateCommand(ComponentObject* ActorSceneComponent, float AnimTime, const FQuat& DestQuat)
{
	diRotateCommand();
	Init(ActorSceneComponent->GetSceneComp(), AnimTime);
	SetRotation(DestQuat);
}

diRotateCommand::~diRotateCommand()
{

}

void diRotateCommand::Init(USceneComponent* ActorSceneComponent, float AnimTime)
{
	m_ActorSceneComponent = ActorSceneComponent;
	m_AnimTime = AnimTime;
	m_CommandState = kIdle;
}

void diRotateCommand::SetRotation(const FQuat& DestQuat)
{	
	m_DestQuat = DestQuat;
}

void diRotateCommand::Update(UdiUpdateParam &UpdateParam)
{
	if (m_CommandState == kRunning)
	{
		float fraction = m_TimeElapsed / m_AnimTime;
		if (fraction >= 1.0f)
		{			
			m_ActorSceneComponent->SetWorldRotation(m_DestQuat.Rotator());
			m_CommandState = kCompleted;
			return;
		}
		FQuat lerpOrientation = FMath::Lerp(m_InitialQuat, m_DestQuat, fraction);

		m_ActorSceneComponent->SetWorldRotation(lerpOrientation.Rotator());

		m_TimeElapsed += UpdateParam.getDeltaTime();
	}
}

void diRotateCommand::Do()
{
	m_InitialQuat = m_ActorSceneComponent->GetComponentTransform().GetRotation();
	m_CommandState = kRunning;
	m_TimeElapsed = 0.0f;
}

void diRotateCommand::UnDo()
{
}

void diRotateCommand::Clear()
{	
	m_InitialQuat = FQuat::Identity;
	m_DestQuat = FQuat::Identity;
	m_TimeElapsed = 0.0f;
	m_CommandState = kIdle;
}