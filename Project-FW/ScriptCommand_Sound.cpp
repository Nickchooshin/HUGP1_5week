#include "ScriptCommand_Sound.h"
#include <Windows.h>

#include "ScriptQueueManager.h"
#include "MusicManager.h"

CScriptCommand_Sound::CScriptCommand_Sound(int channel, char *sound, bool stream, bool loop) : m_bPlay(true),
																							   m_nChannel(channel),
																							   m_pSound(NULL)
{
	char filepath[100] ;
	wsprintf(filepath, "Resource/Sound/%s.mp3", sound) ;
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