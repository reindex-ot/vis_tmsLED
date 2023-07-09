// VisLED.cpp: CVisLED クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vis_tmsled.h"
#include "VisLED.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CVisLED::CVisLED()
{
	m_bEnable = false;
}

CVisLED::~CVisLED()
{

}

bool CVisLED::init(struct winampVisModule *this_mod)
{
	loadIni(this_mod);		
	if(!m_kbd.Init(m_iLedDevId))
	{
		return 1;
	}
	m_bEnable = true;

	m_iLedLevel1 = 0;
	m_iLedLevel2 = 0;
	m_iLedLevel3 = 0;
	if(m_bNumLock0)
	{
		m_iLedLevel0 |= KEYBOARD_NUM_LOCK_ON;
	}
	if(m_bNumLock1)
	{
		m_iLedLevel1 |= KEYBOARD_NUM_LOCK_ON;
	}
	if(m_bNumLock2)
	{
		m_iLedLevel2 |= KEYBOARD_NUM_LOCK_ON;
	}
	if(m_bNumLock3)
	{
		m_iLedLevel3 |= KEYBOARD_NUM_LOCK_ON;
	}
	if(m_bCapsLock0)
	{
		m_iLedLevel0 |= KEYBOARD_CAPS_LOCK_ON;
	}
	if(m_bCapsLock1)
	{
		m_iLedLevel1 |= KEYBOARD_CAPS_LOCK_ON;
	}
	if(m_bCapsLock2)
	{
		m_iLedLevel2 |= KEYBOARD_CAPS_LOCK_ON;
	}
	if(m_bCapsLock3)
	{
		m_iLedLevel3 |= KEYBOARD_CAPS_LOCK_ON;
	}
	if(m_bScrollLock0)
	{
		m_iLedLevel0 |= KEYBOARD_SCROLL_LOCK_ON;
	}
	if(m_bScrollLock1)
	{
		m_iLedLevel1 |= KEYBOARD_SCROLL_LOCK_ON;
	}
	if(m_bScrollLock2)
	{
		m_iLedLevel2 |= KEYBOARD_SCROLL_LOCK_ON;
	}
	if(m_bScrollLock3)
	{
		m_iLedLevel3 |= KEYBOARD_SCROLL_LOCK_ON;
	}

	return true;
}

int CVisLED::render(struct winampVisModule *this_mod,int levelL,int levelR)
{
	int total = (levelL>levelR)?levelL:levelR;
	if(total > 100)
	{
		m_kbd.SetState(m_iLedLevel3);
	}
	else if(total > 70)
	{
		m_kbd.SetState(m_iLedLevel2);
	}
	else if(total > 25)
	{
		m_kbd.SetState(m_iLedLevel1);
	}
	else
	{
		m_kbd.SetState(m_iLedLevel0);
	}
	if(m_bEnable)
	{
		return 0;
	}

	return 0;
}

int CVisLED::quit(struct winampVisModule *this_mod)
{
	m_bEnable = false;

	return 0;
}

void CVisLED::setLedDevId(int id)
{
	m_iLedDevId = id;
}

void CVisLED::loadIni(struct winampVisModule *this_mod)
{
	char ini[MAX_PATH];
	config_getinifn(this_mod,ini);

	m_iLedDevId = ::GetPrivateProfileInt("tmsLED","DevId",0,ini);
	m_bNumLock0 = ::GetPrivateProfileInt("tmsLED","bNumLock0",0,ini);
	m_bNumLock1 = ::GetPrivateProfileInt("tmsLED","bNumLock1",1,ini);
	m_bNumLock2 = ::GetPrivateProfileInt("tmsLED","bNumLock2",1,ini);
	m_bNumLock3 = ::GetPrivateProfileInt("tmsLED","bNumLock3",1,ini);
	m_bCapsLock0 = ::GetPrivateProfileInt("tmsLED","bCapsLock0",0,ini);
	m_bCapsLock1 = ::GetPrivateProfileInt("tmsLED","bCapsLock1",0,ini);
	m_bCapsLock2 = ::GetPrivateProfileInt("tmsLED","bCapsLock2",1,ini);
	m_bCapsLock3 = ::GetPrivateProfileInt("tmsLED","bCapsLock3",1,ini);
	m_bScrollLock0 = ::GetPrivateProfileInt("tmsLED","bScrollLock0",0,ini);
	m_bScrollLock1 = ::GetPrivateProfileInt("tmsLED","bScrollLock1",0,ini);
	m_bScrollLock2 = ::GetPrivateProfileInt("tmsLED","bScrollLock2",0,ini);
	m_bScrollLock3 = ::GetPrivateProfileInt("tmsLED","bScrollLock3",1,ini);

}

void CVisLED::saveIni(struct winampVisModule *this_mod)
{
	char ini[MAX_PATH];
	CString str;
	config_getinifn(this_mod,ini);
	str.Format("%ld",m_iLedDevId);
	::WritePrivateProfileString("tmsLED","DevId",str,ini);
	
	str.Format("%ld",m_bNumLock0);
	::WritePrivateProfileString("tmsLED","bNumLock0",str,ini);
	str.Format("%ld",m_bNumLock1);
	::WritePrivateProfileString("tmsLED","bNumLock1",str,ini);
	str.Format("%ld",m_bNumLock2);
	::WritePrivateProfileString("tmsLED","bNumLock2",str,ini);
	str.Format("%ld",m_bNumLock3);
	::WritePrivateProfileString("tmsLED","bNumLock3",str,ini);
	str.Format("%ld",m_bCapsLock0);
	::WritePrivateProfileString("tmsLED","bCapsLock0",str,ini);
	str.Format("%ld",m_bCapsLock1);
	::WritePrivateProfileString("tmsLED","bCapsLock1",str,ini);
	str.Format("%ld",m_bCapsLock2);
	::WritePrivateProfileString("tmsLED","bCapsLock2",str,ini);
	str.Format("%ld",m_bCapsLock3);
	::WritePrivateProfileString("tmsLED","bCapsLock3",str,ini);
	str.Format("%ld",m_bScrollLock0);
	::WritePrivateProfileString("tmsLED","bScrollLock0",str,ini);
	str.Format("%ld",m_bScrollLock1);
	::WritePrivateProfileString("tmsLED","bScrollLock1",str,ini);
	str.Format("%ld",m_bScrollLock2);
	::WritePrivateProfileString("tmsLED","bScrollLock2",str,ini);
	str.Format("%ld",m_bScrollLock3);
	::WritePrivateProfileString("tmsLED","bScrollLock3",str,ini);
}

