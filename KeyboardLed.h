// KeyboardLed.h: CKeyboardLed クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYBOARDLED_H__B642CBD8_7AF4_4332_B556_3280AFF977ED__INCLUDED_)
#define AFX_KEYBOARDLED_H__B642CBD8_7AF4_4332_B556_3280AFF977ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define KEYBOARD_KANA_LOCK_ON     8
#define KEYBOARD_CAPS_LOCK_ON     4
#define KEYBOARD_NUM_LOCK_ON      2
#define KEYBOARD_SCROLL_LOCK_ON   1

class CKeyboardLed  
{
public:
	CKeyboardLed();
	virtual ~CKeyboardLed();

	bool Init(DWORD devId);
	bool SetState(WORD flag);

private:
	HANDLE m_device;
	bool OpenKeybordDevice(DWORD devId);
	bool CloseKeybordDevice(HANDLE hDevice);
};

#endif // !defined(AFX_KEYBOARDLED_H__B642CBD8_7AF4_4332_B556_3280AFF977ED__INCLUDED_)
