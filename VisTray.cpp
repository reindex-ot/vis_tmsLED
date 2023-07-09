// VisTray.cpp: CVisTray クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vis_tmsled.h"
#include "VisTray.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CVisTray::CVisTray()
{
	memset(&m_hIconVU,0,sizeof(m_hIconVU));
	m_bEnable = false;
	m_bUseSkin = true;
}

CVisTray::~CVisTray()
{

}

void CVisTray::Release()
{
	for(int ch=0; ch<2; ch++)
	{
		for(int i=0; i<(sizeof(m_hIconVU)/(sizeof(m_hIconVU[ch][0])*2)); i++)
		{
			if(m_hIconVU[ch][i])
			{
				DestroyIcon(m_hIconVU[ch][i]);
				m_hIconVU[ch][i] = NULL;
			}
		}
	}
	m_sysTrayVU_L.RemoveIcon();
	m_sysTrayVU_R.RemoveIcon();
	m_bEnable = false;
}

bool CVisTray::init(struct winampVisModule *this_mod)
{
	int n_color_R = 0;	// 針の色
	int n_color_G = 0;	// 針の色
	int n_color_B = 0;	// 針の色
	int roll = 1;	//針の回転方向
	int cx = 7;//針の支点
	int cy = 10;
	double rr = 10.0;//半径
	double rad_width = 2.0;//針の振れ幅
	double rad_start = 1.0;//針の0基準
	
	Release();

	LPBITMAPINFO lpmBi = NULL;
	if(m_bUseSkin)
	{
		//
		//ビットマップリソースの読み込み
		//
		char szRcBmp[MAX_PATH] = "";
		HANDLE hFile = INVALID_HANDLE_VALUE;
		DWORD dwVer = SendMessage(this_mod->hwndParent,WM_WA_IPC,0,IPC_GETVERSION);
		//2.04 以前はSkin検出非対応
		if(dwVer >= 0x2004)
		{
			char *szSkinName = (char *)SendMessage(this_mod->hwndParent,WM_WA_IPC,(WPARAM)szRcBmp,IPC_GETSKIN);
			if(szSkinName && strlen(szSkinName))
			{
				strcat(szRcBmp,"\\vis_tmsLED.BMP");
				hFile = CreateFile(szRcBmp,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			}
		}
		//skin dir
		if(hFile == INVALID_HANDLE_VALUE)
		{
			char szWinampIni[MAX_PATH];
			HINSTANCE hinstWinamp = (HINSTANCE )GetWindowLong(this_mod->hwndParent,GWL_HINSTANCE);
			GetModuleFileName(hinstWinamp,szWinampIni,MAX_PATH);
			char *ptr = (char *)_mbsrchr((const unsigned char *)szWinampIni,'\\');
			if(ptr) *ptr = '\0';
			strcat(szWinampIni,"\\winamp.ini");
			GetPrivateProfileString("Winamp","SkinDir", "",szRcBmp,MAX_PATH,szWinampIni);
			if(szRcBmp[0] == '\0')
			{
				//デフォルトの SkinDir
				GetModuleFileName(hinstWinamp,szRcBmp,MAX_PATH);
				char *ptr = (char *)_mbsrchr((const unsigned char *)szRcBmp,'\\');
				if(ptr) *ptr = '\0';
				strcat(szRcBmp,"\\Skins");
			}
			strcat(szRcBmp,"\\vis_tmsLED.BMP");
			hFile = CreateFile(szRcBmp,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		}
		//dll dir
		if(hFile == INVALID_HANDLE_VALUE)
		{
			GetModuleFileName(this_mod->hDllInstance,szRcBmp,MAX_PATH);
			char *ptr = (char *)_mbsrchr((const unsigned char *)szRcBmp,'\\');
			if(ptr) *ptr = '\0';
			strcat(szRcBmp,"\\vis_tmsLED.BMP");
			hFile = CreateFile(szRcBmp,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		}

		if(hFile != INVALID_HANDLE_VALUE)
		{
			BITMAPFILEHEADER bmfileh;
			long size;
			DWORD dwRet;
			ReadFile(hFile,&bmfileh,sizeof(BITMAPFILEHEADER),&dwRet,NULL);
			if(bmfileh.bfType == 0x4d42)
			{
				size = bmfileh.bfSize - sizeof(BITMAPFILEHEADER);
				lpmBi = (LPBITMAPINFO )malloc(size);
				if(lpmBi)
				{
					ReadFile(hFile,lpmBi,size,&dwRet,NULL);
				}
			}
			CloseHandle(hFile);

			//パラメータの取得
			char szTmsLEDIni[MAX_PATH];
			strcpy(szTmsLEDIni,szRcBmp);
			char *ptr = (char *)_mbsrchr((const unsigned char *)szTmsLEDIni,'\\');
			if(ptr) *ptr = '\0';
			strcat(szTmsLEDIni,"\\vis_tmsLED.ini");
			
			char buf[256];
			//(回転方向)
			int tmp = GetPrivateProfileInt("tray","ROLL",-1,szTmsLEDIni);
			if(tmp != -1)
			{
				roll = tmp;
			}
			//(針の色)
			tmp = GetPrivateProfileInt("tray","NCOLOR16_R",-1,szTmsLEDIni);
			if(tmp != -1)
			{
				n_color_R = tmp;
			}
			tmp = GetPrivateProfileInt("tray","NCOLOR16_G",-1,szTmsLEDIni);
			if(tmp != -1)
			{
				n_color_G = tmp;
			}
			tmp = GetPrivateProfileInt("tray","NCOLOR16_B",-1,szTmsLEDIni);
			if(tmp != -1)
			{
				n_color_B = tmp;
			}
			//(針の支点)
			GetPrivateProfileString("tray","NCX","",buf,sizeof(buf),szTmsLEDIni);
			if(strlen(buf))
			{
				cx = atoi(buf);
			}
			GetPrivateProfileString("tray","NCY","",buf,sizeof(buf),szTmsLEDIni);
			if(strlen(buf))
			{
				cy = atoi(buf);
			}
			//(半径)
			GetPrivateProfileString("tray","NLEN","",buf,sizeof(buf),szTmsLEDIni);
			if(strlen(buf))
			{
				rr = atof(buf);
			}
			//(針の振れ幅)
			GetPrivateProfileString("tray","NRAD_WIDTH","",buf,sizeof(buf),szTmsLEDIni);
			if(strlen(buf))
			{
				rad_width = atof(buf);
			}
			//(針の0基準位置)
			GetPrivateProfileString("tray","NRAD_START","",buf,sizeof(buf),szTmsLEDIni);
			if(strlen(buf))
			{
				rad_start = atof(buf);
			}
		}
	}

	//
	//ICONの生成
	//
	LPBITMAPINFO lpBi;
	if(lpmBi)
	{
		lpBi = lpmBi;
	}
	else
	{
		//ビットマップリソースをメモリに展開
		HGLOBAL hRes = LoadResource(this_mod->hDllInstance,FindResource(this_mod->hDllInstance,MAKEINTRESOURCE(IDB_BITMAP_TRAY_VU),RT_BITMAP));
		lpBi = (LPBITMAPINFO )LockResource(hRes);
		if(!lpBi)
		{
			return false;
		}
	}
	//色数を取得
	int nColorData;
	if(lpBi->bmiHeader.biClrUsed != 0)
	{
		nColorData = lpBi->bmiHeader.biClrUsed;
	}
	else
	{
		switch(lpBi->bmiHeader.biBitCount)
		{
			case 1  : nColorData = 2;	break; // モノクロ
			case 4  : nColorData = 16;  break; // VGA
			case 8  : nColorData = 256; break; // SVGA
			case 24 : nColorData = 0;	break; // True Color
		}
	}
	HDC hdc = GetDC(NULL);
	HDC		hMemDcTmp		= CreateCompatibleDC(hdc);
	HBITMAP hMemBitmapTmp	= CreateCompatibleBitmap(hdc,16,16);
	HDC		hMemDcPt1		= CreateCompatibleDC(hdc);
	HBITMAP hMemBitmapPt1	= CreateCompatibleBitmap(hdc,32,32);
	HDC		hMemDcPt2		= CreateCompatibleDC(hdc);
	HBITMAP hMemBitmapPt2	= CreateCompatibleBitmap(hdc,32,32);
	ReleaseDC(NULL,hdc);

	LPTSTR		lpBits=NULL;
	// ビットマップデータの場所を取得する。
	//........................
	lpBits =  (LPSTR)lpBi;
	lpBits += lpBi->bmiHeader.biSize + (nColorData*sizeof(RGBQUAD));

	int penWidth = 1;
	HPEN hPen = CreatePen(PS_SOLID,penWidth,RGB(n_color_R,n_color_G,n_color_B));
	HPEN OldPen = (HPEN )SelectObject(hMemDcTmp,hPen);
	HBITMAP OldBitmapTmp = (HBITMAP )SelectObject(hMemDcTmp,hMemBitmapTmp);
	for(int ch=0; ch<2; ch++)
	{
		for(int i=0; i<(sizeof(m_hIconVU)/(sizeof(m_hIconVU[ch][0])*2)); i++)
		{
			HBITMAP OldBitmapPt1 = (HBITMAP )SelectObject(hMemDcPt1,hMemBitmapPt1);
			HBITMAP OldBitmapPt2 = (HBITMAP )SelectObject(hMemDcPt2,hMemBitmapPt2);
			
			//マスク画像(C)
			SetDIBitsToDevice(hMemDcTmp,0,0,					//転送先長方形の左上隅の xy 座標
								16,16,							//転送元長方形の幅高さ
								0, lpBi->bmiHeader.biHeight-32-ch*32,	//転送元長方形の左下隅の xy 座標(左下が0,0)
								0, lpBi->bmiHeader.biHeight,	//配列内の最初の走査行,走査行の数
								lpBits,lpBi,DIB_RGB_COLORS);
			//(->拡大展開)
			StretchBlt(hMemDcPt1,0,0,32,32,hMemDcTmp,0,0,16,16,SRCCOPY);
			
			//本体(1回目)(A)
			SetDIBitsToDevice(hMemDcTmp,0,0,					//転送先長方形の左上隅の xy 座標
								16,16,							//転送元長方形の幅高さ
								0, lpBi->bmiHeader.biHeight-16-ch*32,	//転送元長方形の左下隅の xy 座標(左下が0,0)
								0, lpBi->bmiHeader.biHeight,	//配列内の最初の走査行,走査行の数
								lpBits,lpBi,DIB_RGB_COLORS);
			//針を描画
			double mv = rad_width / 15 * (double )i;
			int sx = (int )(cx+rr*sin((mv-rad_start)*(roll?1:-1)));
			int sy = (int )(cy-rr*cos((mv-rad_start)*(roll?1:-1)));
 			MoveToEx(hMemDcTmp,cx,cy,NULL);
			LineTo(hMemDcTmp,sx,sy);
			//(->拡大展開)
			StretchBlt(hMemDcPt2,0,0,32,32,hMemDcTmp,0,0,16,16,SRCCOPY);
			//本体(針の根本を隠すマスク)(D)
			SetDIBitsToDevice(hMemDcTmp,0,0,					//転送先長方形の左上隅の xy 座標
								16,16,							//転送元長方形の幅高さ
								16, lpBi->bmiHeader.biHeight-32-ch*32,	//転送元長方形の左下隅の xy 座標(左下が0,0)
								0, lpBi->bmiHeader.biHeight,	//配列内の最初の走査行,走査行の数
								lpBits,lpBi,DIB_RGB_COLORS);
			//(->拡大展開)
			StretchBlt(hMemDcPt2,0,0,32,32,hMemDcTmp,0,0,16,16,SRCAND);
			//本体(2回目の描画)(B)
			SetDIBitsToDevice(hMemDcTmp,0,0,					//転送先長方形の左上隅の xy 座標
								16,16,							//転送元長方形の幅高さ
								16, lpBi->bmiHeader.biHeight-16-ch*32,	//転送元長方形の左下隅の xy 座標(左下が0,0)
								0, lpBi->bmiHeader.biHeight,	//配列内の最初の走査行,走査行の数
								lpBits,lpBi,DIB_RGB_COLORS);
			//(->拡大展開)
			StretchBlt(hMemDcPt2,0,0,32,32,hMemDcTmp,0,0,16,16,SRCINVERT);
			
			SelectObject(hMemDcPt1,OldBitmapPt1);
			SelectObject(hMemDcPt2,OldBitmapPt2);

			ICONINFO icon;
			memset(&icon,0,sizeof(icon));
			icon.fIcon = TRUE;
			icon.hbmMask = hMemBitmapPt1;
			icon.hbmColor = hMemBitmapPt2;
			m_hIconVU[ch][i] = CreateIconIndirect(&icon);
		}
	}
	SelectObject(hMemDcPt2,OldPen);
	DeleteObject(hPen);
	
	SelectObject(hMemDcTmp,OldBitmapTmp);
	DeleteDC(hMemDcTmp);
	DeleteObject(hMemBitmapTmp);
	DeleteDC(hMemDcPt1);
	DeleteObject(hMemBitmapPt1);
	DeleteDC(hMemDcPt2);
	DeleteObject(hMemBitmapPt2);
	
	m_VULevel_L = 0;
	m_VULevel_R = 0;
	
	m_sysTrayVU_L.Create(this_mod->hDllInstance);
	m_sysTrayVU_R.Create(this_mod->hDllInstance);
	if(IsWinXP_Later())
	{
		m_sysTrayVU_R.Init("tmsLED Rch",m_hIconVU[1][0],1);
		m_sysTrayVU_L.Init("tmsLED Lch",m_hIconVU[0][0],0);
	}
	else
	{
		m_sysTrayVU_L.Init("tmsLED Lch",m_hIconVU[0][0],0);
		m_sysTrayVU_R.Init("tmsLED Rch",m_hIconVU[1][0],1);
	}
	m_bEnable = true;

	if(lpmBi)
	{
		free(lpmBi);
	}
	return true;
}

int CVisTray::render(struct winampVisModule *this_mod,int total_L,int total_R)
{
	if(!m_bEnable)
	{
		return 0;
	}

	total_L *= 100;
	total_R *= 100;

#define GEN_L	500
#define UP_L	500
	//緩衝
	if(m_VULevel_L < total_L)
	{
		m_VULevel_L += UP_L;
		if(m_VULevel_L > total_L)
		{
			m_VULevel_L = total_L;
		}
	}
	else if(m_VULevel_L != total_L)
	{
		m_VULevel_L -= GEN_L;
		if(m_VULevel_L < 0)
		{
			m_VULevel_L = 0;
		}
	}
	if(m_VULevel_R < total_R)
	{
		m_VULevel_R += UP_L;
		if(m_VULevel_R > total_R)
		{
			m_VULevel_R = total_R;
		}
	}
	else if(m_VULevel_R != total_R)
	{
		m_VULevel_R -= GEN_L;
		if(m_VULevel_R < 0)
		{
			m_VULevel_R = 0;
		}
	}

	//[Lチャネル]
	total_L = (int )((double )m_VULevel_L / (12800.0 / 15.0));
	if(total_L > 15)
	{
		total_L = 15;
	}
	m_sysTrayVU_L.SetIcon(m_hIconVU[0][total_L]);

	//[Rチャネル]
	total_R = (int )((double )m_VULevel_R / (12800.0 / 15.0));
	if(total_R > 15)
	{
		total_R = 15;
	}
	m_sysTrayVU_R.SetIcon(m_hIconVU[1][total_R]);

	return 0;
}

int CVisTray::quit(struct winampVisModule *this_mod)
{
	Release();

	return 0;
}
