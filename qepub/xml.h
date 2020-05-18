#pragma once

#include <libxml++/libxml++.h>

#include <fstream>
#include <iostream>
#include <list>
#include <sstream>

#include "entities.h"
//
#include <QDir>
#include <QString>
#include <QStringList>

using namespace xmlpp;
using namespace std;

namespace xml {
// std funcs, stack -> return

list<string> __get_text(const Node* node);

list<string> _rget_text_list(ustring file_name);
// parameter

void _get_text(const Node* node, list<string>& text_list);
list<string> _get_text_list(ustring file_name);

// replace entities, in place
void replace_all(string& subject, const string& search, const string& replace);
string replace_entities(string file_name);

// qt funcs

QString get_qtext(QString file_name, QString sep = "");
QStringList get_qlist(QString file_name);
QString get_folder_text(QString folder);
}  // namespace xml
