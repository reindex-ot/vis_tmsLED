// VisTray.h: CVisTray クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISTRAY_H__6E08F2D2_4D42_4858_8B20_92B06A492E86__INCLUDED_)
#define AFX_VISTRAY_H__6E08F2D2_4D42_4858_8B20_92B06A492E86__INCLUDED_

#include "SystemTray.h"
#include "VIS.H"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVisTray  
{
public:
	CVisTray();
	virtual ~CVisTray();
	void Release();
	bool init(struct winampVisModule *this_mod);
	int render(struct winampVisModule *this_mod,int levelL,int levelR);
	int quit(struct winampVisModule *this_mod);

	void setUseSkin(bool use){m_bUseSkin = use;};
	bool getUseSkin(){return m_bUseSkin;};

private:
	bool m_bEnable;
	bool m_bUseSkin;
	CSystemTray m_sysTrayVU_L;
	int m_VULevel_L;
	CSystemTray m_sysTrayVU_R;
	int m_VULevel_R;
	HICON m_hIconVU[2][15];

	//パーツ置き場
	HDC		m_hMemDcPt;
	HBITMAP	m_hMemBitmapPt;
	HDC		m_hOldBitmapPt;

};

#endif // !defined(AFX_VISTRAY_H__6E08F2D2_4D42_4858_8B20_92B06A492E86__INCLUDED_)
