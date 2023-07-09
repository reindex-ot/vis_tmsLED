// vis_tmsLED.h : VIS_TMSLED アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_VIS_TMSLED_H__4A933F35_4FC9_475E_BBC7_77CF12D42E7F__INCLUDED_)
#define AFX_VIS_TMSLED_H__4A933F35_4FC9_475E_BBC7_77CF12D42E7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル
#include "VIS.H"
#include "Frontend.h"

#ifdef __cplusplus
extern "C" {
#endif

bool IsWinXP_Later();

#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CVis_tmsLEDApp
// このクラスの動作の定義に関しては vis_tmsLED.cpp ファイルを参照してください。
//

class CVis_tmsLEDApp : public CWinApp
{
public:
	CVis_tmsLEDApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CVis_tmsLEDApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CVis_tmsLEDApp)
		// メモ -  ClassWizard はこの位置にメンバ関数を追加または削除します。
		//         この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_VIS_TMSLED_H__4A933F35_4FC9_475E_BBC7_77CF12D42E7F__INCLUDED_)
