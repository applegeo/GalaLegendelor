#include <d3d9.h>

namespace gui
{
	 //constant window size
	constexpr int WIDTH = 500;
	constexpr int HEIGHT = 300;

	inline bool exit = true;

	//winapi window vars
	inline HWND window = nullptr;
	inline WNDCLASSEXA windowClass = { };

	//point for windows movement
	inline POINTS position = { };
	
	//direct x state vars
	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = { };
	
	//creeare si distrugere window
	void CreateHWindow(
		const char* windowName,
		const char* className)noexcept;
	void DestroyHWindow()noexcept;

	//handle creeare si distrugere
	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice()noexcept;

	//handle ImGui creere si distrugere
	void CreateImGui()noexcept;
	void DestroyImGui()noexcept;

	void BeginRender()noexcept;
	void EndRender()noexcept;
	void Render()noexcept;
}