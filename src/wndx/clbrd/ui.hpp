#pragma once

#include <QObject>

namespace Ui {  // forward declare the Qt-generated class

class MainWindow;

}

namespace wndx::clbrd {

class Keys;

namespace ui {

class MainWindow {
 public:
  explicit MainWindow(QObject*);
  ~MainWindow() = default;

  // THE MAGIC: Overload the arrow operator
  // This allows: myWrapper->anyQtWidget (avoids ui->ui->).
  [[nodiscard]] Ui::MainWindow* operator->() { return m_ui_ptr; }
  [[nodiscard]] Ui::MainWindow const* operator->() const { return m_ui_ptr; }

  [[nodiscard]] Ui::MainWindow* ptr() { return m_ui_ptr; }
  [[nodiscard]] Ui::MainWindow const* ptr() const { return m_ui_ptr; }

  [[nodiscard]] Ui::MainWindow& ref() { return *m_ui_ptr; }
  [[nodiscard]] Ui::MainWindow& ref() const { return *m_ui_ptr; }

  auto keys(QObject*) -> Keys&;

  [[nodiscard]] decltype(auto) self_t() { return *this; }
  [[nodiscard]] decltype(auto) self_p() { return &m_self; }
  [[nodiscard]] decltype(auto) self_r() { return m_self; }

  void cleanup();

 private:
  ui::MainWindow& m_self;
  Ui::MainWindow* m_ui_ptr;
  Keys* m_keys_ptr;
};

}  // namespace ui
}  // namespace wndx::clbrd
