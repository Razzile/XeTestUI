/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Solutions component.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

/* 																										 */
/* 																										 */
/* File is originally from
 * https://github.com/qtproject/qt-solutions/tree/master/qtwinmigrate/src */
/* 																										 */
/* It has been modified to support borderless window (HTTRANSPARENT) & to remove
 * pre Qt5 cruft          */
/* 																										 */
/* 																										 */

#include "native_widget_win.h"

#include <qt_windows.h>
#include <QApplication>
#include <QEvent>
#include <QFocusEvent>
#include <QWindow>

/*!
    \class QWinWidget qwinwidget.h
    \brief The QWinWidget class is a Qt widget that can be child of a
    native Win32 widget.

    The QWinWidget class is the bridge between an existing application
    user interface developed using native Win32 APIs or toolkits like
    MFC, and Qt based GUI elements.

    Using QWinWidget as the parent of QDialogs will ensure that
    modality, placement and stacking works properly throughout the
    entire application. If the child widget is a top level window that
    uses the \c WDestructiveClose flag, QWinWidget will destroy itself
    when the child window closes down.

    Applications moving to Qt can use QWinWidget to add new
    functionality, and gradually replace the existing interface.
*/

WinNativeWidget::WinNativeWidget()
    : QWidget(nullptr),
      layout_(),
      widget_(nullptr),
      parent_window_handle_(nullptr),
      prev_focus_(nullptr),
      reenable_parent_(false),
      border_width_(6),
      toolbar_height_(40) {
  widget_ = new MainWidget(this);
  LPCWSTR title = (LPCWSTR)widget_->window_title().utf16();
  // Create a native window and give it geometry values * devicePixelRatio for
  // HiDPI support
  parent_window_ = new WinNativeWindow(
      title, 1 * window()->devicePixelRatio(), 1 * window()->devicePixelRatio(),
      1 * window()->devicePixelRatio(), 1 * window()->devicePixelRatio());

  parent_window_->SetMinimumSize(640 * window()->devicePixelRatio(),
                                 360 * window()->devicePixelRatio());

  // Save the native window handle for shorthand use
  parent_window_handle_ = parent_window_->window_handle();
  Q_ASSERT(parent_window_handle_);

  // Create the child window & embed it into the native one
  if (parent_window_handle_) {
    setWindowFlags(Qt::FramelessWindowHint);
    setProperty("_q_embedded_native_parent_handle", (WId)parent_window_handle_);
    SetWindowLong((HWND)winId(), GWL_STYLE,
                  WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

    SetParent((HWND)winId(), parent_window_handle_);
    QEvent e(QEvent::EmbeddingControl);
    QApplication::sendEvent(this, &e);
  }

  // Pass along our window handle & widget pointer to WinFramelessWidget so we
  // can exchange messages
  parent_window_->set_child_window_handle((HWND)winId());
  parent_window_->set_child_widget(this);

  // Clear margins & spacing & add the layout to prepare for the MainAppWidget
  setContentsMargins(0, 0, 0, 0);
  setLayout(&layout_);
  layout_.setContentsMargins(0, 0, 0, 0);
  layout_.setSpacing(0);

  // Create the true app widget
  layout_.addWidget(widget_);
  widget_->setParent(this, Qt::Widget);
  widget_->setVisible(true);

  // Update the border_width_ value if needed for HiDPI displays
  border_width_ = border_width_ * window()->devicePixelRatio();

  // Update the TOOLBARHEIGHT value to match the height of toolBar * if needed,
  // the HiDPI display
  if (widget_->window_toolbar()) {
    toolbar_height_ =
        widget_->window_toolbar()->height() * window()->devicePixelRatio();
  }

  // You need to keep the native window in sync with the Qt window & children,
  // so wire min/max/close buttons to slots inside of QWinWidget. QWinWidget can
  // then talk with the native window as needed
  QPushButton *min_button = widget_->min_button();
  QPushButton *max_button = widget_->max_button();
  QPushButton *close_button = widget_->close_button();

  if (min_button) {
    connect(min_button, &QPushButton::clicked, this,
            &WinNativeWidget::OnMinimizeButtonClicked);
  }
  if (max_button) {
    connect(max_button, &QPushButton::clicked, this,
            &WinNativeWidget::OnMaximizeButtonClicked);
  }
  if (close_button) {
    connect(close_button, &QPushButton::clicked, this,
            &WinNativeWidget::OnCloseButtonClicked);
  }

  // Send the parent native window a WM_SIZE message to update the widget size
  SendMessage(parent_window_handle_, WM_SIZE, 0, 0);
}

/*!
    Destroys this object, freeing all allocated resources.
*/
WinNativeWidget::~WinNativeWidget() {}

/*!
    Returns the handle of the native Win32 parent window.
*/
HWND WinNativeWidget::GetParentWindow() const { return parent_window_handle_; }

/*!
    \reimp
*/
void WinNativeWidget::childEvent(QChildEvent *e) {
  QObject *obj = e->child();
  if (obj->isWidgetType()) {
    if (e->added()) {
      if (obj->isWidgetType()) {
        obj->installEventFilter(this);
      }
    } else if (e->removed() && reenable_parent_) {
      reenable_parent_ = false;
      EnableWindow(parent_window_handle_, true);
      obj->removeEventFilter(this);
    }
  }
  QWidget::childEvent(e);
}

/*! \internal */
void WinNativeWidget::SaveFocus() {
  if (!(prev_focus_ = ::GetFocus())) {
    prev_focus_ = GetParentWindow();
  }
}

/*!
    Shows this widget. Overrides QWidget::show().

    \sa showCentered()
*/
void WinNativeWidget::showEvent(QShowEvent *e) {
  QWidget::showEvent(e);
  ShowWindow(parent_window_handle_, true);
  SaveFocus();
  //  QWidget::show();
}

/*!
    Centers this widget over the native parent window. Use this
    function to have Qt toplevel windows (i.e. dialogs) positioned
    correctly over their native parent windows.

    \code
    QWinWidget qwin(hParent);
    qwin.center();

    QMessageBox::information(&qwin, "Caption", "Information Text");
    \endcode

    This will center the message box over the client area of hParent.
*/
void WinNativeWidget::Center() {
  const QWidget *child = findChild<QWidget *>();
  if (child && !child->isWindow()) {
    qWarning(
        "QWinWidget::center: Call this function only for QWinWidgets with "
        "toplevel children");
  }
  RECT r;
  GetWindowRect(parent_window_handle_, &r);
  setGeometry((r.right - r.left) / 2 + r.left, (r.bottom - r.top) / 2 + r.top,
              0, 0);
}

/*!
    \obsolete

    Call center() instead.
*/
void WinNativeWidget::ShowCentered() {
  Center();
  show();
}

void WinNativeWidget::setGeometry(int x, int y, int w, int h) {
  parent_window_->SetGeometry(
      x * window()->devicePixelRatio(), y * window()->devicePixelRatio(),
      w * window()->devicePixelRatio(), h * window()->devicePixelRatio());
}

/*!
    Sets the focus to the window that had the focus before this widget
    was shown, or if there was no previous window, sets the focus to
    the parent window.
*/
void WinNativeWidget::ResetFocus() {
  if (prev_focus_)
    ::SetFocus(prev_focus_);
  else
    ::SetFocus(GetParentWindow());
}

// Tell the parent native window to minimize
void WinNativeWidget::OnMinimizeButtonClicked() {
  SendMessage(parent_window_handle_, WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

// Tell the parent native window to maximize or restore as appropriate
void WinNativeWidget::OnMaximizeButtonClicked() {
  if (widget_->max_button()->isChecked()) {
    SendMessage(parent_window_handle_, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
  } else {
    SendMessage(parent_window_handle_, WM_SYSCOMMAND, SC_RESTORE, 0);
  }
}

void WinNativeWidget::OnCloseButtonClicked() {
  if (true /* put your check for it if it safe to close your app here */)  // eg,
                                                                           // does
                                                                           // the
                                                                           // user
                                                                           // need
                                                                           // to
                                                                           // save
                                                                           // a
                                                                           // document
  {
    // Safe to close, so hide the parent window
    ShowWindow(parent_window_handle_, false);

    // And then quit
    QApplication::quit();
  } else {
    // Do nothing, and thus, don't actually close the window
  }
}

bool WinNativeWidget::nativeEvent(const QByteArray &, void *message,
                                  long *result) {
  MSG *msg = (MSG *)message;

  if (msg->message == WM_SETFOCUS) {
    Qt::FocusReason reason;
    if (::GetKeyState(VK_LBUTTON) < 0 || ::GetKeyState(VK_RBUTTON) < 0)
      reason = Qt::MouseFocusReason;
    else if (::GetKeyState(VK_SHIFT) < 0)
      reason = Qt::BacktabFocusReason;
    else
      reason = Qt::TabFocusReason;
    QFocusEvent e(QEvent::FocusIn, reason);
    QApplication::sendEvent(this, &e);
  }

  // Only close if safeToClose clears()
  if (msg->message == WM_CLOSE) {
    if (true /* put your check for it if it safe to close your app here */)  // eg, does the user need to save a document
    {
      // Safe to close, so hide the parent window
      ShowWindow(parent_window_handle_, false);

      // And then quit
      QApplication::quit();
    } else {
      *result = 0;  // Set the message to 0 to ignore it, and thus, don't
                    // actually close
      return true;
    }
  }

  // Double check WM_SIZE messages to see if the parent native window is
  // maximized
  if (msg->message == WM_SIZE) {
    if (widget_ && widget_->max_button()) {
      // Get the window state
      WINDOWPLACEMENT wp;
      GetWindowPlacement(parent_window_handle_, &wp);

      // If we're maximized,
      if (wp.showCmd == SW_MAXIMIZE) {
        // Maximize button should show as Restore
        widget_->max_button()->setChecked(true);
      } else {
        // Maximize button should show as Maximize
        widget_->max_button()->setChecked(false);
      }
    }
  }

  // Pass NCHITTESTS on the window edges as determined by border_width_ &
  // TOOLBARHEIGHT through to the parent native window
  if (msg->message == WM_NCHITTEST) {
    RECT WindowRect;
    int x, y;

    GetWindowRect(msg->hwnd, &WindowRect);
    x = GET_X_LPARAM(msg->lParam) - WindowRect.left;
    y = GET_Y_LPARAM(msg->lParam) - WindowRect.top;

    if (x >= border_width_ &&
        x <= WindowRect.right - WindowRect.left - border_width_ &&
        y >= border_width_ && y <= toolbar_height_) {
      if (widget_->window_toolbar()) {
        // If the mouse is over top of the toolbar area BUT is actually
        // positioned over a child widget of the toolbar, Then we don't want to
        // enable dragging. This allows for buttons in the toolbar, eg, a
        // Maximize button, to keep the mouse interaction
        if (QApplication::widgetAt(QCursor::pos()) != widget_->window_toolbar())
          return false;
      }

      // The mouse is over the toolbar area & is NOT over a child of the
      // toolbar, so pass this message through to the native window for
      // HTCAPTION dragging
      *result = HTTRANSPARENT;
      return true;

    } else if (x < border_width_ && y < border_width_) {
      *result = HTTRANSPARENT;
      return true;
    } else if (x > WindowRect.right - WindowRect.left - border_width_ &&
               y < border_width_) {
      *result = HTTRANSPARENT;
      return true;
    } else if (x > WindowRect.right - WindowRect.left - border_width_ &&
               y > WindowRect.bottom - WindowRect.top - border_width_) {
      *result = HTTRANSPARENT;
      return true;
    } else if (x < border_width_ &&
               y > WindowRect.bottom - WindowRect.top - border_width_) {
      *result = HTTRANSPARENT;
      return true;
    } else if (x < border_width_) {
      *result = HTTRANSPARENT;
      return true;
    } else if (y < border_width_) {
      *result = HTTRANSPARENT;
      return true;
    } else if (x > WindowRect.right - WindowRect.left - border_width_) {
      *result = HTTRANSPARENT;
      return true;
    } else if (y > WindowRect.bottom - WindowRect.top - border_width_) {
      *result = HTTRANSPARENT;
      return true;
    }

    return false;
  }

  return false;
}

/*!
    \reimp
*/
bool WinNativeWidget::eventFilter(QObject *o, QEvent *e) {
  QWidget *w = (QWidget *)o;

  switch (e->type()) {
    case QEvent::WindowDeactivate:
      if (w->isModal() && w->isHidden())
        BringWindowToTop(parent_window_handle_);
      break;

    case QEvent::Hide:
      if (reenable_parent_) {
        EnableWindow(parent_window_handle_, true);
        reenable_parent_ = false;
      }
      ResetFocus();

      if (w->testAttribute(Qt::WA_DeleteOnClose) && w->isWindow())
        deleteLater();
      break;

    case QEvent::Show:
      if (w->isWindow()) {
        SaveFocus();
        hide();
        if (w->isModal() && !reenable_parent_) {
          EnableWindow(parent_window_handle_, false);
          reenable_parent_ = true;
        }
      }
      break;

    case QEvent::Close: {
      ::SetActiveWindow(parent_window_handle_);
      if (w->testAttribute(Qt::WA_DeleteOnClose)) deleteLater();
      break;
    }
    default:
      break;
  }

  return QWidget::eventFilter(o, e);
}

/*! \reimp
 */
void WinNativeWidget::focusInEvent(QFocusEvent *e) {
  QWidget *candidate = this;

  switch (e->reason()) {
    case Qt::TabFocusReason:
    case Qt::BacktabFocusReason:
      while (!(candidate->focusPolicy() & Qt::TabFocus)) {
        candidate = candidate->nextInFocusChain();
        if (candidate == this) {
          candidate = 0;
          break;
        }
      }
      if (candidate) {
        candidate->setFocus(e->reason());
        if (e->reason() == Qt::BacktabFocusReason ||
            e->reason() == Qt::TabFocusReason) {
          candidate->setAttribute(Qt::WA_KeyboardFocusChange);
          candidate->window()->setAttribute(Qt::WA_KeyboardFocusChange);
        }
        if (e->reason() == Qt::BacktabFocusReason)
          QWidget::focusNextPrevChild(false);
      }
      break;
    default:
      break;
  }
}

/*! \reimp
 */
bool WinNativeWidget::focusNextPrevChild(bool next) {
  QWidget *curFocus = focusWidget();
  if (!next) {
    if (!curFocus->isWindow()) {
      QWidget *nextFocus = curFocus->nextInFocusChain();
      QWidget *prevFocus = 0;
      QWidget *topLevel = 0;
      while (nextFocus != curFocus) {
        if (nextFocus->focusPolicy() & Qt::TabFocus) {
          prevFocus = nextFocus;
          topLevel = 0;
        }
        nextFocus = nextFocus->nextInFocusChain();
      }

      if (!topLevel) {
        return QWidget::focusNextPrevChild(false);
      }
    }
  } else {
    QWidget *nextFocus = curFocus;
    while (1 && nextFocus != 0) {
      nextFocus = nextFocus->nextInFocusChain();
      if (nextFocus->focusPolicy() & Qt::TabFocus) {
        return QWidget::focusNextPrevChild(true);
      }
    }
  }

  ::SetFocus(parent_window_handle_);

  return true;
}
