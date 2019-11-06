#include "parser.h"
#include "parser-worker.h"
#include <iostream>

Napi::FunctionReference Parser::constructor;

Napi::Object Parser::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    Napi::Function parser = DefineClass(
                              env,
                              "Parser",
                              { InstanceMethod("transform", &Parser::Transform) }
                            );

    constructor = Napi::Persistent(parser);
    constructor.SuppressDestruct();

    exports.Set("Parser", parser);
    return exports;
}

Parser::Parser(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<Parser>(info)
{
  el_index_beg = 0;
  el_index = 0;
}

void Parser::reset() {
  el_list.erase(el_list.begin(), el_list.end());
  message_id.erase();
  name.erase();
  version.erase();
  el.erase();
  // buf.erase();
  p_split_state = split_state_none;
  c_split_state = split_state_none;
  el_index_beg = 0;
  el_index = 0;
}

Napi::Value Parser::Transform(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    callback = info[1].As<Napi::Function>();

    //Napi::Buffer<char> input = info[0].As<Napi::Buffer<char>>();
    //std::string b(input.Data(), input.Length());
    in += info[0].ToString();
    parse(in);

    return env.Undefined();
}

void Parser::parse (std::string& in)
{
  size_t eox_pos;

  // in = buf + in;
  // buf.empty();

  if ( el_list.empty() )
  {
    split_enclosed(in,
                  PP_DDEX_PARSER_SCHEMA_LOCATION,
                  PP_DDEX_PARSER_SPACE,
                  version);
    if ( version.empty() )
    {
      goto next;
    }

    split_enclosed(in, PP_DDEX_PARSER_XML_END, PP_DDEX_PARSER_SPACE, name);
    if ( name.empty() )
    {
      goto next;
    }
    else
    {
      size_t nsp;
      if ( (nsp = name.find(PP_DDEX_PARSER_LT)) != std::string::npos )
      {
        name = name.substr(nsp + 1);
      }
      if ( (nsp = name.find(PP_DDEX_PARSER_CL)) != std::string::npos )
      {
        name = name.substr(nsp + 1);
      }
    }
    
    if (name.empty()) {
      callback({
          Napi::String::New(Env(), "schema for name not found: " + name),
          Env().Null()
        });
        reset();
        goto next;
    }

    if (schema.count(version) > 0)
    {
      if (schema[version].count(name) > 0)
      {
          el_list = schema[version][name];
      }
      else
      {
        callback({
          Napi::String::New(Env(), "schema for name not found: " + name),
          Env().Null()
        });
        reset();
        goto next;
      }
    }
    else
    {
      callback({
        Napi::String::New(Env(), "schema for version not found: " + version),
        Env().Null()
      });
      reset();
      goto next;
    }

  }

  if ( message_id.empty() )
  {
    split_enclosed(in, PP_DDEX_MESSAGE_ID_BEG, PP_DDEX_MESSAGE_ID_END, message_id);
    if ( message_id.empty() )
    {
      goto next;
    }
  }

  for(el_index = el_index_beg; el_index < el_list.size(); el_index++)
  {
    el = el_list[el_index];

    c_split_state = split_element(el, in);

    switch(c_split_state)
    {
      case split_state_none:
      {
        // if (p_split_state == 3)
        // {
        //   el_index_beg = el_index + 1;
        //   p_split_state = c_split_state;
        goto next;
        // }
        // break;
      }
      case split_state_search:
      {
        break;
      }
      case split_state_record:
      {
        el_index_beg = el_index;
        break;
      }
      case split_state_split:
      {
        el_index_beg = el_index;
        continue;
      }
    }

    // p_split_state = c_split_state;
  }

  next:
  if (!el_list.empty() && ((eox_pos = in.find(PP_DDEX_PARSER_XML_BEG)) != std::string::npos)) {
    reset();
    // if (eox_pos != in.find(PP_DDEX_PARSER_XML_END, eox_pos) != std::string::npos)
    in = in.substr(eox_pos);
  }
  // buf = in;
}

void Parser::parse_element (std::string& xml) {
  ParserWorker* asyncWorker = new ParserWorker(callback, xml);
  asyncWorker->Queue();
}

split_state_t Parser::split_element (
  const std::string& el,
  std::string& in
) {
  split_state_t split_state = split_state_none;

  std::string beg = "<" + el;
  size_t beg_len = beg.length();

  if ( beg_len > in.length() )
    return split_state;

  split_state = split_state_search;

  size_t beg_pos;
  char beg_end_char;

  std::string end = "</" + el + ">";
  size_t end_len = end.length();
  size_t end_pos;

  size_t pos = 0;

  while ( (beg_pos = in.find(beg, pos)) != std::string::npos )
  {
    beg_end_char = in[beg_pos + beg_len];
    if ( beg_end_char != '>' && beg_end_char != ' ' )
    {
      pos = beg_pos + beg_len;
      continue;
    }
    pos = 0;
    if ( (end_pos = in.find(end, beg_pos)) != std::string::npos )
    {
      end_pos += end_len;
      std::string frag;
      // if (el != "MessageHeader") {
      //   if(parent.empty()) {
      //     beg_pos = in.find(">", beg_pos) + 1;
      //     frag = PP_DDEX_PARSER_LT + el + PP_DDEX_PARSER_GT + PP_DDEX_MESSAGE_ID_BEG + message_id + PP_DDEX_MESSAGE_ID_END + in.substr(beg_pos, end_pos - beg_pos - end_len) + PP_DDEX_PARSER_TAG_CLS + el + PP_DDEX_PARSER_GT;
      //   } else {
      //     frag = PP_DDEX_PARSER_LT + parent + PP_DDEX_PARSER_GT + PP_DDEX_MESSAGE_ID_BEG + message_id + PP_DDEX_MESSAGE_ID_END + in.substr(beg_pos, end_pos - beg_pos) + PP_DDEX_PARSER_TAG_CLS + parent + PP_DDEX_PARSER_GT;
      //   }
      // } else {
      //   frag = in.substr(beg_pos, end_pos - beg_pos);
      // }
      //frag = "<root message_id=\"" + message_id + "\" parent=\"" + parent + "\">" + in.substr(beg_pos, end_pos - beg_pos) + "</root>";

      //frag = "<Message MessageVersion=\"" + version + "\" MessageType=\"" + name + "\" MessageId=\"" + message_id + "\"><Data>" + in.substr(beg_pos, end_pos - beg_pos) + "</Data></Message>";

      frag = in.substr(beg_pos, end_pos - beg_pos);

      parse_element(frag);
      // callback({Env().Null(), Napi::String::New(Env(), frag)});

      in = in.substr(end_pos);
      split_state = split_state_split;
    }
    else
    {
      in = in.substr(beg_pos);
      split_state = split_state_record;
      break;
    }
  }

  return split_state;
}

void Parser::split_enclosed (
  const std::string& _in,
  const std::string& beg,
  const std::string& end,
  std::string& out
) {
  std::string in(_in);

  size_t bpos = in.find(beg);
  if ( bpos != std::string::npos )
      bpos += beg.length();
  else
    return;

  size_t epos = in.find(end, bpos);
  if ( epos != std::string::npos )
    out = in.substr(bpos, epos - bpos);
}