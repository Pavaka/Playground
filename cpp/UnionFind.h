#pragma once
#include <vector>
#include <cassert>
#include <unordered_map>

namespace pavakalib
{
template<typename T>
class UnionFind
{
public:
	// Make oprations might invalidate found values
	void MakeSet(const T& el)
	{
		assert(m_Elements.size() == m_Parents.size());
		m_Elements.push_back(Element{ el, 1 });
		m_Parents.insert(std::make_pair(el, unsigned(m_Elements.size() - 1)));
	}

	const T* FindSetRepresentative(const T& el)
	{
		auto currElementToParent = m_Parents.find(el);
		assert(currElementToParent != m_Parents.end());
		auto& parentEl = m_Elements[currElementToParent->second].Value;
		if (el == parentEl)
		{
			return &parentEl;
		}
		auto rep = FindSetRepresentative(parentEl);
		m_Parents[el] = m_Parents[*rep];
		return rep;

	}
	void UnionSets(const T& s1, const T& s2)
	{
		auto rep1 = FindSetRepresentative(s1);
		auto rep2 = FindSetRepresentative(s2);
		if (rep1 != rep2)
		{
			auto& rep1ParentIdx = m_Parents[*rep1];
			auto& rep2ParentIdx = m_Parents[*rep2];
			auto& el1 = m_Elements[rep1ParentIdx];
			auto& el2 = m_Elements[rep2ParentIdx];
			if (el1.TreeSize <= el2.TreeSize)
			{
				el2.TreeSize += el1.TreeSize;
				rep1ParentIdx = rep2ParentIdx;
			}
			else
			{
				el1.TreeSize += el2.TreeSize;
				rep2ParentIdx = rep1ParentIdx;
			}
		}
	}
private:
	struct Element
	{
		T Value;
		unsigned TreeSize;
	};
	std::vector<Element> m_Elements;
	// the parent of i-th element
	std::unordered_map<T, unsigned> m_Parents;
};
}