#include "GrifolsInstructor.h"
#include "ProcessManager.h"

std::list<Process*>	ProcessManager::m_processList;

ProcessManager::ProcessManager()
{
	
}

void	ProcessManager::ClearAllProcess()
{
	std::list<Process*>::iterator procIterator;
	for (procIterator = m_processList.begin(); procIterator != m_processList.end(); procIterator++)
	{
		delete (*procIterator);
	}
	m_processList.clear();
}

ProcessManager::~ProcessManager()
{
	ClearAllProcess();
}


ProcessManager& ProcessManager::Get()
{
	static ProcessManager	staticRef;
	return staticRef;
}


void ProcessManager::AddProcess(Process *process)
{
	m_processList.push_back(process);
}		

void	ProcessManager::DestroyProcess(Process* process)
{
	m_processList.remove(process);
	delete process;
}

void ProcessManager::Update(UdiUpdateParam &updateParam)
{
	std::list<Process*>::iterator procIterator;
	for (procIterator = m_processList.begin(); procIterator != m_processList.end();procIterator++)
	{
		(*procIterator)->Update(updateParam);
	}
}