#pragma once
#include <string>
#include <vector>
#include <memory>
#include <queue>
namespace pavakalib
{

class Trie
{
public:
	Trie()
		: Head(std::make_unique<TrieNode>())
	{}

	bool Insert(const std::string& str)
	{
		TrieNode* currNode = Head.get();
		const int INVALID_IDX = -1;
		int failedLetterIdx = INVALID_IDX;
		for (int i = 0; i < str.size(); ++i)
		{
			TrieNode* nextNode = Transition(currNode, str[i]);
			if (nextNode)
			{
				currNode = nextNode;
			}
			else
			{
				failedLetterIdx = i;
				break;
			}
		}

		// No failed letter, the word is in the trie so no insertio occured
		if (failedLetterIdx == INVALID_IDX)
			return false;

		for (int i = failedLetterIdx; i < str.size(); ++i)
		{
			currNode = AddTransition(currNode, str[i]);
		}
		currNode->IsEndOfWord = true;
		return true;
	}

	bool HasWord(const std::string& str) const
	{
		const TrieNode* currNode = Head.get();
		int letterIdx = 0;
		for (;letterIdx < str.size(); ++letterIdx)
		{
			currNode = Transition(currNode, str[letterIdx]);
			if (!currNode)
			{
				return false;
			}
		}
		return currNode->IsEndOfWord;
	}

	void Print()
	{
		struct NodeLvlPair
		{
			TrieNode* Node;
			int Level;
		};
		std::queue<NodeLvlPair> q;
		q.push(NodeLvlPair{ Head.get(), 0 });
		while (!q.empty())
		{
			auto currNode = q.front();
			q.pop();
			for (auto& trans : currNode.Node->Transitions)
			{
				std::cout << trans.Letter << ' ';
				q.push(NodeLvlPair{ trans.Node.get(), currNode.Level + 1 });
			}
			if (q.empty() || currNode.Level != q.front().Level)
			{
				std::cout << '\n';
			}
		}
	}
private:
	struct TrieNode
	{
		struct Transition
		{
			std::unique_ptr<TrieNode> Node;
			char Letter;
		};
		std::vector<Transition> Transitions;
		bool IsEndOfWord = false;;
	};

	static TrieNode* AddTransition(TrieNode* node, char letter)
	{
		node->Transitions.push_back(TrieNode::Transition{ std::make_unique<TrieNode>(), letter });
		return node->Transitions.back().Node.get();
	}

	static TrieNode* Transition(const TrieNode* node, char letter)
	{
		for (auto& trans : node->Transitions)
		{
			if (trans.Letter == letter)
			{
				return trans.Node.get();
			}
		}
		return nullptr;
	}

	std::unique_ptr<TrieNode> Head;
};
}