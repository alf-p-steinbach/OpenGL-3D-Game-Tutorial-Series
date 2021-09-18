/*MIT License

C++ OpenGL 3D Game Tutorial Series (https://github.com/PardCode/OpenGL-3D-Game-Tutorial-Series)

Copyright (c) 2021, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Game/OGame.h>
#include <Windows.h>
#include <assert.h>

#include <functional>       // std::invoke

namespace {
    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
        case WM_CLOSE:
        {
            PostQuitMessage(EXIT_SUCCESS);
            break;
        }

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        return NULL;
    }

}  // namespace <anon>

OWindow::OWindow()
{
    static const ATOM window_class_id = std::invoke(
        []() -> ATOM
        {
            WNDCLASSEX wc = {};
            wc.cbSize = sizeof(WNDCLASSEX);
            wc.lpszClassName = L"OGL3DWindow";
            wc.lpfnWndProc = &WndProc;
            return RegisterClassEx(&wc);
        }
    );
    assert(window_class_id);

    const DWORD style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME;
    RECT rc = { 0,0,1024,768 };
    AdjustWindowRect(&rc, style, false);

    m_handle = CreateWindowEx(
        DWORD(), MAKEINTATOM(window_class_id), L"PardCode | OpenGL 3D Game",
        style, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
        HWND(), HMENU(), HINSTANCE(), nullptr);
    assert(m_handle);

    SetWindowLongPtr(HWND(m_handle), GWLP_USERDATA, LONG_PTR(this));

    ShowWindow(HWND(m_handle), SW_SHOW);
    UpdateWindow(HWND(m_handle));
}

OWindow::~OWindow()
{
    DestroyWindow(HWND(m_handle));
}
