#include "LoadManager.h"
#include <stdio.h>
#include <string>

LoadManager::LoadManager() : m_File(NULL)
{
}
LoadManager::~LoadManager()
{
}

const bool LoadManager::OpenDat(char *filepath)
{
	if(m_File!=NULL)
		return false ;

	m_File = fopen(filepath, "r") ;
	if(m_File==NULL)
		return false ;

	return true ;
}

const bool LoadManager::CloseDat()
{
	if(m_File==NULL)
		return false ;

	fclose(m_File) ;

	m_File = NULL ;

	return true ;
}

const bool LoadManager::GetItem(char *item)
{
	std::string data="" ;
	char key=NULL ;
	bool comment=false ;
	bool bracket=false ;

	while(1)
	{
		key = fgetc(m_File) ;
		if(key==EOF)
			break ;

		if(comment)
		{
			if(key==10)
				comment = false ;
		}
		else if(key=='#')
		{
			comment = true ;
		}
		else if(key==10 || key==' ')
		{
			continue ;
		}
		else
		{
			if(!bracket && key=='<')
			{
				bracket = true ;
			}
			else if(bracket)
			{
				if(key=='>')
					break ;

				if(key>='a' && key<='z')
					key -= 32 ;

				char temp[] = { key, NULL } ;
				data.append(temp) ;
			}
		}
	}

	if(key==EOF && data.empty())
		return false ;

	strcpy(item, data.c_str()) ;

	return true ;
}

const bool LoadManager::GetCommand(char *command)
{
	std::string data="" ;
	char key=NULL ;
	bool comment=false ;

	while(1)
	{
		key = fgetc(m_File) ;
		if(key==EOF)
			break ;

		if(comment)
		{
			if(key==10)
				comment = false ;
		}
		else if(key=='#')
		{
			comment = true ;
		}
		else if(key==10 || key==' ')
		{
			if(data=="")
				continue ;
			else
				break ;
		}
		else
		{
			if(key>='a' && key<='z')
				key -= 32 ;

			char temp[] = { key, NULL } ;
			data.append(temp) ;
		}
	}

	if(key==EOF && data.empty())
		return false ;

	strcpy(command, data.c_str()) ;

	return true ;
}

void LoadManager::GetString(char *str)
{
	std::string data="" ;
	char key=NULL ;
	bool blank=true ;
	bool quotation_mark=false ;

	while(1)
	{
		key = fgetc(m_File) ;
		if(key==EOF)
			break ;

		if(!quotation_mark && key=='\"')
		{
			quotation_mark = true ;
		}
		else if(quotation_mark && key!=10)
		{
			if(key=='\"')
				break ;

			char temp[] = { key, NULL } ;
			data.append(temp) ;
		}
	}

	/*while(1)
	{
		key = fgetc(m_File) ;
		if(key==EOF)
			break ;

		if(blank && (key!=10 && key!=' '))
			blank = false ;

		if(!blank)
		{
			if(key==10 || key==' ')
				break ;

			char temp[] = { key, NULL } ;
			data.append(temp) ;
		}
	}*/

	strcpy(str, data.c_str()) ;
}

void LoadManager::GetValue(int &value)
{
	std::string data="" ;
	char key=NULL ;
	bool blank=true ;

	while(1)
	{
		key = fgetc(m_File) ;
		if(key==EOF)
			break ;

		if(blank && (key!=10 && key!=' ' && key!=','))
			blank = false ;

		if(!blank)
		{
			if(key==10 || key==' ' || key==',')
				break ;

			if(!blank)
			{
				char temp[] = { key, NULL } ;
				data.append(temp) ;
			}
		}
	}

	value = atoi(data.c_str()) ;
}

void LoadManager::GetValue(float &value)
{
	std::string data="" ;
	char key=NULL ;
	bool blank=true ;

	while(1)
	{
		key = fgetc(m_File) ;
		if(key==EOF)
			break ;

		if(blank && (key!=10 && key!=' ' && key!=','))
			blank = false ;

		if(!blank)
		{
			if(key==10 || key==' ' || key==',')
				break ;

			if(!blank)
			{
				char temp[] = { key, NULL } ;
				data.append(temp) ;
			}
		}
	}

	value = (float)strtod(data.c_str(), NULL) ;
}