#include "ui.hpp"

#include "keys.hpp"
#include "ui_mainwindow.h"  // generated header for Ui::MainWindow

namespace wndx::clbrd::ui {

MainWindow::MainWindow(QObject* window)
    : m_self(self_t()), m_ui_ptr(new Ui::MainWindow) {
  keys(window);
}

/// \brief init Keys class & bind hotkeys.
auto MainWindow::keys(QObject* window) -> Keys& {
  m_keys_ptr = new Keys(window, *m_ui_ptr);
  return *m_keys_ptr;
}

void MainWindow::cleanup() {
  delete m_keys_ptr;
  delete m_ui_ptr;
}

}  // namespace wndx::clbrd::ui
