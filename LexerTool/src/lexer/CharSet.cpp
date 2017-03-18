/*
 * CharSet.cpp
 *
 *  Created on: 17 Mar 2017
 *      Author: uri
 */

#include "CharSet.h"
#include <algorithm>
#include <utility>

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
inline CPV::const_iterator& selectMin(const CPV& r0,const CPV& r1,CPV::const_iterator& i0,CPV::const_iterator& i1){
	assert(i0!=r0.end() || i1!=r1.end());
	return (i1==r1.end() || i0->first<=i1->first) ? i0 : i1;
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
			auto& i = selectMin(r0, r1, i0, i1);
			l = i->first;
			h = i->second;
			i++;
		}
		while (true){
			auto& i = selectMin(r0, r1, i0, i1);
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

/*


bool unionCheckAddRange(Char& h, unsigned int& i,const CPV& r){
	if (i<r.size() && h+1>=r[i].first)
	{
		h = max(h,r[i].second);
		i++;
		return true;
	}
	return false;
}

CharSet operator+(const CharSet& s0,const CharSet& s1){ //set union
	CPV v;
	const CPV* rs[2] = {&s0.r,&s1.r};
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
/ *				if (is[k]<rs[k]->size() && h+1>=(*rs[k])[is[k]].first)
				{
					h = max(h,(*rs[k])[is[k]].second);
					is[k]++;
					stop=false;
				}* /
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
*/
CharSet operator-(const CharSet& s0,const CharSet& s1); //set difference
CharSet operator*(const CharSet& s0,const CharSet& s1); //set intersection

} /* namespace Lexer */
