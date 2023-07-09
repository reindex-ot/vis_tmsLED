// vis_tmsLED.cpp : DLL 用の初期化処理の定義を行います。
//

#include "stdafx.h"
#include "vis_tmsLED.h"

#include "DlgConfig.h"
#include "VisLED.h"
#include "VisTray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	メモ!
//
//		この DLL が MFC DLL に対して動的にリンクされる場合、
//		MFC 内で呼び出されるこの DLL からエクスポートされた
//		どの関数も関数の最初に追加される AFX_MANAGE_STATE 
//		マクロを含んでいなければなりません。
//
//		例:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 通常関数の本体はこの位置にあります
//		}
//
//		このマクロが各関数に含まれていること、MFC 内の
//		どの呼び出しより優先することは非常に重要です。
//		これは関数内の最初のステートメントでなければな
//		らないことを意味します、コンストラクタが MFC 
//		DLL 内への呼び出しを行う可能性があるので、オブ
//		ジェクト変数の宣言よりも前でなければなりません。
//
//		詳細については MFC テクニカル ノート 33 および
//		58 を参照してください。
//

/////////////////////////////////////////////////////////////////////////////
// CVis_tmsLEDApp

BEGIN_MESSAGE_MAP(CVis_tmsLEDApp, CWinApp)
	//{{AFX_MSG_MAP(CVis_tmsLEDApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVis_tmsLEDApp の構築

CVis_tmsLEDApp::CVis_tmsLEDApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance の中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CVis_tmsLEDApp オブジェクト

CVis_tmsLEDApp theApp;

AFX_MANAGE_STATE(AfxGetStaticModuleState());

bool bActive = false;

CVisTray tray;
BOOL g_bTray;
CVisLED led;
BOOL g_bLed;

#ifdef __cplusplus
extern "C" {
#endif

winampVisModule *getModule(int which);
winampVisHeader hdr = {0x0101,"tmsLED v1.01",getModule};

void config(struct winampVisModule *this_mod);
int init(struct winampVisModule *this_mod);
int render1(struct winampVisModule *this_mod);
void quit(struct winampVisModule *this_mod);

void config_getinifn(struct winampVisModule *this_mod,char *ini_file);
bool IsWinNT();

winampVisModule mod1 =
{
	"LED/SystemTray Level Meter",
	NULL,	// hwndParent
	NULL,	// hDllInstance
	0,		// sRate
	0,		// nCh
	1,		// latencyMS
	50,		// delayMS(50)
	2,		// spectrumNch
	2,		// waveformNch
	{ 0, },	// spectrumData
	{ 0, },	// waveformData
	config,
	init,
	render1, 
	quit
};

__declspec( dllexport ) winampVisHeader *winampVisGetHeader()
{
	return &hdr;
}

winampVisModule *getModule(int which)
{
	switch(which)
	{
		case 0: return &mod1;
		default:return NULL;
	}
}

void config(struct winampVisModule *this_mod)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	char ini[MAX_PATH];
	CString str;
	config_getinifn(this_mod,ini);
	g_bLed = ::GetPrivateProfileInt("tmsLED","Led",1,ini);
	g_bTray = ::GetPrivateProfileInt("tmsLED","Tray",1,ini);
	led.loadIni(this_mod);

	CDlgConfig dlg;
	dlg.m_bLed = g_bLed;
	dlg.m_bTrayVU = g_bTray;
	if(IsWinNT())
	{
		dlg.m_strDevice.Format("\\Device\\KeyboardClass%d",led.getLedDevId());
	}
	dlg.m_bNumLock0 = led.m_bNumLock0;
	dlg.m_bNumLock1 = led.m_bNumLock1;
	dlg.m_bNumLock2 = led.m_bNumLock2;
	dlg.m_bNumLock3 = led.m_bNumLock3;
	dlg.m_bCapsLock0 = led.m_bCapsLock0;
	dlg.m_bCapsLock1 = led.m_bCapsLock1;
	dlg.m_bCapsLock2 = led.m_bCapsLock2;
	dlg.m_bCapsLock3 = led.m_bCapsLock3;
	dlg.m_bScrollLock0 = led.m_bScrollLock0;
	dlg.m_bScrollLock1 = led.m_bScrollLock1;
	dlg.m_bScrollLock2 = led.m_bScrollLock2;
	dlg.m_bScrollLock3 = led.m_bScrollLock3;
	if(dlg.DoModal() == IDOK)
	{
		g_bLed = dlg.m_bLed;
		str.Format("%ld",g_bLed);
		::WritePrivateProfileString("tmsLED","Led",str,ini);
		g_bTray = dlg.m_bTrayVU;
		str.Format("%ld",g_bTray);
		::WritePrivateProfileString("tmsLED","Tray",str,ini);

		CString str = dlg.m_strDevice;
		led.setLedDevId(0);
		if(str.GetLength() > 21)
		{
			led.setLedDevId(atoi(&((LPCSTR )str)[21]));
		}
		led.m_bNumLock0 = dlg.m_bNumLock0;
		led.m_bNumLock1 = dlg.m_bNumLock1;
		led.m_bNumLock2 = dlg.m_bNumLock2;
		led.m_bNumLock3 = dlg.m_bNumLock3;
		led.m_bCapsLock0 = dlg.m_bCapsLock0;
		led.m_bCapsLock1 = dlg.m_bCapsLock1;
		led.m_bCapsLock2 = dlg.m_bCapsLock2;
		led.m_bCapsLock3 = dlg.m_bCapsLock3;
		led.m_bScrollLock0 = dlg.m_bScrollLock0;
		led.m_bScrollLock1 = dlg.m_bScrollLock1;
		led.m_bScrollLock2 = dlg.m_bScrollLock2;
		led.m_bScrollLock3 = dlg.m_bScrollLock3;
		led.saveIni(this_mod);

		if(bActive)
		{
			quit(this_mod);
			init(this_mod);
		}
	}
}

int init(struct winampVisModule *this_mod)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	bActive = true;

	char ini[MAX_PATH];
	config_getinifn(this_mod,ini);

	g_bLed = ::GetPrivateProfileInt("tmsLED","Led",1,ini);
	if(g_bLed) led.init(this_mod);

	g_bTray = ::GetPrivateProfileInt("tmsLED","Tray",1,ini);
	if(g_bTray) tray.init(this_mod);

	return 0;
}

int render1(struct winampVisModule *this_mod)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	int total_L = 0;
	int total_R = 0;
	for(int x=1; x<576; x++)
	{
		if(total_L < (this_mod->waveformData[0][x]^128))
		{
			total_L = this_mod->waveformData[0][x]^128;
		}
		if(total_R < (this_mod->waveformData[1][x]^128))
		{
			total_R = this_mod->waveformData[1][x]^128;
		}
	}
	total_L -= 128;
	total_R -= 128;
	if(g_bLed) led.render(this_mod,total_L,total_R);
	if(g_bTray) tray.render(this_mod,total_L,total_R);

	return 0;
}

void quit(struct winampVisModule *this_mod)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	bActive = false;

	led.quit(this_mod);
	tray.quit(this_mod);
}

void config_getinifn(struct winampVisModule *this_mod,char *ini_file)
{
	::GetModuleFileName(this_mod->hDllInstance,ini_file,MAX_PATH);
	char *p = (char *)_mbsrchr((const unsigned char *)ini_file,'\\');
	if(p) *p = '\0';
	strcat(ini_file,"\\plugin.ini");
}

bool IsWinXP_Later()
{
	static bool bChecked = false;
	static bool bIsWinXP_Later = false;

	if(!bChecked)
	{
		OSVERSIONINFO osvi;
		memset(&osvi,0,sizeof(OSVERSIONINFO));
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&osvi);
		if(osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
		{
			if((osvi.dwMajorVersion >= 5) && (osvi.dwMinorVersion >= 1))
			{
				bIsWinXP_Later = true;
			}
		}
		bChecked = true;
	}

	return bIsWinXP_Later;
}

bool IsWinNT()
{
	static bool bChecked = false;
	static bool bIsWinNT = false;

	if(!bChecked)
	{
		OSVERSIONINFO osvi;
		memset(&osvi,0,sizeof(OSVERSIONINFO));
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&osvi);
		if(osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
		{
			bIsWinNT = true;
		}
		bChecked = true;
	}

	return bIsWinNT;
}

#ifdef __cplusplus
}
#endif

