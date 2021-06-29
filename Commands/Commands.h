#pragma once
#include <vector>

#include "diUpdateParam.h"

enum TCommandType
{
	kDragCommand,
	kMoveToCommand,
	kNestedMovesCommand,
	kSelectObjectCommand,
	kOrientToCommand,
	kRotateCommand,
	kNestedOrientsCommand,
	kShowPathCommand,
	kTimerCommand,
	kRetrieveMTUCommand,
	kLoadMTUSetCommand,
	kFeedMTUCommand,
	kSplineCommand,
	kNumCommands
};

class diCommand
{
	public:
		
		enum TCommandState
		{
			kIdle,
			kRunning,
			kPause,
			kCompleted,
			kNumCommandStates
		};

		diCommand(void){ m_CommandState = kIdle;}
		virtual ~diCommand(void){}

		virtual void Update(UdiUpdateParam &UpdateParam) = 0;
		virtual void Do() = 0;
		virtual void UnDo() = 0;
		virtual enum TCommandType GetCommandType() = 0;

		virtual void Stop() { m_CommandState = kIdle; }
		bool IsCommandCompleted() const { return (m_CommandState == kCompleted); }
		enum TCommandState GetCommandState()const { return m_CommandState; }
		void AddCommandLink(diCommand * command) { m_linkedCmds.push_back(command); }

	protected:

		enum TCommandState			m_CommandState;
		std::vector<diCommand*>		m_linkedCmds;

};