#pragma once

#include "wndx/clbrd/aliases.hpp"

#include "ui.hpp"

#include <QObject>

namespace wndx::clbrd {

class Keys : public QObject {
  Q_OBJECT
 public:
  explicit Keys(QObject* window, Ui::MainWindow& ui_);
  ~Keys() override;

 private:
  void hotkeys();

  QObject* mw;
  Ui::MainWindow& ui;
};

}  // namespace wndx::clbrd
