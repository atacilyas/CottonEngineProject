// Windows Header Files:
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <crtdbg.h>
#include <Initguid.h>
#include <dxgidebug.h>
#include <time.h>
//engine header files
#include "../CottonEngine/MainClass.h"
#include "MainScene.h"
int wmain()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	return wWinMain(hInstance, 0, nullptr, SW_SHOW);
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, WCHAR*, int)
{
	//set random seed
	srand((int)time(NULL));

	//notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Enable run-time memory leak check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	typedef HRESULT(__stdcall *fPtr)(const IID&, void**);
	HMODULE hDll = LoadLibrary("dxgidebug.dll");
	fPtr DXGIGetDebugInterface = (fPtr)GetProcAddress(hDll, "DXGIGetDebugInterface");

	IDXGIDebug* pDXGIDebug;
	DXGIGetDebugInterface(__uuidof(IDXGIDebug), (void**)&pDXGIDebug);
	//_CrtSetBreakAlloc(384);//break at line
#endif

	//start the gameloop
	MainClass* t = new MainScene();
	t->InitializeGameLoop();
	delete t;

#if defined(DEBUG) | defined(_DEBUG)

	// unresolved external  
	if (pDXGIDebug) pDXGIDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
	pDXGIDebug->Release();
#endif

}