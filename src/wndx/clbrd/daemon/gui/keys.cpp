#include "keys.hpp"

#include <QDebug>

#include "ui_mainwindow.h"  // generated header for Ui::MainWindow

namespace wndx::clbrd {

Keys::Keys(QObject* window, Ui::MainWindow& ui_)
    : QObject(window), mw(window), ui(ui_) {
  this->hotkeys();  // bind hotkeys
}

Keys::~Keys() = default;

/// \brief bind hotkeys.
void Keys::hotkeys() {}

}  // namespace wndx::clbrd
