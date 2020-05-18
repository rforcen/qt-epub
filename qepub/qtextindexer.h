#pragma once

#include <stop_words_es.h>

#include <QMap>
#include <QString>
#include <QVector>

class qtextindexer {
 public:
  qtextindexer() : sw(new StopWords) {}

  void add_indexes(QString &s) {
    QString w;

    for (auto &ch : s) {
      ch = ch.toLower();
      if (ch.isLetter())
        w.push_back(ch);
      else {
        if (!w.isEmpty()) {
          if (!(*sw)[w]) index[w] << pos;
          w.clear();
        }
      }
      pos++;
    }
    if (!w.isEmpty()) index[w] << pos;
  }

  void clear() {
    index.clear();
    pos = 0;
  }

  void begin() {
    if (qmi) delete qmi;
    qmi = new QMapIterator(index);
    next();
    row = 0;
  }
  void next() {
    if (qmi->hasNext()) qmi->next();
    row++;
  }
  bool end() { return !qmi->hasNext(); }
  QString key() { return qmi->key(); }
  size_t n_words() { return qmi->value().size(); }

 public:
  StopWords *sw;
  typedef QMap<QString, QVector<size_t>> map_words;
  map_words index;
  QMapIterator<QString, QVector<size_t>> *qmi = nullptr;

  int pos = 0, row = 0;
};
