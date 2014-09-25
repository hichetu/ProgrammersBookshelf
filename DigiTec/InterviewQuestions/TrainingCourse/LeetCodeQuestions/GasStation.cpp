#include "stdafx.h"

namespace GasStation
{
    class Solution
    {
    public:
        int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
        {
            if (gas.size() != 0)
            {
                bool loop = false;
                int currentStation = 0;
                int stations = 0;
                int net = 0;

                do
                {
                    net += gas[currentStation] - cost[currentStation];
                    currentStation++;
                    if (net < 0)
                    {
                        net = 0;
                        stations = 0;
                    }
                    else
                    {
                        stations++;
                    }
                    if (currentStation == gas.size())
                    {
                        currentStation = 0;
                        loop = true;
                    }
                }
                while (!loop || (stations > 0 && stations < gas.size()));

                if (stations == gas.size())
                {
                    return currentStation;
                }
            }
            return -1;
        }
    };

    void RunTests()
    {
        Solution s;

        vector<int> emptyGas1{ };
        vector<int> emptyCost1{ };
        _ASSERT(-1 == s.canCompleteCircuit(emptyGas1, emptyCost1));

        vector<int> simplePassGas1{ 2, 1 };
        vector<int> simplePassCost1{ 1, 0 };
        _ASSERT(0 == s.canCompleteCircuit(simplePassGas1, simplePassCost1));

        vector<int> wrapPassGas1{ 1, 5 };
        vector<int> wrapPassCost1{ 2, 2 };
        _ASSERT(1 == s.canCompleteCircuit(wrapPassGas1, wrapPassCost1));

        vector<int> judgeGas1{ 4 };
        vector<int> judgeCost1{ 5 };
        _ASSERT(-1 == s.canCompleteCircuit(judgeGas1, judgeCost1));
    }
};