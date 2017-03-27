/*
 * unicode.cpp
 *
 *  Created on: 21 Mar 2017
 *      Author: uri
 */

#include "unicode.h"
#include <codecvt>
#include <locale>

namespace Lexer{
static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> u8c;
std::string u8(const char16_t c16){ return u8c.to_bytes(c16); }
std::string u8(const char32_t c32){ return u8c.to_bytes(c32); }
}


