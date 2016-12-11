#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class TwoSum {
public:
	vector<int> twoSum(vector<int>& nums, int target) {

		unordered_map<int, int> map;

		vector<int> ans;

		for (int i = 0; i < nums.size(); ++i) {

			int comp = target - nums[i];

			if (map.count(comp)) {
				return vector<int> {map[comp], i};
			}

			map[nums[i]] = i;
		}

		return vector<int> {0, 0};
	}
};