// KeyboardLed.cpp: CKeyboardLed クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vis_tmsLED.h"
#include "KeyboardLed.h"

#include <winioctl.h>
#include <ntddkbd.h>
#include <conio.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CKeyboardLed::CKeyboardLed()
{
	m_device = NULL;
}

CKeyboardLed::~CKeyboardLed()
{
	//LED状態を復元
	bool bCapsLock = GetKeyState(VK_CAPITAL) & 0x01;
	bool bNumLock = GetKeyState(VK_NUMLOCK) & 0x01;
	bool bScrollLock = GetKeyState(VK_SCROLL) & 0x01;
	SetState((bCapsLock?KEYBOARD_CAPS_LOCK_ON:0) |
			(bNumLock?KEYBOARD_NUM_LOCK_ON:0) |
			(bScrollLock?KEYBOARD_SCROLL_LOCK_ON:0)
			);
	if(m_device)
	{
		CloseKeybordDevice(m_device);
	}
}

bool CKeyboardLed::Init(DWORD devId)
{
	if(m_device)
	{
		CloseKeybordDevice(m_device);
	}
	if(!OpenKeybordDevice(devId))
	{
		return false;
	}
	return true;
}

void errMessageBox(HWND hWnd,DWORD dwErrorCode,char *mes)
{
	LPSTR lpBuffer;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			dwErrorCode,
			0,
			(LPTSTR )&lpBuffer,
			0,
			NULL );
	MessageBox(hWnd,lpBuffer,mes,MB_APPLMODAL | MB_ICONSTOP);
	LocalFree(lpBuffer);
	return;
}


bool CKeyboardLed::SetState(WORD flag)
{
	ULONG retLen;

	if(IsWinNT())
	{
   		if(!m_device)
		{
			return false;
		}
		KEYBOARD_INDICATOR_PARAMETERS param;
		memset(&param,0,sizeof(param));
		param.UnitId = 0;
		param.LedFlags = flag;
		if(!DeviceIoControl(m_device,IOCTL_KEYBOARD_SET_INDICATORS,
						&param,sizeof(param),
						NULL,0,
						&retLen,NULL))
		{
			return false;
		}
	}
	else
	{
		_outp(0x60,0xed);
		_outp(0x60,flag & 0x07);	//よけいなビットを1にするとOSがとても重くなる
	}

	return true;
}

bool CKeyboardLed::OpenKeybordDevice(DWORD devId)
{
	if(IsWinNT())
	{
		CString strTmp;
		strTmp.Format("\\Device\\KeyboardClass%d",devId);
		if(!DefineDosDevice(DDD_RAW_TARGET_PATH,"tmsKbd",strTmp))
		{
			return false;
		}
		HANDLE hDevice = CreateFile("\\\\.\\tmsKbd",0,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
		if(hDevice == INVALID_HANDLE_VALUE)
		{
			DefineDosDevice(DDD_REMOVE_DEFINITION,"tmsKbd",NULL);
			return false;
		}
		m_device = hDevice;
	}

	return true;
}

bool CKeyboardLed::CloseKeybordDevice(HANDLE hDevice)
{
	if(IsWinNT())
	{
		DefineDosDevice(DDD_REMOVE_DEFINITION,"tmsKbd",NULL);
	}
	if(!CloseHandle(hDevice))
	{
		return false;
	}

    return true;
}

