#ifndef WINNATIVEWINDOW_H
#define WINNATIVEWINDOW_H

#include "Windows.h"
#include "Windowsx.h"

#include <QWidget>

class WinNativeWindow {
 public:
  WinNativeWindow(LPCWSTR title, const int x, const int y, const int width,
                  const int height);
  ~WinNativeWindow();

  HWND window_handle() const { return window_handle_; }

  HWND child_window_handle() const { return child_window_handle_; }

  void set_child_window_handle(const HWND &handle) {
    child_window_handle_ = handle;
  }

  QWidget *child_widget() { return child_widget_; }

  void set_child_widget(QWidget *child) { child_widget_ = child; }

  static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
                                  LPARAM lParam);

  // These six functions exist to restrict native window resizing to whatever
  // you want your app minimum/maximum size to be
  void SetMinimumSize(const int width, const int height);
  int GetMinimumHeight();
  int GetMinimumWidth();

  void SetMaximumSize(const int width, const int height);
  int GetMaximumHeight();
  int GetMaximumWidth();

  void SetGeometry(const int x, const int y, const int width, const int height);

 private:
  struct SizeType {
    SizeType() : required(false), width(0), height(0) {}
    bool required;
    int width;
    int height;
  };

  HWND window_handle_;

  HWND child_window_handle_;
  QWidget *child_widget_;

  SizeType minimum_size_;
  SizeType maximum_size_;

  static const DWORD aero_borderless = WS_POPUP | WS_CAPTION | WS_SYSMENU |
                                       WS_MINIMIZEBOX | WS_MAXIMIZEBOX |
                                       WS_THICKFRAME | WS_CLIPCHILDREN;
};

#endif  // WINNATIVEWINDOW_H
