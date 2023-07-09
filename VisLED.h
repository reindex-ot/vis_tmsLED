// VisLED.h: CVisLED クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISLED_H__FE7266AD_3F10_4FC4_8FE9_BD9A3E2CEB11__INCLUDED_)
#define AFX_VISLED_H__FE7266AD_3F10_4FC4_8FE9_BD9A3E2CEB11__INCLUDED_

#include "VIS.H"
#include "KeyboardLed.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVisLED  
{
public:
	CVisLED();
	virtual ~CVisLED();
	bool init(struct winampVisModule *this_mod);
	int render(struct winampVisModule *this_mod,int levelL,int levelR);
	int quit(struct winampVisModule *this_mod);

	int getLedDevId(){return m_iLedDevId;};
	void setLedDevId(int id);
	void loadIni(struct winampVisModule *this_mod);
	void saveIni(struct winampVisModule *this_mod);

	BOOL m_bNumLock0;
	BOOL m_bNumLock1;
	BOOL m_bNumLock2;
	BOOL m_bNumLock3;
	BOOL m_bCapsLock0;
	BOOL m_bCapsLock1;
	BOOL m_bCapsLock2;
	BOOL m_bCapsLock3;
	BOOL m_bScrollLock0;
	BOOL m_bScrollLock1;
	BOOL m_bScrollLock2;
	BOOL m_bScrollLock3;

private:
	bool m_bEnable;

	int m_iLedLevel0;
	int m_iLedLevel1;
	int m_iLedLevel2;
	int m_iLedLevel3;
	int m_iLedDevId;
	CKeyboardLed m_kbd;
};

#endif // !defined(AFX_VISLED_H__FE7266AD_3F10_4FC4_8FE9_BD9A3E2CEB11__INCLUDED_)
