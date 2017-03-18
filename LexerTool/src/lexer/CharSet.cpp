/*
 * CharSet.cpp
 *
 *  Created on: 17 Mar 2017
 *      Author: uri
 */

#include "CharSet.h"
#include <algorithm>

namespace Lexer {

	bool CharSet::has(Char c) const{//todo binary search
		unsigned int i=0;
		while (i<r.size() && c<r[i].first)
			i++;
		return i!=r.size() && c<=r[i].second;
	}

	CharSet::CharSet(Char c) : CharSet(c,c){}
	CharSet::CharSet(Char c0,Char c1) : CharSet(CPV{CP(c0,c1)})
	{
		assert(c0<=c1);
	}
	CharSet::CharSet(const CPV& r) : r(r)
	{
#ifdef DEBUG
		assert(r.size()>0);
/*		assert(all_of(r.begin(),r.end(),[b=true,lh=r[0].first](CP cp)mutable{
			auto t = cp.first<=cp.second && (b || lh+1<cp.first);
			b=false;
			return t;}));*/

//		assert(all_of(r.begin(),r.end(),[](CP cp){cp.first<=cp.second;}));
		int i=0; Char lh;
		for (auto p : r){
			assert (p.first<=p.second);
			if (i>0) assert (lh+1<p.first);
			i++; lh = p.second;
		}
/*		for (auto i=0;i<r.size();i++)
		{
			const CP& p=r[i];
			assert (p.first<=p.second);
			if (i>0)
				assert (lastHigh+1 < p.first);
			lastHigh = p.second;
		}*/
#endif
	}


CharSet CharSet::make(Char c){return CharSet(c);}
CharSet CharSet::make(Char c0,Char c1){return CharSet(c0,c1);}


static Char max(Char c0,Char c1){
	return c0>c1 ? c0 : c1;
}


bool unionCheckAddRange(Char& h, unsigned int& i,const CharSet::CPV& r){
	if (i<r.size() && h+1>=r[i].first)
	{
		h = max(h,r[i].second);
		i++;
		return true;
	}
	return false;
}

CharSet operator+(const CharSet& s0,const CharSet& s1){ //set union
	CharSet::CPV v;
	const CharSet::CPV* rs[2] = {&s0.r,&s1.r};
	unsigned int is[2] = {0,0};
	while (is[0]<rs[0]->size() && is[1]<rs[1]->size())
	{
		auto l0 = (*rs[0])[is[0]].first;
		auto l1 = (*rs[1])[is[1]].first;

		auto s = (l0<l1) ? 0 : 1;

		Char l = (*rs[s])[is[s]].first;
		Char h = (*rs[s])[is[s]].second;
		is[s]++;

		auto cont = false;
		do {
			cont = false;
			for (auto k=0;k<2;k++)
				cont |= unionCheckAddRange(h, is[k], *rs[k]);
/*				if (is[k]<rs[k]->size() && h+1>=(*rs[k])[is[k]].first)
				{
					h = max(h,(*rs[k])[is[k]].second);
					is[k]++;
					stop=false;
				}*/
		}while (cont);
		v.push_back(CharSet::CP(l,h));
	}
	for (auto i=0;i<2;i++)
		while (is[i]<rs[i]->size()){
			v.push_back((*rs[i])[is[i]]);
			is[i]++;
		}
	return CharSet(v);
}
CharSet operator-(const CharSet& s0,const CharSet& s1); //set difference
CharSet operator*(const CharSet& s0,const CharSet& s1); //set intersection



/*
CharSet::CharSet() {
}

CharSet::~CharSet() {}

class SingletonCharSet final : public CharSet{
public:
	bool has (Char k) const override{return c==k;}
	const Char c;
private:
	SingletonCharSet(Char c) : c(c){}
};
class RangeCharSet final : public CharSet{
public:
	bool has (Char k) const override{return k>=c0 && k<=c1;}
	const Char c0,c1;
private:
	RangeCharSet(Char c0,Char c1) : c0(c0), c1(c1){ assert(c0 < c1);}
};
class RangesCharSet final : public CharSet{
public:
	RangesCharSet(const vector<pair<Char,Char>>& rs) : rs(rs){

	}
	bool has (Char k) const override{return s0.has(k) || s1(has(k)); }
	const vector<pair<Char,Char>> rs;
};


*/
} /* namespace Lexer */
