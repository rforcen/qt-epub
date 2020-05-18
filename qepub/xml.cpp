#include "xml.h"

list<string> xml::__get_text(const Node* node) {
  const auto nodeContent = dynamic_cast<const ContentNode*>(node);
  const auto nodeText = dynamic_cast<const TextNode*>(node);

  list<string> ls;
  if (!(nodeText && nodeText->is_white_space())) {
    if (nodeText) ls.push_back(nodeText->get_content());
    if (!nodeContent)  // Recurse through child nodes:
      for (const auto& child : node->get_children()) {
        auto _l = __get_text(child);  // recursive
        ls.insert(ls.begin(), _l.begin(), _l.end());
      }
  }
  return ls;
}

list<string> xml::_rget_text_list(ustring file_name) {
  DomParser parser;
  parser.parse_memory(replace_entities(file_name));

  list<string> text;
  if (parser) text = __get_text(parser.get_document()->get_root_node());
  text.reverse();
  return text;
}

// text list parameter -> faster

void xml::_get_text(const Node* node, list<string>& text_list) {
  const auto nodeText = dynamic_cast<const TextNode*>(node);

  if (!(nodeText && nodeText->is_white_space())) {
    if (nodeText)
      text_list.push_back(nodeText->get_content());
    else  // Recurse through child nodes:
      for (const auto& child : node->get_children())
        _get_text(child, text_list);  // recursive
  }
}

list<string> xml::_get_text_list(ustring file_name) {
  DomParser parser;
  parser.parse_memory(replace_entities(file_name));

  list<string> text;
  if (parser) _get_text(parser.get_document()->get_root_node(), text);
  return text;
}

// replace entities, in place
void xml::replace_all(string& subject, const string& search,
                      const string& replace) {
  for (size_t pos = 0; ((pos = subject.find(search, pos)) != string::npos);
       pos += replace.length())
    subject.replace(pos, search.length(), replace);
}

// from entities list
string xml::replace_entities(string file_name) {
  ifstream _ifs(file_name);  // file -> string
  string s((istreambuf_iterator<char>(_ifs)), istreambuf_iterator<char>());

  for (auto& he : htmlEntitiesTable)  // "&nbsp;", "&#160;"
    replace_all(s, "&" + string(he.name) + ";",
                "&#" + to_string(he.value) + ";");

  return s;
}

// qt funcs

QString xml::get_qtext(QString file_name, QString sep) {
  QString s;
  for (auto& l : _get_text_list(file_name.toStdString()))
    s.append(QString::fromStdString(l) + sep);
  return s;
}

QStringList xml::get_qlist(QString file_name) {
  QStringList sl;
  for (auto& l : _get_text_list(file_name.toStdString()))
    sl.append(QString::fromStdString(l));
  return sl;
}

QString xml::get_folder_text(QString folder) {
  QString content;
  for (auto& d : QDir(folder).entryInfoList({"*.xhtml"}))
    content.append(get_qtext(d.filePath(), " "));
  return content;
}
