#include "MoveToCommand.h"
#include "diUpdateParam.h"
diMoveToCommand::diMoveToCommand(void)
{
	m_ActorSceneComponent = nullptr;
	m_InitialPos		  = FVector::ZeroVector;
	m_DestPos			  = FVector::ZeroVector;
	m_MoveByOffset        = FVector::ZeroVector;
	m_AnimTime			  = 0.0f;
	m_TimeElapsed		  = 0.0f;
	m_CommandState		  = kIdle;
}

diMoveToCommand::diMoveToCommand(USceneComponent* ActorSceneComponent, float AnimTime, USceneComponent* TargetSceneComponent,bool IsPerUnitTime )
{
	Clear();
	if (IsPerUnitTime)
	{
		FVector curPos		= ActorSceneComponent->GetComponentLocation();
		FVector targetPos	= TargetSceneComponent->GetComponentLocation();
		float distance = FVector::Dist(targetPos, curPos);
		AnimTime = FMath::Abs(AnimTime * distance);
	}	
	Init(ActorSceneComponent, AnimTime);
	SetMoveTo(TargetSceneComponent);
}

diMoveToCommand::diMoveToCommand(USceneComponent* ActorSceneComponent, float AnimTime, const FVector moveToPostion, bool IsPerUnitTime)
{
	if (IsPerUnitTime)
	{
		FVector curPos = ActorSceneComponent->GetComponentLocation();		
		float distance = FVector::Dist(moveToPostion, curPos);
		AnimTime = FMath::Abs(AnimTime * distance);
	}
	Clear();
	Init(ActorSceneComponent, AnimTime);
	m_DestPos = moveToPostion;
}

diMoveToCommand::diMoveToCommand(ComponentObject* ActorSceneComponent, float AnimTime, ComponentObject* TargetSceneComponent, bool IsPerUnitTime)
{
	Clear();
	if (IsPerUnitTime)
	{
		FVector curPos = ActorSceneComponent->GetComponentLocation();
		FVector targetPos = TargetSceneComponent->GetComponentLocation();
		float distance = FVector::Dist(targetPos, curPos);
		AnimTime = FMath::Abs(AnimTime * distance);
	}
	Init(ActorSceneComponent->GetSceneComp(), AnimTime);
	SetMoveTo(TargetSceneComponent->GetSceneComp());
}

diMoveToCommand::diMoveToCommand(ComponentObject* ActorSceneComponent, float AnimTime, const FVector moveToPostion, bool IsPerUnitTime )
{
	if (IsPerUnitTime)
	{
		FVector curPos = ActorSceneComponent->GetComponentLocation();
		float distance = FVector::Dist(moveToPostion, curPos);
		AnimTime = FMath::Abs(AnimTime * distance);
	}
	Clear();
	Init(ActorSceneComponent->GetSceneComp(), AnimTime);
	m_DestPos = moveToPostion;
}

diMoveToCommand::~diMoveToCommand(void)
{

}

void diMoveToCommand::Init(USceneComponent* ActorSceneComponent, float AnimTime)
{
	m_ActorSceneComponent = ActorSceneComponent;
	m_AnimTime			  = AnimTime;
	m_CommandState		  = kIdle;
}

void diMoveToCommand::SetMoveTo(USceneComponent* TargetSceneComponent)
{
	m_DestPos = TargetSceneComponent->GetComponentTransform().GetLocation();
}

void diMoveToCommand::SetMoveTo(const float x, const float y, const float z)
{
	m_DestPos = FVector(x,y,z);
}

void diMoveToCommand::SetMoveBy(const float x, const float y, const float z)
{
	m_MoveByOffset = FVector(x, y, z);
}

void diMoveToCommand::Update(UdiUpdateParam &Updateparam)
{
	if (m_CommandState == kRunning)
	{
		float fraction = m_TimeElapsed / m_AnimTime;
		if (fraction >= 1.0f)
		{
			m_ActorSceneComponent->SetWorldLocation(m_DestPos);
			m_CommandState = kCompleted;
			return;
		}
		FVector lerpLocation = FMath::Lerp(m_InitialPos, m_DestPos, fraction);
		m_ActorSceneComponent->SetWorldLocation(lerpLocation);
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, lerpLocation.ToString());
		m_TimeElapsed += Updateparam.getDeltaTime();
	}
}

void diMoveToCommand::Do()
{
	m_InitialPos	= m_ActorSceneComponent->GetComponentTransform().GetLocation();
	m_DestPos		= m_DestPos + m_MoveByOffset;
	m_CommandState  = kRunning;
	m_TimeElapsed   = 0.0f;
}

void diMoveToCommand::UnDo()
{

}

void diMoveToCommand::Clear()
{
	m_InitialPos	= FVector::ZeroVector;
	m_DestPos		= FVector::ZeroVector;
	m_MoveByOffset	= FVector::ZeroVector;
	m_TimeElapsed	= 0.0f;
	m_CommandState	= kIdle;
}