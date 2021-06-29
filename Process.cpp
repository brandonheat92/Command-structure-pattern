#include "GrifolsInstructor.h"
#include "Process.h"

Process::Process()
{
	m_currentCommand = nullptr;
}

Process::~Process()
{
	while (!m_commandQueue.empty())
	{
		diCommand *command = m_commandQueue.front();
		m_commandQueue.pop();
		delete command;		
	}
	m_currentCommand = nullptr; 
}

bool Process::isProcessing()
{
	bool isProcessing = (m_currentState == kProcessing) ? true : false;
	return isProcessing;
}

void Process::Update(UdiUpdateParam &updateParam)
{
	switch (m_currentState)
	{
		case kIdle:
		{
			break;
		}
		case kProcessing:
		{
			ProcessUpdate(updateParam);
			break;
		}
	}
}


void Process::ProcessUpdate(UdiUpdateParam &updateParam)
{
	if (m_currentCommand != nullptr)
	{
		//check if the command completed and then dispose of the command
		if (m_currentCommand->IsCommandCompleted() == true)
		{
			DestroyCurrentCommand();
			ProcessNextCommand();
		}

		if (m_currentCommand)
		{
			m_currentCommand->Update(updateParam);
		}	
	}
}

int Process::GetNoOfCommands()
{
	int temp = m_commandQueue.size();
	return temp;
}

void Process::DestroyCurrentCommand()
{
	if (m_currentCommand != nullptr)
	{
		m_commandQueue.pop();
		delete m_currentCommand;
		m_currentCommand = nullptr;		
	}
}

void Process::ProcessNextCommand()
{
	if (!m_commandQueue.empty())
	{
		m_currentCommand = m_commandQueue.front();
		m_currentCommand->Do();		
	}
	else
	{
		ChangeState(kIdle);
	}
}

void Process::ChangeState(TProcessState state)
{
	m_currentState = state;
}

void Process::AddCommand(diCommand *command)
{
	if (m_commandQueue.empty())
	{
		m_currentCommand = command;
		m_currentCommand->Do();
	}
	m_commandQueue.push(command);
	ChangeState(kProcessing);
}

