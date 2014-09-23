#include "stdafx.h"

namespace EvaluateReversePolishNotation
{
    class Solution
    {
    public:
        int evalRPN(vector<string> &tokens)
        {
            vector<int> numbers;

            for (const string& token : tokens)
            {
                if (token == "/" || token == "+" || token == "-" || token == "*")
                {
                    int operand2 = numbers.back(); numbers.pop_back();
                    int operand1 = numbers.back(); numbers.pop_back();

                    if (token == "/")
                    {
                        operand1 /= operand2;
                    }
                    else if (token == "+")
                    {
                        operand1 += operand2;
                    }
                    else if (token == "-")
                    {
                        operand1 -= operand2;
                    }
                    else
                    {
                        operand1 *= operand2;
                    }
                    numbers.push_back(operand1);
                }
                else
                {
                    numbers.push_back(atoi(token.c_str()));
                }
            }
            if (numbers.size() > 0)
            {
                return numbers.back();
            }
        }
    };

    void RunTests()
    {
        Solution s;
        vector<string> input1{ "2", "1", "+", "3", "*" };
        vector<string> input2{ "4", "13", "5", "/", "+" };
        vector<string> judge1{ "0", "3", "/" };

        _ASSERT(9 == s.evalRPN(input1));
        _ASSERT(6 == s.evalRPN(input2));
        _ASSERT(0 == s.evalRPN(judge1));
    }
}