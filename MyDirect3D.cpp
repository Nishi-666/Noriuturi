
#include <Windows.h>
#include <d3d9.h>
#include <d3d9.h>
#include "Config.h"
//#include <d3dx9.h>//Ｖｅｃｔｏｒとか入っているがDX11には入ってないが、11は外部から持っていくような感じ

//グローバル変数宣言
static LPDIRECT3D9 g_pD3D = NULL;//Direct3Dインタフェース
static LPDIRECT3DDEVICE9 g_pDevice = NULL;//Direct3Dデバイスインタフェース
//関数定義



//Direct3D9の初期化、失敗時はfalseを投下
bool MyDirect3D_initialize(HWND hw)
{

	//Direct3Dインタフェースの取得
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{

		MessageBox(NULL, "アプリケーション終了します", "Direct3Dインタフェースの作成が失敗しましたので", MB_OK);//OKを押されるまでプログラムがとまる
		return false;
	}
	//Direct3Dデバイスの取得

	//デバイスの取得に必要な情報構造体の作成
	D3DPRESENT_PARAMETERS d3dpp = {};
	

	d3dpp.BackBufferWidth = 1280;//バックバッファのサイズ設定
	d3dpp.BackBufferHeight = 720;//もしサイズが違うと引き延ばされる
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;//バックバッファのフォーマット//デスクトップのフォーマットと同一
	d3dpp.BackBufferCount = 1;//バックバッファを1つ作ってダブルバッファにする
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//スワップ方法の設定
	d3dpp.Windowed = TRUE;//フルスクリーンにするかウィンドウにするか
	//小文字のtrueはC++から、そしてD3Dはwindows自作の大文字の方
	d3dpp.EnableAutoDepthStencil = TRUE;//深度バッファ、ステンシルバッファの使用するか
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//深度バッファ・ステンシルバッファが前にあるよ後ろにあるよっていう情報を入れる
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//フルスクリーン時のリフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//リフレッシュレートとPresent処理の関係を指定する
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//これでCPUの処理時間に依存した性能出せるだけ出せる(安定しないが//リフレッシュレートとPresent処理の関係を指定する
	//これでもまだ注文書書いた程度なのでまだ出来てない

	HRESULT hr;
	hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hw, D3DCREATE_HARDWARE_VERTEXPROCESSING/*ハードウェアで計算をすかどうか*/, &d3dpp, &g_pDevice);
	//これで発注書書いたものを発注先にたたきつけて発注してもらう//&g_pDeviceに良さげな奴の場所を教えてくれる感じ,そしてそれが無いとポリゴン１つすらかけない
	//第二引数はデバイスで全てやってくれるか、コンピュータで計算するかを選べる、そして第三引数で//女の子に女の子を紹介してもらうような感じ
	//DX系の関数はHRESULTという結果を返してくれる
	if (FAILED(hr))
	{//FAILEDで包んでやる事により失敗か調べることが出来る
	//失敗や成功だけ判定する場合はFAILED()やSUCCEEDEDを()を使うべし
		MessageBox(NULL, "アプリケーション終了します", "Direct3Dデバイスの取得にが失敗しましたので", MB_OK);//OKを押されるまでプログラムがとまる
		return false;
	}
	//ここにテクスチャ情報をいれる

	//UVアドレッシングモードの設定
	//g_pDevice->SetSamplerState;//初期はダブルラップ(反復)モード(1で割ったあまりが出る(つまり4とかしていしてやると画像サイズ/4したものが4つ出る
	//Uが縦　、Vが横
	
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);//これが初期設定
	//テクスチャフィルタリングの設定
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);

	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);//これがCLAMP,最後のラインのピクセルをそのまま延長

	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);//このMIRRORはある不具合を直すのに便利である
	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);//これがMIRROR,反転する(2以上の場合はまたさらに反転して..って感じの、

	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);//BORDER
	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);//これがBORDER,UV参照値外は下のD3DCOLOR_RGBAで塗りつぶす
	//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DCOLOR_RGBA(255,255,0,255));//そんなに処理が速いってことじゃない、この行だけはbiginscene、Endsceneの時に呼び出してもおK

	//ほんと謎
//アルファブレンドの設定
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//アルファブレンド有効にする
	//半透明	描画色=今から描画するRGB*今から描画するα+画面のRGB*(１-今から描画するα)
	g_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//ポリゴンRGB * テクスチャRGB
	//テクスチャα * テクスチャαにする処理
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	return true;//初期化成功
}
//Direct3D9の終了処理、失敗時は0を投下
void MyDirect3D_Finalize(void)
{
	if(g_pDevice==nullptr)
	{
		MessageBox(NULL, "エラー", "g_pDevice", MB_OK);//OKを押されるまでプログラムがとまる

	}
	if (g_pDevice)
	{
		g_pDevice->Release();
		g_pDevice = NULL;
	}

	if (g_pD3D == nullptr)
	{
		MessageBox(NULL, "エラー(ぬるぽ)", "g_pD3D", MB_OK);//OKを押されるまでプログラムがとまる
	}

	if (g_pD3D)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void)
{
	return g_pDevice;
}


LPDIRECT3D9 MyDirect3D_GetLPDIRECT3D9(void)
{
	return g_pD3D;
}