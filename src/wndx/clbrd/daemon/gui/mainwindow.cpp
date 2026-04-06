#include "mainwindow.hpp"

#include <QLocale>
#include <QtGlobal>  // QT_VERSION_CHECK

#include "ui_mainwindow.h"  // generated header for Ui::MainWindow

namespace wndx::clbrd {

/// Required for using the '_L1' string literal.
using namespace Qt::StringLiterals;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_ui_self(ui::MainWindow(this).self_r()),
      m_ui(m_ui_self.ref()) {
  m_ui.setupUi(this);

  connect(m_ui.action_Exit, &QAction::triggered, this, &MainWindow::close);

  connect(m_ui.action_Chinese_Simplified, &QAction::triggered, this,
          [&]() { SwitchToLanguage("zh_CN"); });
  connect(m_ui.action_English, &QAction::triggered, this,
          [&]() { SwitchToLanguage("en_US"); });
  connect(m_ui.action_Russian, &QAction::triggered, this,
          [&]() { SwitchToLanguage("ru_RU"); });

  /// at the end - after signal/slot connections
  Startup();
}

MainWindow::~MainWindow() = default;

bool MainWindow::SwitchToLanguage(const QString& language) {
  static constexpr auto fn{"SwitchToLanguage()"};
  if (m_translator.load(QStringLiteral(":/i18n/clbrd_") + language)) {
    QCoreApplication::installTranslator(&m_translator);
    m_ui.retranslateUi(this);
    WNDX_LOG(LL::DBUG, "[ OK ] {} language: {}\n", fn, language);
    return true;
  } else {
    WNDX_LOG(LL::ERRO, "[FAIL] {} language: {}\n", fn, language);
  }
  return false;
}

/// \see https://doc.qt.io/qt-6/qtranslator.html#details
bool MainWindow::SetLanguageToDefaultLocale() {
  static constexpr auto fn{"SetLanguageToDefaultLocale()"};
  if (m_translator.load(QLocale(), "clbrd"_L1, "_"_L1, ":/i18n"_L1)) {
    WNDX_LOG(LL::DBUG, "[ OK ] {} language to the system locale\n", fn);
    QCoreApplication::installTranslator(&m_translator);
    m_ui.retranslateUi(this);
    return true;
  } else {
    WNDX_LOG(LL::DBUG, "[ OK ] {} fallback\n", fn);
    SwitchToLanguage("en_US");
    return false;
  }
}

void MainWindow::Startup() { SetLanguageToDefaultLocale(); }

}  // namespace wndx::clbrd
