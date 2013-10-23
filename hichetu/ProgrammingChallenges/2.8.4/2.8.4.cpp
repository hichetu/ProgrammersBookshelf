// 2.8.4.cpp : http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110204&format=html
//

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <bitset>
#include <set>
using namespace std;

class Enigma
{
public:
	void SetDictionary(const vector<string>& dictionary)
	{
		dictionary_ = dictionary;
		mapLengthToDictionaryStrings_.clear();

		for(size_t i=0; i<dictionary.size(); ++i)
		{
			mapLengthToDictionaryStrings_[dictionary[i].size()].insert(dictionary[i]);
		}
	}

	string Decrpyt(const string& message)
	{
		Clear();
		BuildWords(message);

		DecrpyptInPasses();

		return Decode();;
	}

private:
	void BuildWords(const string& message)
	{
		stringstream stream(message);

		while(stream.good())
		{
			string word;
			stream >> word;
			inputWords_.push_back(word);
			mapCipher_[word] = mapLengthToDictionaryStrings_[word.size()];

			if(mapCipher_[word].size() == 1)
			{
				MapChars(word, *(mapCipher_[word].begin()));
			}
		}
	}

	void Clear()
	{
		inputWords_.clear();
		mapChars_.clear();
		mapCipher_.clear();
	}

	string Decode()
	{
		string secret;

		if(!inputWords_.size()) return false;

		if(mapCipher_[inputWords_[0]].size() != 1) return string();
		secret += *(mapCipher_[inputWords_[0]].begin());

		for(size_t i=1; i<inputWords_.size(); ++i)
		{
			secret += " ";
			if(mapCipher_[inputWords_[i]].size() != 1) return string();
			secret += *(mapCipher_[inputWords_[i]].begin());
		}

		return secret;
	}

	void DecrpyptInPasses()
	{
		bool fProgress = true;

		while(fProgress)
		{
			fProgress = false;

			for(map<string, set<string> >::iterator iter = mapCipher_.begin(); iter != mapCipher_.end(); ++iter)
			{
				bool progress = DecodeCipher(iter);

				if(progress)
				{
					fProgress = true;
				}
			}
		}
	}

	bool DecodeCipher(map<string, set<string> >::iterator& iter)
	{
		if(iter->second.size() == 1) return false;

		bool fProgress = false;

		const string& code = iter->first;
		set<string>& setTargets = iter->second;

		for(size_t i=0; i<code.size(); ++i)
		{
			if(mapChars_.find(code[i]) != mapChars_.end())
			{
				for(set<string>::iterator setIter = setTargets.begin(); setIter != setTargets.end(); )
				{
					const string& strTarget = *setIter;

					if(mapChars_[code[i]] != strTarget[i])
					{
						set<string>::iterator eraseIter = setIter;
						++setIter;
						setTargets.erase(eraseIter);
						fProgress = true;
					}
					else
					{
						++setIter;
					}
				}
			}
		}

		if(setTargets.size() == 1)
		{
			MapChars(code, *(setTargets.begin()));
		}

		return fProgress;
	}

	void MapChars(const string& code, const string& target)
	{
		for(size_t i=0; i<code.size(); ++i)
		{
			mapChars_[code[i]] = target[i];
		}
	}

private:
	vector<string> dictionary_;
	vector<string> inputWords_;
	map< size_t, set<string> > mapLengthToDictionaryStrings_;
	map<char, char> mapChars_;
	map<string, set<string>> mapCipher_;

};

class Problem
{
public:
	void Solve()
	{
		ReadDictionary();

		while(ReadEncryptedInputs())
		{
			DecryptCipher();
			PrintTheSecret();
		}
	}

	void ReadDictionary()
	{
		string line;
		getline(cin, line);

		size_t dictionarySize = 0;
		stringstream stream(line);
		stream >> dictionarySize;

		vector<string> dictionary(dictionarySize);

		for(size_t i=0; i<dictionarySize; ++i)
		{
			string line;
			getline(cin, line);
			dictionary.push_back(line);
		}

		enigma_.SetDictionary(dictionary);
	}

	bool ReadEncryptedInputs()
	{
		encrpytedLine_.clear();
		getline(cin, encrpytedLine_);

		if(cin.bad()) return false;
		if(encrpytedLine_.empty()) return false;

		return true;
	}

	void DecryptCipher()
	{
		theSecret_ = enigma_.Decrpyt(encrpytedLine_);
	}

	void PrintTheSecret()
	{
		if(theSecret_.empty())
		{
			for(size_t i=0; i<encrpytedLine_.size(); ++i)
			{
				if(encrpytedLine_[i] == ' ') cout<<' ';
				else cout<<'x';
			}
		}
		else
		{
			cout<<theSecret_;
		}

		cout<<endl;
	}

private:
	string encrpytedLine_;
	string theSecret_;
	Enigma enigma_;
};

int main()
{
	Problem problem;
	problem.Solve();

	return 0;
}