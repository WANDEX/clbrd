#pragma once

#include "wndx/clbrd/aliases.hpp"

#include "ui.hpp"

#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QTranslator>

namespace wndx::clbrd {

class Keys;

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

  // signals:

 private slots:
  bool SwitchToLanguage(const QString& language);
  bool SetLanguageToDefaultLocale();

  void Startup();

 private:  // NOLINT(readability-redundant-access-specifiers)
  QTranslator m_translator;
  ui::MainWindow& m_ui_self;
  Ui::MainWindow& m_ui;
};

}  // namespace wndx::clbrd
