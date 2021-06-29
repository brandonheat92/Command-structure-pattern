#pragma once

#include "Commands.h"
#include "diUpdateParam.h"
#include <queue>

class LinearDistributor;
class Object;
class ObjectHolder;
/**
Currently the process starts executing as soon as a command is added, if need arises add a do or execute 
function to delay the process execution in code
**/
class Process
{
	public:
		Process();
		~Process();

		//adds a command to execute to the command stack, ---------the process takes ownership of the command		
		void AddCommand(diCommand *command);

		//update called continously in an process manager or another class
		void Update(UdiUpdateParam &updateParam);

		/** returns whether the process is processing any commands currently
		@return if any command is being processed
		**/
		bool isProcessing();	

		int GetNoOfCommands();

	private:

		void ProcessUpdate(UdiUpdateParam &updateParam);

		void DestroyCurrentCommand();

		void ProcessNextCommand();

		enum TProcessState
		{
			kIdle,
			kProcessing
		};
		void ChangeState(TProcessState state);

		std::queue<diCommand*>	m_commandQueue;
		diCommand				*m_currentCommand;
		TProcessState			m_currentState;
};