#pragma once

#include <QMainWindow>
#include <QObject>

#include "ui.hpp"
#include "wndx/clbrd/aliases.hpp"

namespace wndx::clbrd {

class Keys;

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

  // signals:

  // private slots:
  //
  //  void startup();

 private:
  ui::MainWindow& m_ui_self;
  Ui::MainWindow& m_ui;
};

}  // namespace wndx::clbrd
