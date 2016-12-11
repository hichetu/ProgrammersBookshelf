
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class CountingBits {
public:
	vector<int> countBits(int n) {
		vector<int> ans(n + 1, 0);

		int p = 1;
		int pow = 1;

		for (int i = 1; i <= n; ++i) {

			if (i == pow) {
				p = 1;
				ans[i] = 1;
				pow <<= 1;
			}
			else {
				ans[i] = 1 + ans[p++];
			}
		}

		return ans;
	}
};