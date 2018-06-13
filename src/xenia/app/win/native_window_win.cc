#include "native_window_win.h"

#include <dwmapi.h>
#include <stdexcept>
#include "../theme_manager.h"

WinNativeWindow::WinNativeWindow(LPCWSTR title, const int x, const int y,
                                 const int width, const int height)
    : window_handle_(nullptr),
      child_widget_(nullptr),
      child_window_handle_(nullptr) {
  Theme theme = ThemeManager::SharedManager().theme();

  HBRUSH windowBackground = CreateSolidBrush(theme["background"].rgb());

  HINSTANCE hInstance = GetModuleHandle(nullptr);
  WNDCLASSEX wcx = {0};

  wcx.cbSize = sizeof(WNDCLASSEX);
  wcx.style = CS_HREDRAW | CS_VREDRAW;
  wcx.hInstance = hInstance;
  wcx.lpfnWndProc = WndProc;
  wcx.cbClsExtra = 0;
  wcx.cbWndExtra = 0;
  wcx.lpszClassName = L"WindowClass";
  wcx.hbrBackground = windowBackground;
  wcx.hCursor = LoadCursor(hInstance, IDC_ARROW);

  RegisterClassEx(&wcx);
  if (FAILED(RegisterClassEx(&wcx))) {
    throw std::runtime_error("Couldn't register window class");
  }

  // Create a native window with the appropriate style
  window_handle_ = CreateWindow(L"WindowClass", title, aero_borderless, x, y,
                                width, height, 0, 0, hInstance, nullptr);
  if (!window_handle_) {
    throw std::runtime_error("couldn't create window because of reasons");
  }

  SetWindowLongPtr(window_handle_, GWLP_USERDATA,
                   reinterpret_cast<LONG_PTR>(this));

  SetWindowPos(window_handle_, 0, 0, 0, 0, 0,
               SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

  const MARGINS shadow_on = {1, 1, 1, 1};
  DwmExtendFrameIntoClientArea(window_handle_, &shadow_on);
}

WinNativeWindow::~WinNativeWindow() {
  // Hide the window & send the destroy message
  ShowWindow(window_handle_, SW_HIDE);
  DestroyWindow(window_handle_);
}

LRESULT CALLBACK WinNativeWindow::WndProc(HWND hWnd, UINT message,
                                          WPARAM wParam, LPARAM lParam) {
  WinNativeWindow* window =
      reinterpret_cast<WinNativeWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

  if (!window) {
    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  switch (message) {
    // ALT + SPACE or F10 system menu
    case WM_SYSCOMMAND: {
      if (wParam == SC_KEYMENU) {
        RECT winrect;
        GetWindowRect(hWnd, &winrect);
        TrackPopupMenu(GetSystemMenu(hWnd, false), TPM_TOPALIGN | TPM_LEFTALIGN,
                       winrect.left + 5, winrect.top + 5, 0, hWnd, NULL);
        break;
      } else {
        return DefWindowProc(hWnd, message, wParam, lParam);
      }
    }
    case WM_NCCALCSIZE: {
      // this kills the window frame and title bar we added with
      // WS_THICKFRAME and WS_CAPTION
      return 0;
    }

    // If the parent window gets any close messages, send them over to
    // QWinWidget and don't actually close here
    case WM_CLOSE: {
      if (window->child_window_handle()) {
        SendMessage(window->child_window_handle(), WM_CLOSE, 0, 0);
        return 0;
      }
      break;
    }
    case WM_DESTROY: {
      PostQuitMessage(0);
      break;
    }

    case WM_NCHITTEST: {
      const LONG border_width =
          8 *
          window->child_widget()
              ->window()
              ->devicePixelRatio();  // This value can be arbitrarily large
                                     // as only intentionally-HTTRANSPARENT'd
                                     // messages arrive here
      RECT winrect;
      GetWindowRect(hWnd, &winrect);
      long x = GET_X_LPARAM(lParam);
      long y = GET_Y_LPARAM(lParam);

      // bottom left corner
      if (x >= winrect.left && x < winrect.left + border_width &&
          y < winrect.bottom && y >= winrect.bottom - border_width) {
        return HTBOTTOMLEFT;
      }
      // bottom right corner
      if (x < winrect.right && x >= winrect.right - border_width &&
          y < winrect.bottom && y >= winrect.bottom - border_width) {
        return HTBOTTOMRIGHT;
      }
      // top left corner
      if (x >= winrect.left && x < winrect.left + border_width &&
          y >= winrect.top && y < winrect.top + border_width) {
        return HTTOPLEFT;
      }
      // top right corner
      if (x < winrect.right && x >= winrect.right - border_width &&
          y >= winrect.top && y < winrect.top + border_width) {
        return HTTOPRIGHT;
      }
      // left border
      if (x >= winrect.left && x < winrect.left + border_width) {
        return HTLEFT;
      }
      // right border
      if (x < winrect.right && x >= winrect.right - border_width) {
        return HTRIGHT;
      }
      // bottom border
      if (y < winrect.bottom && y >= winrect.bottom - border_width) {
        return HTBOTTOM;
      }
      // top border
      if (y >= winrect.top && y < winrect.top + border_width) {
        return HTTOP;
      }

      // If it wasn't a border but we still got the message, return HTCAPTION to
      // allow click-dragging the window
      return HTCAPTION;

      break;
    }

      // When this native window changes size, it needs to manually resize the
      // QWinWidget child
    case WM_SIZE: {
      RECT winrect;
      GetClientRect(hWnd, &winrect);

      WINDOWPLACEMENT wp;
      wp.length = sizeof(WINDOWPLACEMENT);
      GetWindowPlacement(hWnd, &wp);
      QWidget* child_widget = window->child_widget();
      if (child_widget) {
        if (wp.showCmd == SW_MAXIMIZE) {
          child_widget->setGeometry(
              8, 8  // Maximized window draw 8 pixels off screen
              ,
              winrect.right / child_widget->window()->devicePixelRatio() - 16,
              winrect.bottom / child_widget->window()->devicePixelRatio() - 16);
        } else {
          child_widget->setGeometry(
              0, 0, winrect.right / child_widget->window()->devicePixelRatio(),
              winrect.bottom / child_widget->window()->devicePixelRatio());
        }
      }

      break;
    }

    case WM_GETMINMAXINFO: {
      MINMAXINFO* minmax = (MINMAXINFO*)lParam;
      if (window->minimum_size_.required) {
        minmax->ptMinTrackSize.x = window->GetMinimumWidth();
        minmax->ptMinTrackSize.y = window->GetMinimumHeight();
      }

      if (window->maximum_size_.required) {
        minmax->ptMaxTrackSize.x = window->GetMaximumWidth();
        minmax->ptMaxTrackSize.y = window->GetMaximumHeight();
      }
      return 0;
    }
  }

  return DefWindowProc(hWnd, message, wParam, lParam);
}

void WinNativeWindow::SetGeometry(const int x, const int y, const int width,
                                  const int height) {
  MoveWindow(window_handle_, x, y, width, height, 1);
}

void WinNativeWindow::SetMinimumSize(const int width, const int height) {
  this->minimum_size_.required = true;
  this->minimum_size_.width = width;
  this->minimum_size_.height = height;
}

int WinNativeWindow::GetMinimumWidth() { return minimum_size_.width; }

int WinNativeWindow::GetMinimumHeight() { return minimum_size_.height; }

void WinNativeWindow::SetMaximumSize(const int width, const int height) {
  this->maximum_size_.required = true;
  this->maximum_size_.width = width;
  this->maximum_size_.height = height;
}

int WinNativeWindow::GetMaximumWidth() { return maximum_size_.width; }

int WinNativeWindow::GetMaximumHeight() { return maximum_size_.height; }
