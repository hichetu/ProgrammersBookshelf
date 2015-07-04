#include "stdafx.h"

namespace TextJustification
{
    class Solution
    {
    public:
        string formatLine(vector<string>& line, int currentLineLength, int totalLineLength, bool forceLeftJustify)
        {
            if (line.size() == 1)
            {
                forceLeftJustify = true;
            }

            string output = "";
            if (!forceLeftJustify)
            {
                int totalExtraSpace = totalLineLength - currentLineLength;
                int gaps = line.size() - 1;
                int spaceDistribution = totalExtraSpace / gaps;
                int overflowSpace = totalExtraSpace % gaps;

                while (line.size() > 0)
                {
                    if (output.size() > 0)
                    {
                        int extraSpaceForWord = spaceDistribution + 1;
                        if (overflowSpace > 0)
                        {
                            extraSpaceForWord++;
                            overflowSpace--;
                        }

                        while (extraSpaceForWord > 0)
                        {
                            output += " ";
                            extraSpaceForWord--;
                        }
                    }
                    output += line.front();
                    line.erase(line.begin());
                }
            }
            else
            {
                while (line.size() > 0)
                {
                    if (output.size() > 0)
                    {
                        output += " ";
                    }
                    output += line.front();
                    line.erase(line.begin());
                }
                while (output.size() < totalLineLength)
                {
                    output += " ";
                }
            }
            return output;
        }

        vector<string> fullJustify(vector<string> &words, int L)
        {
            vector<string> lines;
            vector<string> currentLine;
            int currentLineLength = 0;

            while (words.size() > 0)
            {
                if (currentLineLength + words.front().size() > L)
                {
                    // Format the line, but remember to strip the trailing whitespace character.
                    lines.push_back(formatLine(currentLine, currentLineLength - 1, L, false));
                    currentLineLength = 0;
                    currentLine.clear();
                }
                else
                {
                    // Add the word and the length;
                    currentLineLength += words.front().size() + 1;
                    currentLine.push_back(words.front());
                    words.erase(words.begin());
                }
            }
            lines.push_back(formatLine(currentLine, currentLineLength - 1, L, true));
            return lines;
        }
    };

    void PrintResults(vector<string>& lines)
    {
        for (const string& s : lines)
        {
            printf("|%s|\n", s.c_str());
        }
        printf("\n");
    }

    void RunTests()
    {
        Solution s;

        vector<string> s1 = { "This", "is", "an", "example", "of", "text", "justification." };
        vector<string> r1 = s.fullJustify(s1, 16);
        PrintResults(r1);

        vector<string> empty = { "" };
        vector<string> emptyResults = s.fullJustify(empty, 0);
        PrintResults(emptyResults);

        vector<string> single = { "a" };
        vector<string> singleResultsResults = s.fullJustify(single, 1);
        PrintResults(singleResultsResults);

        vector<string> single2 = { "a" };
        vector<string> singleResultsResultsJustified = s.fullJustify(single2, 4);
        PrintResults(singleResultsResultsJustified);

        getchar();
    }
}