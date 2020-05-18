#pragma once

#include <qtablenumberitem.h>
#include <qtextindexer.h>

#include <QTableWidget>
#include <QtXml>

class Common {
 public:
  Common() : index(new qtextindexer) {}

  qtextindexer *index = nullptr;

  void populate_index_table(QTableWidget *table_index) {
    // populate index table
    table_index->clear();
    table_index->setRowCount(index->index.size());

    for (index->begin(); !index->end(); index->next()) {
      table_index->setItem(index->row, 0, new QTableNumberItem(index->key()));
      table_index->setItem(index->row, 1,
                           new QTableNumberItem(size_t(index->n_words())));
    }
  }

  QString xml_get_attribute(QString txt, QString item, QString attribute) {
    QString res;

    QDomDocument domDocument;
    QString err_msg;
    int err_line, err_col;
    if (domDocument.setContent(txt, false, &err_msg, &err_line, &err_col)) {
      QDomNodeList nl = domDocument.documentElement().elementsByTagName(item);
      res.append(nl.at(0).toElement().attribute(attribute) + " ");
    }
    return res;
  }

  // get content.opf
  class Pair {
   public:
    Pair(QString id, QString content) : id(id), content(content) {}
    QString id, content;
  };

  QString get_text(QDomNode &&child) { return child.toElement().text(); }
  QString get_attr(QDomNode &&child, QString an) {
    return child.toElement().attributeNode(an).value();
  }

  typedef QMap<QString, QList<Pair>> opf_map;

  opf_map xml_get_opf(QString txt) {
    opf_map m;
    QStringList itemlist = {"metadata", "manifest", "spine"};

    QString res;
    QDomDocument domDocument;
    QString err_msg;
    int err_line, err_col;

    if (domDocument.setContent(txt, false, &err_msg, &err_line, &err_col)) {
      for (auto &main_item : itemlist) {
        QDomNodeList nl =
            domDocument.documentElement().elementsByTagName(main_item);

        for (int i = 0; i < nl.count(); i++) {
          QDomNodeList childs = nl.at(i).childNodes();

          for (int j = 0; j < childs.count(); j++) {
            if (main_item == "metadata") {
              auto tn = childs.item(j).toElement().tagName();
              QString id, content;
              if (tn.contains("dc:")) {
                id = tn.remove("dc:"), content = get_text(childs.item(j));
                if (id == "date")
                  id += " " + get_attr(childs.item(j), "opf:event");

              } else {
                id = get_attr(childs.item(j), "name"),
                content = get_attr(childs.item(j), "content");
              }
              m[main_item] << Pair(id, content);

            } else if (main_item == "manifest") {
              auto id = get_attr(childs.item(j), "id");
              auto href = get_attr(childs.item(j), "href");
              m[main_item] << Pair(id, href);

            } else if (main_item == "spine") {
              auto id = get_attr(childs.item(j), "idref");
              m[main_item] << Pair(id, id);
            }
          }
        }
      }
    }
    return m;
  }

  QString find(QList<Pair> &lp, QString s) {
    for (auto &p : lp)
      if (p.id == s) return p.content;
    return QString();
  }

  // xml file <body> section -> qstring
  QString xml_read(QString file_name) {
    QString res;
    QFile file(file_name);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
      QDomDocument domDocument;
      if (domDocument.setContent(&file)) {
        QStringList il = {"h1", "h2", "p"};
        for (auto &_i : il) {
          QDomNodeList nl = domDocument.documentElement().elementsByTagName(_i);
          for (int i = 0; i < nl.size(); i++)
            res.append(nl.at(i).toElement().text() + " ");
        }
      }
      file.close();
    }
    return res;
  }

  QString xml_read_folder(QString folder) {
    QString content;
    for (auto &d : QDir(folder).entryInfoList({"*.xhtml"}))
      content.append(xml_read(d.filePath()));
    return content;
  }
};

extern Common *_c;
