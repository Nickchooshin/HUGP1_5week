#pragma once

#include "Singleton.h"
#include <queue>

class CScriptCommand ;

class CScriptQueueManager : public Singleton<CScriptQueueManager>
{
private :
	std::queue<CScriptCommand*> m_CommandQueue ;
	CScriptCommand *m_pNowCommand ;
	bool m_bQueueEnd ;

public :
	CScriptQueueManager() ;
	~CScriptQueueManager() ;

	bool LoadScript(char *filename) ;

	const bool BeQueueEnd() const ;

	void ClearQueue() ;

	void Update() ;
} ;

#define g_ScriptQueueManager CScriptQueueManager::GetInstance()