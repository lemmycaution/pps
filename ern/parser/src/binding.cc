#include <napi.h>
#include "parser.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Parser::Init(env, exports);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)