#pragma once

enum Dialogist { NONE=0, GUEST, DRIVER } ;

class IDialog
{
protected :
	Dialogist m_Dialogist ;

public :
	IDialog() : m_Dialogist(NONE) {}
	virtual ~IDialog() {}

	virtual void SetAlpha(float fAlpha) = 0 ;

	const Dialogist GetDialogist() const { return m_Dialogist ; }

	virtual void Render() = 0 ;
} ;