#pragma once

#include <QObject>

#include "ui.hpp"
#include "wndx/clbrd/aliases.hpp"

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
