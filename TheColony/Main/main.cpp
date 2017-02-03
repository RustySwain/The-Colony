#include "Defines.h"
#include "Macros.h"
#include "crtdbg.h"
#include <chrono>
#include <string>
#include "Application.h"
#include "Time.h"
#include "Debug.h"

using namespace std;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hInstancePrev, LPSTR _cmdLine, int _showCmd)
{
	// Leak detection
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);
#endif
	// Start up the app singleton
	Application& app = *Application::GetInstance();

	// Windows Stuff
	HWND hWnd;
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = _hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass1";
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	RegisterClassEx(&wc);

	RECT monitorRect;
	const HWND desktopWindow = GetDesktopWindow();
	GetWindowRect(desktopWindow, &monitorRect);

	hWnd = CreateWindowEx(NULL, "WindowClass1", "Supersonic Acrobatic Rocket Powered Battlecars 2: Electric Boogaloo: Dawn of the Rise of the Rising Revengeance of the Brotherhood of the Dawn of the Final Day of the Reckoning of the 99 Dragons: The Presequel of Time and Space  LLC Project", WS_POPUP, 0, 0, monitorRect.right, monitorRect.bottom, NULL, NULL, _hInstance, NULL);
	ShowWindow(hWnd, _showCmd);

	// Initialize the Game
	app.GetWindowRect() = monitorRect;
	app.Init(hWnd);
	MSG msg;
	ZMem(msg);

	// For tracking elapsed time
	auto startTime = chrono::high_resolution_clock::now();
	unsigned int numFrames = 0;
	float invFPS = 1 / (float)FRAME_RATE;
	float seconds = 0;

	// Update/Render Loop
	while (msg.message != WM_QUIT)
	{
		// Only Render 60 FPS
		auto endTime = chrono::high_resolution_clock::now();
		double elapsed = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count() * 1e-6;
		if (elapsed > invFPS)
		{
			numFrames++;
			Time::SetDelta((float)elapsed);
			seconds += Time::Delta();
			app.Update();
			app.Render();
			startTime = endTime;
		}
		// Output framerate
		if (seconds > 1)
		{
			string secondsStr = to_string(numFrames);
			numFrames = 0;
			seconds = 0;
			Debug::Log(("Frame Rate: " + secondsStr).c_str(), 0);
		}
		// Windows
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// TODO: Remove. This is only so I can be lazy
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
	}

	// Shutdown Program
	app.Shutdown();
	delete &app;
	return 0;
}