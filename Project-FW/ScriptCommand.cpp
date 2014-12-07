#include "ScriptCommand.h"

CScriptCommand::CScriptCommand() : m_bLife(true)
{
}
CScriptCommand::~CScriptCommand()
{
}

const bool CScriptCommand::BeLife() const
{
	return m_bLife ;
}