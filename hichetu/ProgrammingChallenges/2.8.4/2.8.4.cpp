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

#if _MSC_VER >=	1700
#include <chrono>
#endif

using namespace std;


class EnigmaGuess
{
public:

	static void SetDictionary(const vector<string>& dictionary)
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
		DecrpytStage0();

		if(Abort()) return string();

		if(Lucky()) return Decode();

		BuildGuesses();

		return DecryptWithGuesses(message);
	}

	bool MapGuessChars(const string& code, const string& target)
	{
		for(size_t i=0; i<code.size(); ++i)
		{
			if(mapRChars_.count(target[i]))
			{
				if(mapRChars_[target[i]] != code[i])
				{
					return false;
				}
			}

			if(mapChars_.count(code[i]))
			{
				if(mapChars_[code[i]] != target[i])
				{
					return false;
				}
			}

			mapChars_[code[i]] = target[i];
			mapRChars_[target[i]] = code[i];
		}

		return true;
	}

	void MapChars(const string& code, const string& target)
	{
		for(size_t i=0; i<code.size(); ++i)
		{
			mapChars_[code[i]] = target[i];
			mapRChars_[target[i]] = code[i];
		}
	}

	void BuildWords(const string& message)
	{
		stringstream stream(message);
		inputWords_.clear();

		while(stream.good())
		{
			string word;
			stream >> word;
			if(!word.empty())
			{
				inputWords_.push_back(word);
				mapCipher_[word] = mapLengthToDictionaryStrings_[word.size()];

				PruneForCharacterFrequenceMatch(word);

				if(mapCipher_[word].size() == 1)
				{
					MapChars(word, *(mapCipher_[word].begin()));
				}
			}
		}
	}
private:

	void PruneForCharacterFrequenceMatch(const string& word)
	{
		set<string>& setTargets = mapCipher_[word];
		size_t uniqueCharacters = UniqueCharactersInWord(word);

		for(set<string>::iterator setIter = setTargets.begin(); setIter != setTargets.end(); )
		{
			const string& strTarget = *setIter;
			size_t uniqueCharactersInTarget = UniqueCharactersInWord(strTarget);

			if(uniqueCharacters != uniqueCharactersInTarget)
			{
				set<string>::iterator eraseIter = setIter;
				++setIter;
				setTargets.erase(eraseIter);
			}
			else
			{
				++setIter;
			}
		}
	}

	size_t UniqueCharactersInWord(const string& word)
	{
		map<char, int> mapChars;
		for(size_t i=0; i<word.size(); ++i)
		{
			++mapChars[word[i]];
		}
		return mapChars.size();
	}

	bool Abort() const
	{
		return fAbort_;
	}

	bool Lucky()
	{
		for(map<string, set<string> >::iterator iter = mapCipher_.begin(); iter != mapCipher_.end(); ++iter)
		{
			if(iter->second.size() != 1) return false;;
		}

		return true;
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

	void DecrpytStage0()
	{
		bool fProgress = true;
		fAbort_ = false;

		while(fProgress)
		{
			fProgress = false;

			for(map<string, set<string> >::iterator iter = mapCipher_.begin(); iter != mapCipher_.end(); ++iter)
			{
				if(iter->second.size() == 1) continue;
				if(iter->second.size() == 0)
				{
					fAbort_ = true; 
					return;
				}

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
		bool fProgress = false;

		const string& code = iter->first;
		set<string>& setTargets = iter->second;

		for(size_t i=0; i<code.size(); ++i)
		{
			if(mapChars_.count(code[i]))
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
			else
			{
				for(set<string>::iterator setIter = setTargets.begin(); setIter != setTargets.end(); )
				{
					const string& strTarget = *setIter;

					if(mapRChars_.count(strTarget[i]))
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

	string DecryptWithGuesses(const string& message)
	{
		for(size_t i=0; i<guessWork_.size(); ++i)
		{
			const string& code = guessWork_[i].first;
			const set<string>& target = guessWork_[i].second;

			for(set<string>::const_iterator iter = target.begin(); iter!=target.end(); ++iter)
			{
				EnigmaGuess enigmaGuess(*this);

				if(!enigmaGuess.MapGuessChars(code, *iter)) continue;

				string secret = enigmaGuess.Decrpyt(message);

				if(!secret.empty()) return secret;
			}
		}

		return string();
	}

	void BuildGuesses()
	{
		guessWork_.clear();

		for(map<string, set<string> >::iterator iter = mapCipher_.begin(); iter != mapCipher_.end(); ++iter)
		{
			if(iter->second.size() == 1) continue;
			if(iter->second.size() == 0) continue;

			guessWork_.push_back(*iter);
		}
	}

private:
	bool fAbort_;
	vector<string> inputWords_;
	map<char, char> mapChars_;
	map<char, char> mapRChars_;
	map<string, set<string> > mapCipher_;

	vector< pair< string, set<string> > > guessWork_;

private:
	static vector<string> dictionary_;
	static map< size_t, set<string> > mapLengthToDictionaryStrings_;
};

vector<string> EnigmaGuess::dictionary_;
map< size_t, set<string> > EnigmaGuess::mapLengthToDictionaryStrings_;

class Problem
{
public:
	Problem() : outputCounter_(0) {}

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

		dictionary_.clear();
		dictionary_.reserve(dictionarySize);

		for(size_t i=0; i<dictionarySize; ++i)
		{
			string line;
			getline(cin, line);

			dictionary_.push_back(trim(line));
		}

		EnigmaGuess::SetDictionary(dictionary_);
	}

	string trim(const std::string& str, const std::string& whitespace = " \t")
	{
		const string::size_type strBegin = str.find_first_not_of(whitespace);
		if (strBegin == std::string::npos)
			return ""; // no content

		const string::size_type strEnd = str.find_last_not_of(whitespace);
		const string::size_type strRange = strEnd - strBegin + 1;

		return str.substr(strBegin, strRange);
	}

	bool ReadEncryptedInputs()
	{
		string str;
		getline(cin, str);

		if(cin.bad()) return false;
		if(str.empty()) return false;

		encrpytedLine_ = trim(str);

		return true;
	}

	void DecryptCipher()
	{
		EnigmaGuess enigma;
		enigma.BuildWords(encrpytedLine_);
		theSecret_ = enigma.Decrpyt(encrpytedLine_);
	}

	void PrintTheSecret()
	{
		if(outputCounter_++ > 0)
		{
			cout<<endl;
		}

		if(theSecret_.empty())
		{
			for(size_t i=0; i<encrpytedLine_.size(); ++i)
			{
				if(encrpytedLine_[i] == ' ') cout<<' ';
				else cout<<'*';
			}
		}
		else
		{
			cout<<theSecret_;
		}
	}

private:
	string encrpytedLine_;
	string theSecret_;
	int outputCounter_;
	vector<string> dictionary_;
};

int main()
{
#if _MSC_VER >=	1700
	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();
#endif


	Problem problem;
	problem.Solve();

#if _MSC_VER >=	1700
	end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end-start;
	cout <<"\n"<<endl;
	cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
#endif

	return 0;
}