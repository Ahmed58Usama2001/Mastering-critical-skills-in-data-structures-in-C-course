#include<iostream>
#include<vector>
using namespace std;


class Trie {

private:

	static const int MAX_CHAR = 26;
	Trie* child[MAX_CHAR];
	bool is_leaf{};


public:

	Trie()
	{
		memset(child, 0, sizeof(child));
	}

	void insert(string str, int idx = 0)
	{
		if (idx == str.size())
			is_leaf = true;
		else
		{
			int cur = str[idx] - 'a';
			if (child[cur] == 0)
				child[cur] = new Trie();
			child[cur]->insert(str, idx + 1);
		}
	}

	bool word_exist(string str, int idx = 0)
	{
		if (idx == str.size())
			return is_leaf;
		
			int cur = str[idx] - 'a';
			if (!child[cur])
				return false;
		
			return child[cur]->word_exist(str, idx + 1);

	}

	bool prefix_exist(string str, int idx = 0)
	{
		if (idx == str.size())
			return true;

		int cur = str[idx] - 'a';
		if (!child[cur])
			return false;

		return child[cur]->prefix_exist(str, idx + 1);

	}

	void iterative_insert(string str) {
		Trie* cur_trie =this ;

		for (int idx = 0; idx < str.size(); idx++) {
			int cur = str[idx] - 'a';
			if (cur_trie->child[cur] == 0)
				cur_trie->child[cur] = new Trie();
			cur_trie = cur_trie->child[cur];
		}
		cur_trie->is_leaf = true;
	}

	bool iterative_word_exist(string str)
	{
		Trie* cur_trie = this;

		for (int idx = 0; idx < str.size(); idx++) {
			int cur = str[idx] - 'a';
			if (!cur_trie->child[cur])
				return false;
			cur_trie = cur_trie->child[cur];
		}
		return cur_trie->is_leaf;
	}

	string first_word_prefix(const string& str)
	{
		Trie* cur = this;
		for (int i = 0; i < str.size(); i++)
		{
			int ch = str[i] - 'a';

			if (cur->child[ch])
			{
				if (cur->child[ch]->is_leaf)
					return str.substr(0, i + 1);
			}
			else
				return "doesn't exist";

			cur = cur->child[ch];
		}

	}

	void get_all_strings(vector<string>& res, string str = "")
	{
		if (is_leaf)
			res.push_back(str);

		for (int i=0;i<MAX_CHAR;i++)
		{	
			if (child[i])
				child[i]->get_all_strings(res,str+(char)(i+'a'));
		
		}
	}

	void auto_complete(const string& str, vector<string>& res, int idx = 0, string cur_str = "")
	{
		
		if (idx < str.size())
		{
		
			child[str[idx]-'a']->auto_complete(str, res, idx + 1, cur_str + str[idx]);
			
		}
		
		else
		{
			
			
			if(is_leaf)
			res.push_back(cur_str);

			for (int i = 0; i < MAX_CHAR; i++)
			{
				if (child[i])
					child[i]->auto_complete(str, res, str.size(), cur_str + (char)(i + 'a'));
			}
		}
	}

	void iterative_auto_complete(const string& str, vector<string>& res) {
		Trie* cur = this;

		for (int idx = 0; idx < (int)str.size(); ++idx) {
			int ch = str[idx] - 'a';
			if (!cur->child[ch])
				return;
			cur = cur->child[ch];
		}
		cur->get_all_strings(res, str);
	}

	bool word_exist_with_1_change_1st(string str)  
	{//O(NL)-->N is the number of words in my dictionary
		vector<string>res;
		this->get_all_strings(res);

		for (int i = 0; i < res.size(); i++)
		{
			int chg = 0;
			for (int ch = 0; ch <(int)min( res[i].size(),str.size()); ch++)
			{
				if (str[ch] != res[i][ch])
					chg++;
				if (chg > 1)
					break;
			}
			if (chg == 1&&res[i].size()==str.size())
				return true;
		}

		return false;
	}

	bool word_exist_with_1_change_2nd(string str) {
		// Brute force all possible 1-char change and search for it
		// O(L * 26 * L)
		for (int i = 0; i < (int)str.size(); ++i) {
			char cpy = str[i];
			for (char ch = 'a'; ch <= 'z'; ch++) {
				if (ch == cpy)	// Must do a change
					continue;
				str[i] = ch;
				if (word_exist(str))
					return true;
			}
			str[i] = cpy;	// copy back
		}
		return false;
	}

};

class MagicDictionary {
public:
	Trie tree;

	MagicDictionary() {

	}

	void buildDict(vector<string> dictionary) {
		for (int i = 0; i < (int)dictionary.size(); ++i) {
			tree.insert(dictionary[i]);
		}

	}

	bool search(string str) {
		return tree.word_exist_with_1_change_1st(str);
	}
};

int main()
{
	MagicDictionary magicDictionary;

	magicDictionary.buildDict({ "hello", "leetcode" });

	cout << magicDictionary.search("hello"); // return False
	cout << magicDictionary.search("hhllo"); // We can change the second 'h' to 'e' to match "hello" so we return True
	cout << magicDictionary.search("hell"); // return False
	cout << magicDictionary.search("leetcoded"); // return False

	return 0;
}