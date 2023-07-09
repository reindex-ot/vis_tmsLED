# Winamp Visualization Plug-in - tmsLED
キーボードLEDとシステムトレイを利用したWinamp用のレベルメータープラグインです。

## レベルメーターの表示
以下の2種類のレベルメーターを表示できます。
- Windowsのシステムトレイに常駐するアナログVUメーター
- キーボードのLED(CapsLock/NumLock/ScrollLock)をレベルメーターのように点灯

## 使用方法
Winampがインストールされているフォルダーの下のPluginsフォルダーに、同梱の
配布ファイル「vis_tmsLED.dll」を解凍した後、preferences の plug-ins で
vis_tmsLED を選択してください。Auto execute on play にチェックをつけると
インストール後に、preferences の plug-ins で vis_tmsLED を選択してください。
Auto execute on play にチェックをつけると演奏開始と同時に作動します。
Configure ボタンを押すと、設定プロパティが表示されます。

## 動作環境での注意事項
ハードウェアの仕様により、テンキー機能がQWERTY部分に(NUM切り替えで)割り当てられているノートPCや、省スペースキーボードでは正常に機能しない可能性があります。

## スキン(vis_tmsLED.bmp/vis_tmsLED.ini)について
vis_tmsLED.bmpとvis_tmsLED.iniを変更することでVU計のデザインを変更できます。
詳しくはvis_tmsLED.iniを参照してください。

変更したファイルは使用中のSkinに含めるか、プラグインフォルダーに入れてください。

## このソースとバイナリについて
Win32工作小屋のT-Matsuo様が公開していたのですが、いつの間にか閉鎖されておりソースもない状態となっていた為ソースとバイナリと共にミラーという形にしています。

Winampの開発も再開し始めたのでこのプラグインを使いたい、Mod版をビルドしたいと思う方は有効利用してください。
