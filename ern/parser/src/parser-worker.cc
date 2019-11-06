#include "parser-worker.h"
#include "parser.h"
#include "schema.h"
#include <iostream>
#include <string>
#include <map>

static std::map<char,int> P {
  {'P', -1},
  {'Y', 31556926},
  {'M', 2629743},
  {'D', 86400},
  {'T', -1},
};
static std::map<char,int> T {
  {'T', -1},
  {'H', 3600},
  {'M', 60},
  {'S', 1},
};

int parseDuration(const char* in)
{
  std::map<char,int> m = P;
  std::string b ("0");
  std::string str (in);
  int v = 0;
  int *y;
  for (std::string::iterator rit = str.begin(); rit != str.end(); ++rit) {
    int u =  m[*rit];
    if (u < 0) {
      if (*rit == 'T') m = T;
    } else if (u > 0) {
      // NOTE: this should not be needed, fix the bug instead
      v += std::stol(b) * (*y);
      b = "";
      y = &u;
    } else {
      b += *rit;
    }
  }
  return v;
}

void ParserWorker::parseType(const pugi::xml_node& node) {
  std::string name (node.name());
  if (types.count(name)==0) {
    writer.String(node.child_value());
    return;
  }
  std::string * type = &types[name];
  if (*type == "Bool")
    writer.Bool(node.first_child().text().as_bool());
  else if (*type == "Int")
    writer.Int(node.first_child().text().as_int());
  else if (*type == "Double")
    writer.Double(node.first_child().text().as_double());
  else if (*type == "Duration")
    writer.Int(parseDuration(node.child_value()));
  else
    writer.String(node.child_value());
}
void ParserWorker::parseType(const pugi::xml_attribute& attr) {
  std::string name (attr.name());
  if (types.count(name)==0) {
    writer.String(attr.value());
    return;
  }
  std::string * type = &types[name];
  if (*type == "Bool")
    writer.Bool(attr.as_bool());
  else if (*type == "Int")
    writer.Int(attr.as_int());
  else if (*type == "Double")
    writer.Double(attr.as_double());
  else if (*type == "Duration")
    writer.Int(parseDuration(attr.value()));
  else
    writer.String(attr.value());
}

void ParserWorker::Execute() {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml.c_str());

    if (result) {
        rapidjson::StringBuffer s;
        writer.Reset(s);
        pugi::xml_node root = doc.document_element();
        // pugi::xml_node root = doc.document_element().first_child();
        // root.append_attribute("MessageId");
        // root.attribute("MessageId").set_value(doc.document_element().attribute("MessageId").value());
        parse(root, false);
        json = s.GetString();
        s.Clear();
    } else {
      SetError(result.description());
    }

    doc.reset();
}

void ParserWorker::OnOK() {
    Napi::HandleScope scope(Env());
    Callback().Call({
        Env().Null(),
        Napi::String::New(Env(), json)
    });
}
void ParserWorker::OnError(const Napi::Error& e) {
    Napi::HandleScope scope(Env());
    Callback().Call({
        Napi::String::New(Env(), e.Message()),
        Env().Null()
    });
}

void ParserWorker::parse(pugi::xml_node &node, bool named) {
  if (named) {
    writer.StartObject();
    writer.Key(node.name());
  }

  //std::string nname;
  // std::string * type;

  // get first child to determine complex/simple type diff
  pugi::xml_node first_child = node.first_child();
  // simple type
  if (first_child.type() == pugi::node_pcdata) {
    // count attrs
    size_t attr_count = std::distance(node.attributes().begin(), node.attributes().end());
    // if has any attrs parse value is an object
    if (attr_count > 0) {
      // handle UserDefined
      pugi::xml_attribute userDefined = node.attribute("UserDefinedValue");
      if (userDefined) {
        writer.String(userDefined.value());
      } else {
        // start object
        writer.StartObject();
        // add attrs
        for (pugi::xml_attribute attr: node.attributes()) {
          writer.Key(attr.name());
          writer.String(attr.value());
        }
        // add value
        writer.Key("Value");
        parseType(node);
        
        // end object
        writer.EndObject();
      }
    // no attr, value is primitive
    } else {
      parseType(node);
    }
  // complex type
  } else {
    // start object
    writer.StartObject();
    // add attrs
    for (pugi::xml_attribute attr: node.attributes()) {
      writer.Key(attr.name());
      parseType(attr);
    }
    // add childs
    std::string pcname;
    for (pugi::xml_node child: node.children()) {
      std::string cname = child.name();
      const char *cnamec = cname.c_str();
      
      // prevent recursive children names, eg: {SoundRecording: [{SoundRecording:{...}}]}
      if (pcname != cname) {
        size_t n = std::distance(node.children(cnamec).begin(), node.children(cnamec).end());
        // sequences -> array
        if (n > 1) {
          writer.Key(cnamec);
          writer.StartArray();
          for (pugi::xml_node cchild: node.children(cnamec)) {
            parse(cchild, false);
          }
          writer.EndArray();
        } else {
          // handle DDEX4 references
          // int pos = cname.find("PartyReference");
          // if (pos > 0) {
          //   pugi::xpath_variable_set vars;
          //   vars.add("refid", pugi::xpath_type_string);
          //   pugi::xpath_query query_ref("//PartyReference[text()=string($refid)]", &vars);
          //   vars.set("refid", child.child_value());
          //   pugi::xpath_node ref_xnode = query_ref.evaluate_node(partylist.root());
          //   for (pugi::xml_node ref_node = ref_xnode.node(); ref_node; ref_node = ref_node.next_sibling())
          //   {
          //     std::string rname = ref_node.name();
          //     if (rname != "PartyReference") {
          //       writer.Key(ref_node.name());
          //       parse(writer, ref_node, false);
          //     }
          //   }
          // // no reference, simple
          // } else {
            writer.Key(cnamec);
            parse(child, false);
          // }
        }
        pcname = cname;
      }
    }

    writer.EndObject();
  }

  if (named) {
    writer.EndObject();
  }
}

