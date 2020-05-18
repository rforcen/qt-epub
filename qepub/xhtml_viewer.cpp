#include "xhtml_viewer.h"

XHTML_viewer::XHTML_viewer(QWidget *parent) : QTextBrowser(parent) {}

QVariant XHTML_viewer::loadResource(int type, const QUrl &name) {
  auto path = epub->relative_to_file(name);  // convert ../p/n -> OEBPS/p/n

  switch (type) {
    case QTextDocument::ImageResource:
      return QVariant::fromValue(QImage::fromData(epub->contents[path]));
      break;

    case QTextDocument::StyleSheetResource:
      return QVariant::fromValue(epub->contents[path]);
      break;

    case QTextDocument::HtmlResource:
      return QTextBrowser::loadResource(type, name);
    case QTextDocument::UserResource:
    default:
      return QTextBrowser::loadResource(type, name);
  }
}
