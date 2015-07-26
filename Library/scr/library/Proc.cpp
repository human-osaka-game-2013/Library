#include <windows.h>


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		if(wp==VK_ESCAPE){
			PostQuitMessage (0);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage (0);
		break;

	}
	return DefWindowProc (hWnd, msg, wp, lp);
}