#ifndef PP_DDEX_PARSER_H_
#define PP_DDEX_PARSER_H_

#include <napi.h>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include "schema.h"

#ifndef PP_DDEX_PARSER_SCHEMA_LOCATION
#define PP_DDEX_PARSER_SCHEMA_LOCATION "schemaLocation=\"http://ddex.net/xml/ern/"
#define PP_DDEX_PARSER_SPACE " "
#define PP_DDEX_PARSER_XML_BEG "<?xml"
#define PP_DDEX_PARSER_XML_END "?>"
#define PP_DDEX_PARSER_TAG_CLS "</"
#define PP_DDEX_PARSER_LT "<"
#define PP_DDEX_PARSER_GT ">"
#define PP_DDEX_PARSER_CL ":"
#define PP_DDEX_MESSAGE_ID_BEG "<MessageId>"
#define PP_DDEX_MESSAGE_ID_END "</MessageId>"
#endif

enum split_state_t
{
  split_state_none,
  split_state_search,
  split_state_record,
  split_state_split
};

class Parser : public Napi::ObjectWrap<Parser> {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        static void Destructor(Napi::Env env, void* nativeObject, void* finalize_hint);
        static void split_enclosed (
          const std::string& in,
          const std::string& beg,
          const std::string& end,
          std::string& out
        );
        Parser(const Napi::CallbackInfo& info);

    private:
        static Napi::FunctionReference constructor;
        Napi::Value Transform(const Napi::CallbackInfo& info);
        Napi::Function callback;
        void reset ();
        void parse (std::string& in);
        void parse_element(std::string& xml);
        split_state_t split_element (
          const std::string& el,
          std::string& in
        );
        
        std::vector<std::string> el_list;
        std::string message_id;
        std::string name;
        std::string version;
        std::string el;
        std::string in;
        split_state_t p_split_state;
        split_state_t c_split_state;
        size_t el_index_beg = 0;
        size_t el_index = 0;
};


#endif