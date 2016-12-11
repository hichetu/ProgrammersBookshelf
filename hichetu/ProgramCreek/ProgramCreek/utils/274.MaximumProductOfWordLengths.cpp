/*
274 Maximum Product of Word Lengths

Given a string array words, find the maximum value of length(word[i]) * length(word[j])
where the two words do not share common letters.You may assume that each word
will contain only lower case letters.If no such two words exist, return 0.

274.1 Java Solution

public int maxProduct(String[] words) {
	if (words == null || words.length == 0)
		return 0;
	int[] arr = new int[words.length];
	for (int i = 0; i<words.length; i++) {
		for (int j = 0; j<words[i].length(); j++) {
			char c = words[i].charAt(j);
			arr[i] |= (1 << (c - ’a’));
		}
	}
	int result = 0;
	for (int i = 0; i<words.length; i++) {
		for (int j = i + 1; j<words.length; j++) {
			if ((arr[i] & arr[j]) == 0) {
				result = Math.max(result, words[i].length()*words[j].length());
			}
		}
	}
	return result;
}

*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

#include "PrintVector.h"

class MaxProduct {
public:
	unsigned int maxProduct(vector<string>& words) {

		vector<int> hash(words.size(), 0);

		int i = 0;
		for (const string& word : words) {
			for (char c : word) {
				hash[i] |= 1 << (c - 'a');
			}
			++i;
		}

		unsigned int result = 0;

		for (size_t i = 0; i < words.size() - 1; ++i) {
			for (size_t j = i + 1; j < words.size(); ++j) {
				if (hash[i] & hash[j] == 0) {
					result = max(result, words[i].size() * words[j].size());
				}
			}
		}

		return result;
	}
};