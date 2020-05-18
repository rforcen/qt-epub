#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QEpub>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QtMacExtras/QMacToolBar>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_listWidget_itemClicked(QListWidgetItem *item);

  void on_actionopen_triggered();

 private:
  Ui::MainWindow *ui;
  QEpub *epub = nullptr;
  QString epub_file;

  void show_epub();
  void create_tool_bar();
};
#endif  // MAINWINDOW_H
