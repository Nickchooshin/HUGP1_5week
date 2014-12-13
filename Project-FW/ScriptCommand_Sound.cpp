#include "ScriptCommand_Sound.h"

#include "ScriptQueueManager.h"
#include "MusicManager.h"

CScriptCommand_Sound::CScriptCommand_Sound(int channel, char *filepath, bool stream, bool loop) : m_bPlay(true),
																								  m_nChannel(channel),
																								  m_pSound(NULL)
{
	m_pSound = g_MusicManager->LoadMusic(filepath, stream, loop) ;
}
CScriptCommand_Sound::CScriptCommand_Sound(int channel) : m_bPlay(false),
														  m_nChannel(channel),
														  m_pSound(NULL)
{
}
CScriptCommand_Sound::~CScriptCommand_Sound()
{
}

void CScriptCommand_Sound::Update()
{
	if(m_bPlay)
		g_MusicManager->PlayMusic(m_pSound, m_nChannel) ;
	else
		g_MusicManager->StopMusic(m_nChannel) ;

	m_bLife = false ;
}