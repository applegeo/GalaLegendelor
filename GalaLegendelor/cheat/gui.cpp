#include "gui.h"

#include "../imgui/imgui.h";
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImpWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter
);

long __stdcall WindowProcess(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter)
{
	if (ImGui_ImpWin32_WndProcHandler(window, message, wideParameter, longParameter))
		return true;

	switch (message)
	{
	case WM_SIZE: {
		if (gui::device && wideParameter != SIZE_MINIMIZED)
		{
			gui::presentParameters.BackBufferWidth = LOWORD(longParameter);
			gui::presentParameters.BackBufferHeight = HIWORD(longParameter);
			gui::ResetDevice();
		}
	}return 0;
	case WM_SYSCOMMAND: {
		if ((wideParameter & 0xfff0) == SC_KEYMENU) // Disable ALT app menu
			return 0;
	}break;

	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}
	case WM_LBUTTONDOWN: {
		gui::position = MAKEPOINTS(longParameter)l //set click points
	}return 0;

	case WM_MOUSEMOVE: {
		if (wideParameter == MK_LBUTTON)
		{
			const auto points = MAKEPOINTS(longParameter);
			auto rect = ::RECT{ };

			GetWindowRect(gui::window, &rect);

			rect.left += points.x - gui::position.x;
			rect.top += points.y - gui::position.y;

			if (gui::position.x >= 0 &&
				gui::position.x <= gui::WIDTH &&
				gui::position.y >= 0 &&
				gui::position.y <= 19)
				SetWindowPos(
					gui::window,
					HWND_TOPMOST,
					rect.left,
					rect.top,
					0, 0,
					SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
				);
		}
	}return 0;

	}

	return DefWindowProcW(window, message, wideParameter, longParameter)
}



void gui::CreateHWindow(
	const char* windowName,
	const char* className)noexcept;
{
	windowClass.cb = sizeof(WNDCLASSEXA);
	windowClass.style = CS_CLASSDC;
	windowClass.lpfnWndProc = WindowProcess;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.jInstance = GetModuleHandleA(0);
	windowClass.hIcon = 0;
	windowClass.hCurosr = 0;
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = className;
	windowClass.hIconSm = 0;

	RegisterClassExA(&windowClass);

	window = CreateWindowA(
		className,
		windowName,
		WS_POPUP,
		100,
		100,
		WIDTH,
		HEIGHT,
		0,
		0,
		windowClass.hInstance,
		0
	);

	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);
}

void gui::DestroyHWindow()noexcept;
{
	DestroyWindow(window);
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}

bool gui::CreateDevice() noexcept;
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d)
		return false;

	ZeroMemory(&presentParameters, sizeof(presentParameters));

	presentParameters.Windowed = TRUE;
	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.BackBufferFormat = D3DFMT_UNKOWN;
	presentParameters.EnableAutoDepthStencil = TRUE;
	presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
	presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&presentParameters,
		&device) < 0)
		return false;
	
	return true;

}

void gui::ResetDevice() noexcept;
{
	ImGui_Imp
}

void gui::DestroyDevice()noexcept;
{

}


void gui::CreateImGui()noexcept;
{

}

void gui::DestroyImGui()noexcept;
{

}

void gui::BeginRender()noexcept;
{

}

void gui::EndRender()noexcept;
{

}

void gui::Render()noexcept;
{

}