#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {

		int x = 0;
		int y = nums.size() - 1;

		while (x < y) {

			int sum = nums[x] + nums[y];

			if (sum == target) {
				return vector<int> {x, y};
			}
			else if (sum < target) {
				++x;
			}
			else {
				--y;
			}
		}

		return vector<int> {0, 0};
	}
};