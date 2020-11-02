/*============================================================

windowsの表示[main.cpp]                            Author:Kai Yamaya
                                                   Date:2020/5/18
-------------------------------------------------------
												  
==============================================================
*/

//#define _CRT_SECURE_NO_WARNINGS
#include "DX98Set-up.h"
#include <Windows.h>
#include <d3d9.h>
#include<d3d9.h>
#include "mouse.h"
#include <stdio.h>//プロジェクトのプロパティーのVC++ディレクトリにある奴が<>になってる
#include "debugPrintf.h"//んでっこれは同ディレクトリファイル内の奴
#include <d3dx9.h>//Ｖｅｃｔｏｒとか入っているがDX11には入ってないが、11は外部から持っていくような感じ
#include"Config.h"
#include "MyDirect3D.h"
#include <stdio.h>
#include "Game.h"
#include "Debug_Font.h"
#include "DebugPrimitiv.h"
#include "system_timer.h"
#include "Sprite.h"
#include "keyboard.h"
#include "TexMan.h"
#include "KeyLoggerr.h"
//定数定義
#define CLASS_NAME  "GameWindow"//ウィンドウクラスの名前
#define WINDOW_CAPTION "Game"//ウィンドウの名前

//プロトタイプ宣言
//ウィンドウプロシージャ(コールバック関数)
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPraam);
//ゲーム初期化
//戻り値、初期化に失敗した時false
static bool INitialize(HWND hw);
//ゲーム更新
static void Update(void);
//ゲーム描画関数
static void Draw(void);
//ゲーム終了
static void Finalize(void);
////グローバル変数宣言
//static LPDIRECT3D9 g_pD3D =NULL;//Direct3Dインタフェース
//static LPDIRECT3DDEVICE9 g_pDevice = NULL;//Direct3Dデバイスインタフェース

static float f = 0;
//構造体宣言
static int g_FrameCount = 0;
static int g_BaseFrame = 0;
static double g_BaseTime = 0;
static double g_FPS = 0;
static double g_ReservaeTime = 0.0;

//頂点構造体
typedef struct Vertex2D_tag
{
	D3DXVECTOR4 Position;
	D3DCOLOR Collar;
	D3DXVECTOR2 TexCoord;
}Vertex2D;
#define FVF_VERTEX3D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
//座標変換済み頂点 RHW =1
//↑のVertex2D_tagと対の数になってないとダメ
//FVFとはフレキシブルヴァーテックスフォーマットの略、Direct3dの仕様　
//今から渡す情報はどういうものですよって姉さんに伝える
//メイン
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ipCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);//使用しない一位変数
	UNREFERENCED_PARAMETER(ipCmdLine);
	//ウィンドウクラス構造体の設定//構造体の要素が増えたWNDCLASSEXというものがある
	WNDCLASS  wc = {};//オリジナルのウィンドウパーツを作る(一旦システムに登録してから呼び出す)
	//必ずWNDCLASSは hoge;では変な物も一緒に生成されるので hoge ={}を必ず使うこと
	//最低限必要なやつ//アイコンとかもここで登録できる
	wc.lpfnWndProc = WndProc;//ウィンドウプロシージャっていう関数の設定
	wc.lpszClassName = CLASS_NAME;//クラス名の設定//ぶっちゃけなんでもいい
	wc.hInstance = hInstance;//インスタントハンドルの設定//上のインスタンスハンドルを入れる
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//マウスカーソルを指定//
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);//ウィンドウのクライアント領域の背景色を指定
	//class登録//これやらないと使えないので注意
	RegisterClass(&wc);
	DWORD style = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX;//ダブルワード型32bit
	//^(xor(ビット下げ))の注意事項:左辺値の下げたいBitが確実に立っていることが条件
	//(もしわからなかったら逆に立っちゃう、そのためその時は&~を使うとおｋ
	// 都合のいいウィンドウサイズを算出
	//RECT Window_rect = { 0,0,SCREEN_WHIDTH ,SCREEN_HEIGHT }; //ウィンドウスに搭載された構造体でleft、Top、right,bottomというLONG型が入っている
	//AdjustWindowRect(&Window_rect, style, false);
	//
	//int window_width = Window_rect.right - Window_rect.left;//幅
	//int window_height = Window_rect.bottom - Window_rect.top;//高さ
	//実行結果は左に-8,下に-31下がって窓枠分膨張してちょうどいいようになる
	//表示するウインドウの場所を算出する
	//デバイス(システム)からモニタ解像度取得
	//プライマリモニターの解像度取得
	int window_width =GetSystemMetrics(SM_CXSCREEN);//幅
	int window_height = GetSystemMetrics(SM_CYSCREEN);//高さ
	
	//仮装画面の解像度取得//ディアルモニター用の
	int  virtual_desktop_width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int  virtual_desktop_height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	//仮装画面の左上端座標//ディアルモニター用の
	int  virtual_desktop_x = GetSystemMetrics(SM_XVIRTUALSCREEN);
	int  virtual_desktop_y = GetSystemMetrics(SM_XVIRTUALSCREEN);

	int winwow_x =virtual_desktop_x +max((virtual_desktop_width- window_width) / 2, 0);
	//max(x,y)はx,yのどちらか大きい値を出す
	int winwow_y = virtual_desktop_y + max((virtual_desktop_height - window_height) / 2, 0);
	//ただし万が一デスクトップよりウィンドウが大きい場合は左上に表示
//	int winwow_x = max((window_width - window_width) / 2, 0);
//	int winwow_y = max((window_height - window_height) / 2, 0);
	//デスクトップ(クライアント領域)のサイズ

	//APIを用いたデスクトップ幅高さ取得
	//デスクトップの短型を取得
	RECT Desktop_rect;
	GetWindowRect(GetDesktopWindow(), &Desktop_rect);
	//デスクトップの幅と高さを算出
	int desktop_whidth = Desktop_rect.right - Desktop_rect.left;
	int desktop_height = Desktop_rect.bottom - Desktop_rect.top;
	//ウィンドウ生成
	//!CreateWindow出戻ってくるのがHWND
	//そしてHWNDにはユニークなIDが帰ってくる！!(ポインタで
	HWND hWnd = CreateWindow(//CreateWindow関数//ファイルのドラックアンドドロップが出来るCreateWindowexというものがある
		CLASS_NAME,//ウィンドウクラス
		WINDOW_CAPTION,//ウィンドウテキスト//起動したときの左上の文字
		//普通に"hogehoge"でも出来る
		style,//ウィンドウスタイル(ビットフラグ)
		//^ (XOR)
		//サイズと位置
		CW_USEDEFAULT,//画面の一番左上からウィンドウ左上までの距離(x)
		CW_USEDEFAULT,//画面の一番左上からウィンドウ左上までの距離(y)
		//ただしx/y両方数字でなければ変になるので注意！！
		//CW_USEDEFAULTはOS任せって意味
		window_width,//画面サイズX//フレームも含んだサイズ
		window_height,//画面サイズY//フレームも含んだサイズ
		NULL,//親ウィンドウハンドル//ここに親を入れると親子関係となり
		//親ウィンドウを移動させると子ウィンドウも移動する
		NULL,//メニューハンドル//左上の方のファイル(F)とかその類
		hInstance,//インスタンスハンドル
		NULL//追加のアプリケーションデータ
		//なにその引数...ってときは基本的にNULLをいれときゃどーにかなる
	);
	if (hWnd == NULL)
	{//ウィンドウハンドルが何らかの理由で制作できなかった場合
		return 0;
	}

	//指定したウィンドウハンドルのウィンドウを指定の方法で表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);//ウィンドウの機能を更新

	g_ReservaeTime = g_BaseTime = SystemTimer_GetTime();
	g_FrameCount = g_BaseFrame = 0;
	g_FPS = 0.0;

	Mouse_Initialize(hWnd);
	//InitSound(hWnd);
	if (!INitialize(hWnd))//最初の方に回す方法もあるが、ユーザビリティ的にはウィンドウが速く
	//出たほうがありがたい
	{//メッセージボックスでゲームの初期化失敗したためアプリケーション終了する感じで

		MessageBox(NULL, "アプリケーション終了します", "ゲームの初期化が失敗したので", MB_OK);//OKを押されるまでプログラムがとまる
		return 0;//下のreturnさえさせずにそのまま殺す
		
	}
#if defined(_DEBUG) || defined(DEBUG)
	
	//DebugPrimitiv_Init();
#endif
	//MyDirect3D_initialize(hWnd);
	//ウィンドウメッセージの取得(メッセージループ)
	MSG msg = {};
	//ゲームループ...にしたいが、GetMessageはメッセージが来ないと駄目なscanfなので....
	//PeekMessageというメッセージが来なくても進行するものを使うべし！
	//while (GetMessage(&msg, NULL, 0, 0))
//ゲーム初期化
	//DX９のﾌﾟﾛｼﾞｪｸﾄを作りなおす時が多々あり、
	//その時用メモ
	//プロジェクトのプロパティ//構成は全ての構成、すべてのプラットフォーム
	//を選択
	//VC++ディレクトリのインクルードディレクトリ
	//親または子の規定値から継承にチェックが入ってる
	//ことを確認し$(DXSDK_DIR)includeと入力する
	//すべてのプラットフォームやめてwin32を選択
	//ライブラリディレクトリlibのx86をえらんで$(DXSDK_DIR)lib|x86
	//んでwin32からx64に変更、リンカの全般の方でもおｋ
	//外部のライブラリを使うときはソースコードに書く方法と
	//プロパティに書く方法構成をdebug、プラットフォームをすべてのプラットフォームに、リンカの入力の追加の依存ファイルを選択して、
	//d3d9.lib
	//d3dx9d.lib
	//んでreleaseを選んで追加の依存ファイル、で
	//d3d9.lib
	//d3dx9.lib
//戻り値、初期化に失敗した時false

	while (WM_QUIT != msg.message)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			// messageがある場合はメッセージ処理を実行
			TranslateMessage(&msg);
			DispatchMessage(&msg);//メッセージが呼ばれると↓のWndProcが呼ばれる
			int test;
		}
		else
		{//ここにゲーム本編
			/*
			double Time= SystemTimer_GetTime();
			if ((Time + -g_ReservaeTime) < 1.0f / 60.0f)
			{
				Sleep(0);
				continue;
			}
			g_ReservaeTime = Time;
			*/
			//ゲーム更新
			  Update();
			//ゲーム描画関数
			  Draw();
		}
	}
	Finalize();
	return (int)msg.wParam;

}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPraam)
{//フックという

	switch (uMsg)
	{



	case WM_ACTIVATEAPP:
		if (wParam == VK_ESCAPE)//エスケープキーが押されった場合
		{
			SendMessage(hwnd, WM_CLOSE, 0, 0);//WM_CLOSEメッセージの送信
			UpdateWindow(hwnd);
		}
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		Mouse_ProcessMessage(uMsg, wParam, lPraam);
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard_ProcessMessage(uMsg, wParam, lPraam);
		break;
	}
	switch (uMsg)//たくさんのメッセージがここに飛んでくる
	{
	case WM_KEYDOWN:
		break;//ここのbreakはここのswitchを殺して下のreturnに回す

	case WM_CLOSE://Windowの×ボタン
		if (MessageBox(hwnd, "本当に終了してよろしいでしょうか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
		{
			DestroyWindow(hwnd);//hwndを破棄
		}
		return 0;//下のreturnさえさせずにそのまま殺す
		
	case WM_DESTROY://ウィンドウ破棄メッセージ
		PostQuitMessage(0);//WM_QUITメッセージの送信//なぜこいつがあるかといえば誤操作防止
		return 0;;
	}

	//だが１個１個やるのはめんどいので上以外の通常メッセージ処理はこの関数に任せる
	//良きに計らってくれる、子の場合上にある奴を消して終了処理してもタスク上は終わらないので
	//最低でも終了処理は↑に書いておくこと
	return DefWindowProc(hwnd, uMsg, wParam, lPraam);
}
//ゲーム初期化
//戻り値、初期化に失敗した時false
bool INitialize(HWND hw)
{
	Keyboard_Initialize();
	KeyLogger_initialize();

	SpriteInitialize();
	Texture_initialize();
	if (!MyDirect3D_initialize(hw))
	{
		MessageBox(NULL, "アプリケーション終了します", "D3Dの初期化に失敗しましたので", MB_OK);//OKを押されるまでプログラムがとまる
     return 0;
	}
	Game_initialize(0);
	//DebugFont_initialize();
	SystemTimer_Initialize();
	DX98Initialize();

	return 1;
}


//ゲーム更新
void Update(void)
{
	KeyLogger_Update();
	Game_Update();
	//計測
	double time = SystemTimer_GetTime();
		if (time - g_BaseTime > 1.0)
		{
			g_FPS = (g_FrameCount - g_BaseFrame) / (time - g_BaseTime);
			g_BaseTime = time;
			g_BaseFrame = g_FrameCount;
		}
		g_FrameCount++;
}
//ゲーム描画関数
void Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	if (!pDevice)
	{
		return;
	}
	
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 200, 255), 1.0f, 0);//背景色
	pDevice->BeginScene();
//	DebugPrimitiv_BatchBegin();
	Game_Draw();
//
	char buf[64];
	sprintf(buf, "FPS =%.2f", g_FPS);
	//DebugFont_Draw(0.0f, 0.0f, buf,1);

	//DebugPrimitiv_BatchRun();
	pDevice->EndScene();
	pDevice->Present(NULL, NULL, NULL, NULL);

}//ゲーム終了
void Finalize(void)
{

//	DebugPrimitiv_Finalize();
	KeyLogger_Finalize();
	SpriteFinalaise();
	//DebugFont_finalize();
	//お片付けのしかた:テク姉はデバ姉に教えてもらってきてる、テクスチャいらないなってなったらテク姉はバイバイしないといけない
	Game_Finalize();
	MyDirect3D_Finalize();
}