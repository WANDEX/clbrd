#include "mainwindow.hpp"

#include <QtGlobal>  // QT_VERSION_CHECK

#include "ui_mainwindow.h"  // generated header for Ui::MainWindow

namespace wndx::clbrd {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_ui_self(ui::MainWindow(this).self_r()),
      m_ui(m_ui_self.ref()) {
  m_ui.setupUi(this);

  // at the end - after signal/slot connections
  // startup();
}

MainWindow::~MainWindow() = default;

// void MainWindow::startup() {}

}  // namespace wndx::clbrd
