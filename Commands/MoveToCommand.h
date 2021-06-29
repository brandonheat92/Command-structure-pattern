#ifndef DC_MOVETO_COMMANDS_H
#define DC_MOVETO_COMMANDS_H
#include "ComponentObject.h"
#include "Commands.h"

class diMoveToCommand :	public diCommand
{
	public:

		diMoveToCommand(void);

		diMoveToCommand(USceneComponent* ActorSceneComponent, float AnimTime, USceneComponent* TargetSceneComponent,bool IsPerUnitTime = false);
		diMoveToCommand(USceneComponent* ActorSceneComponent, float AnimTime, const FVector moveToPostion, bool IsPerUnitTime = false);
		
		diMoveToCommand(ComponentObject* ActorSceneComponent, float AnimTime, ComponentObject* TargetSceneComponent, bool IsPerUnitTime = false);
		diMoveToCommand(ComponentObject* ActorSceneComponent, float AnimTime, const FVector moveToPostion, bool IsPerUnitTime = false);

		virtual ~diMoveToCommand(void);

		void Init(USceneComponent* ActorSceneComponent, float AnimTime);

		void SetMoveTo(USceneComponent* TargetSceneComponent);
		void SetMoveTo(const float x, const float y, const float z);
		void SetMoveBy(const float x, const float y, const float z);

		virtual void Update(UdiUpdateParam &Updateparam);
		virtual void Do();
		virtual void UnDo();
		void Clear();

		enum TCommandType GetCommandType() { return kMoveToCommand;}

	protected:

		USceneComponent*	m_ActorSceneComponent;
		FVector				m_InitialPos;
		FVector				m_DestPos;
		FVector				m_MoveByOffset;
		float				m_TimeElapsed;
		float				m_AnimTime;

};

#endif