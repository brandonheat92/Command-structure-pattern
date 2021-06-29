#pragma once
#include "Commands.h"
#include "ComponentObject.h"

class diRotateCommand : public diCommand
{
public:

	diRotateCommand(void);	

	//constructor overload that calls the Init and destination commands during creation
	diRotateCommand(USceneComponent* ActorSceneComponent, float AnimTime,const FQuat& DestQuat);
	diRotateCommand(ComponentObject* ActorSceneComponent, float AnimTime, const FQuat& DestQuat);

	virtual ~diRotateCommand(void);

	void Init(USceneComponent* ActorSceneComponent, float AnimTime);

	void SetRotation(const FQuat& DestQuat);

	virtual void Update(UdiUpdateParam &UpdateParam);
	virtual void Do();
	virtual void UnDo();
	virtual void Clear();

	enum TCommandType GetCommandType() { return kRotateCommand; }

protected:

	USceneComponent*	m_ActorSceneComponent;	
	FQuat			    m_InitialQuat;
	FQuat			    m_DestQuat;
	float				m_TimeElapsed;
	float				m_AnimTime;

};
