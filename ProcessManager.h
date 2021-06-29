#pragma once
#include "Process.h"
#include <list>
class ProcessManager
{
public:
	ProcessManager();	
	~ProcessManager();

	static ProcessManager& Get();
	
	void AddProcess(Process *process);
	
	void	Update(UdiUpdateParam &updateParam);
	void	DestroyProcess(Process* process);
	void	ClearAllProcess();
private:
	static std::list<Process*>		m_processList;

};

