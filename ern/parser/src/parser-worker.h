#ifndef PP_DDEX_PARSER_WORKER_H_
#define PP_DDEX_PARSER_WORKER_H_

#include<napi.h>
#include "pugixml/pugixml.hpp"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class ParserWorker : public Napi::AsyncWorker {
    public:
        ParserWorker(Napi::Function& callback, std::string& xml)
        : Napi::AsyncWorker(callback), xml(xml), json("") {};

        ~ParserWorker() {};

    void Execute();

    void OnOK();
    void OnError(const Napi::Error& e);

    private:
        std::string xml;
        std::string json;
        rapidjson::Writer<rapidjson::StringBuffer, rapidjson::UTF8<>, rapidjson::UTF8<>> writer;
        void parse(pugi::xml_node &node, bool named = true);
        void parseType(const pugi::xml_node& node);
        void parseType(const pugi::xml_attribute& attr);
};

#endif