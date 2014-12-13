#pragma once

#include "ScriptCommand.h"
#include <fmod.hpp>

class CScriptCommand_Sound : public CScriptCommand
{
private :
	bool m_bPlay ;
	int m_nChannel ;
	FMOD::Sound *m_pSound ;

public :
	CScriptCommand_Sound(int channel, char *sound, bool stream, bool loop) ;
	CScriptCommand_Sound(int channel) ;
	~CScriptCommand_Sound() ;

	void Update() ;
} ;