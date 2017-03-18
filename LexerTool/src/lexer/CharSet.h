/*
 * CharSet.h
 *
 *  Created on: 17 Mar 2017
 *      Author: uri
 */

#ifndef LEXER_CHARSET_H_
#define LEXER_CHARSET_H_

#include "LexerTypes.h"
#include <cassert>
#include <vector>
#include <utility>

namespace Lexer {

class CharSet final{
public:
	~CharSet() {};

	bool has(Char c) const;

	static CharSet make(Char c);
	static CharSet make(Char c0,Char c1);
private:
	typedef std::pair<Char,Char> CP;
	typedef std::vector<CP>      CPV;
	CPV r;
	friend CharSet operator+(const CharSet& s0,const CharSet& s1); //set union


	CharSet(Char c);
	CharSet(Char c0,Char c1);
	CharSet(const CPV& r);
};

CharSet operator+(const CharSet& s0,const CharSet& s1); //set union
CharSet operator-(const CharSet& s0,const CharSet& s1); //set difference
CharSet operator*(const CharSet& s0,const CharSet& s1); //set intersection

} /* namespace Lexer */

#endif /* LEXER_CHARSET_H_ */
