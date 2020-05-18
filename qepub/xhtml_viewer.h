#ifndef XHTML_VIEWER_H
#define XHTML_VIEWER_H

#include <QEpub>
#include <QTextBrowser>

class XHTML_viewer : public QTextBrowser {
  Q_OBJECT
 public:
  XHTML_viewer(QWidget *parent = nullptr);
  QEpub *epub=nullptr;

  QVariant loadResource(int type, const QUrl &name) override;
};

#endif  // XHTML_VIEWER_H
