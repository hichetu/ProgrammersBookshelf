#include "stdafx.h"

namespace WordLadder
{
    class Solution
    {
    public:
        int ladderLength(string start, string end, unordered_set<string> &dict)
        {
            if (start.size() != end.size() || start.size() == 0)
            {
                return 0;
            }

            // If our final word isn't in the dictionary then we can't complete
            dict.insert(start);

            unordered_set<string>* currentWords = new unordered_set<string>();
            unordered_set<string>* newWords = new unordered_set<string>();

            currentWords->insert(end);
            // Both start and end count as an entry. When we find the word, we add one to
            // the current depth. So 1+1 is 2 and that is the distance between the simplest
            // forms of two words like hog and dog.
            int currentDepth = 1;
            do
            {
                for (const string& curWord : *currentWords)
                {
                    if (BFSMap(start, curWord, dict, newWords))
                    {
                        return ++currentDepth;
                    }
                }
                
                delete currentWords;
                currentWords = newWords;
                newWords = new unordered_set<string>();
                currentDepth++;
            }
            while (currentWords->size() > 0);
            
            return 0;
        }

        int BFSMap(const string& start, const string& cur, unordered_set<string> &dict, unordered_set<string>* newWords)
        {
            for (const string& dictionary_entry : dict)
            {
                if (differsByOne(cur, dictionary_entry))
                {
                    if (dictionary_entry == start)
                    {
                        return true;
                    }
                    newWords->insert(dictionary_entry);
                }
            }
            for (const string& dictionary_entry : *newWords)
            {
                dict.erase(dictionary_entry);
            }
            return false;
        }
        
        bool differsByOne(const string& str1, const string& str2)
        {
            bool differentByOne = false;
            for (int i = 0; i < str1.size(); i++)
            {
                if (str1[i] != str2[i])
                {
                    if (differentByOne)
                    {
                        return false;
                    }
                    else
                    {
                        differentByOne = true;
                    }
                }
            }
            return differentByOne;
        }
    };

    void RunTests()
    {
        string test1start = "hit";
        string test1end = "cog";
        unordered_set<string> test1dict = { "hot", "dot", "dog", "lot", "log" };
        
        Solution s1;
        _ASSERT(5 == s1.ladderLength(test1start, test1end, test1dict));

        string test2start = "hot";
        string test2end = "dog";
        unordered_set<string> test2dict = { "hot", "dog" };

        Solution s2;
        _ASSERT(0 == s2.ladderLength(test2start, test2end, test2dict));
    }
};
