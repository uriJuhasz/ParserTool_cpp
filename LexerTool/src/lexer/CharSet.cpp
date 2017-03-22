/*
 * CharSet.cpp
 *
 *  Created on: 17 Mar 2017
 *      Author: uri
 */

#include "CharSet.h"
#include <algorithm>
#include <utility>
#include "unicode.h"

namespace Lexer {

	bool CharSet::has(Char c) const{//todo binary search
		auto i=r.begin();
		while (i!=r.end() && i->second<c)
			i++;
		return i!=r.end() && c>=i->first && c<=i->second;
	}

	CharSet::CharSet() : CharSet(CPV()){}
	CharSet::CharSet(Char c) : CharSet(c,c){}
	CharSet::CharSet(Char c0,Char c1) : CharSet(CPV{CP(c0,c1)})
	{
		assert(c0<=c1);
	}
	CharSet::CharSet(const CPV& r) : r(r)
	{
#ifdef DEBUG
		if (r.size()>0){
			int i=0; Char lh;
			for (auto p : r){
				assert (p.first<=p.second);
				if (i>0) assert (lh+1<p.first);
				i++; lh = p.second;
			}
		}
#endif
	}


CharSet CharSet::make(){return CharSet();}
CharSet CharSet::make(Char c){return CharSet(c);}
CharSet CharSet::make(Char c0,Char c1){return CharSet(c0,c1);}


template<typename T>inline T max(T c0,T c1){
	return c0>c1 ? c0 : c1;
}
template<typename T>inline T min(T c0,T c1){
	return c0<c1 ? c0 : c1;
}

typedef std::pair<Char,Char> CP;
typedef std::vector<CP>      CPV;

/*inline void CharSetUnionSetStart(Char& l, Char& h, CPV::const_iterator& it){
	l = it->first();
	h = it->second();
	it++;
}
*/
inline CPV::const_iterator* selectMin(const CPV& r0,const CPV& r1,CPV::const_iterator& i0,CPV::const_iterator& i1){
	assert(i0!=r0.end() || i1!=r1.end());
	return (i1==r1.end() ) ? &i0 : (i0==r0.end()) ? &i1 : (i0->first<=i1->first) ? &i0 : &i1;
}
CharSet operator+(const CharSet& s0,const CharSet& s1){ //set union
	const CPV& r0 = s0.r;
	const CPV& r1 = s1.r;

	auto i0 = r0.begin();
	auto i1 = r1.begin();

	CPV v;
	while (i0!=r0.end() || i1!=r1.end()){
		Char l,h;
		{
			auto& i = *selectMin(r0, r1, i0, i1);
			l = i->first;
			h = i->second;
			i++;
		}
		while (i0!=r0.end() || i1!=r1.end()){
			auto& i = *selectMin(r0, r1, i0, i1);
			if (i->first<=h+1){ //merge
				h = max(h,i->second);
				i++;
			}else
				break;
		}
		v.push_back(CP(l,h));
	}

	return CharSet(v);
}
CharSet operator*(const CharSet& s0,const CharSet& s1){ //set intersection
	const CPV& r0 = s0.r;
	const CPV& r1 = s1.r;

	auto i0 = r0.begin();
	auto i1 = r1.begin();

	CPV v;
	while (i0!=r0.end() && i1!=r1.end()){
		//invariant forall j0<i0 : ((r0[j0] intersect r1) in v)
		//invariant i1==r1.end \/ forall j1<i1 : j1->second<i1->first
		while (i1!=r1.end() && i1->second<i0->first)
			i1++;
		//invariant i1==r1.end \/ (i1->second>=i1->first && forall j1<i1 : j1->second<i1->first)
		while (i1!=r1.end() && i1->first<=i0->second){
			//invariant i1==r1.end \/
			//  (i1->second>=i0->first
			//    &&
			//	forall j1<i1 :
			//		j1->second<i1->first \/ (j1 \cap i1 \in v))
			auto l = max(i0->first,i1->first);
			auto h = min(i0->second,i1->second);
			if (l<=h)
				v.push_back(CP(l,h));
			if (i1->second<=i0->second)
				i1++;
			else
				break;
		}
		i0++;
	}
	return CharSet(v);
}

CharSet operator-(const CharSet& s0,const CharSet& s1){ //set difference
	const CPV& r0 = s0.r;
	const CPV& r1 = s1.r;

	auto i0 = r0.begin();
	auto i1 = r1.begin();

	CPV v;
	for (i0=r0.begin();i0!=r0.end();i0++){
		//invariant forall j0<i0 : ((r0[j0] \setminus r1) in v)
		//invariant i1==r1.end || forall j1<i1 : j1->second<i1->first
		while (i1!=r1.end() && i1->second<i0->first)
			i1++;
		//invariant i1==r1.end || (i1->second>=i0->first && forall j1<i1 : j1->second<i1->first)
		auto l = i0->first;
		auto h = i0->second;

		if (i1!=r1.end() && i1->first<=i0->first)
		{
			assert(i1->second>=i0->first);
			if (i1->second>=i0->second)
				continue;
			assert(i1->second<i0->second);
			l = i1->second+1;
			i1++;
		}
		//invariant i1==r1.end() || i1->first>i0.first
		assert (l<=h);
		while (true){
			assert (i1==r1.end() || i1->first>i0->first);
			assert (i1==r1.end() || l<i1->first);
			assert (i1==r1.end() || i1->first>l);
			assert (h<=i0->second);
			if  (i1!=r1.end() && i1->first<=i0->second){
				h = i1->first-1;
				assert(l<=h);
				v.push_back(CP(l,h));
				if (i1->second<i0->second){
					l = i1->second+1;
					i1++;
				}else
					break;
			}else{
				h = i0->second;
				assert(l<=h);
				v.push_back(CP(l,h));
				break;
			}
		};
	}
	return CharSet(v);
}
#include <ostream>

std::wostream& operator<<(std::wostream& os, const CharSet& s){ //print
	os << "{";
	for (auto p : s.r)
		if (p.first==p.second)
			os << p.first;
		else{
			os << "[";
			os << p.first;
			os << "-";
			os << p.second;
			os << "]";
		}
	os << "}";
	return os;
}

std::ostream& operator<<(std::ostream& os, const CharSet& s){ //print
	os << "{";
	for (auto p : s.r)
		if (p.first==p.second)
			os << u8(p.first);
		else{
			os << "[";
			os << u8(p.first);
			os << "-";
			os << u8(p.second);
			os << "]";
		}
	os << "}";
	return os;
}

} /* namespace Lexer */
