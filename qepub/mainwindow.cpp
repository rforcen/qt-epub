#include "mainwindow.h"

#include <qtablenumberitem.h>

#include <QDir>
#include <QEpub>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->centralwidget->hide();

  create_tool_bar();
}

void MainWindow::create_tool_bar() {  // use mac toolbar
  auto tb = new QMacToolBar(this);
  auto tbItem = tb->addItem(QIcon(QStringLiteral(":/icons/open.png")),
                            QStringLiteral("open"));
  connect(tbItem, &QMacToolBarItem::activated,
          [&]() { on_actionopen_triggered(); });

  tb->attachToWindow(windowHandle());
}

void MainWindow::show_epub() {
  if (epub) {
    this->setWindowTitle(QFileInfo(epub_file).fileName());
    ui->textBrowser->epub = epub;
    ui->textBrowser->setHtml(epub->get_first_page());

    // populate metadata table
    ui->table_index->clear();
    ui->table_index->setRowCount(epub->metadata_size());

    int row = 0;
    for (auto &metadata : epub->get_metadata()) {
      ui->table_index->setItem(row, 0, new QTableNumberItem(metadata.id));
      ui->table_index->setItem(row, 1, new QTableNumberItem(metadata.content));
      row++;
    }

    // spine
    ui->listWidget->clear();
    ui->listWidget->addItems(epub->get_spine_list());
  }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item) {
  ui->textBrowser->setHtml(epub->qstext_from_basename(item->text()));
}

void MainWindow::on_actionopen_triggered() {
  if (!(epub_file = QFileDialog::getOpenFileName(this, "open epub", epub_file,
                                                 "epub File (*.epub)"))
           .isEmpty()) {
    if (epub) delete epub;
    epub = new QEpub(epub_file);
    show_epub();
  }
}
