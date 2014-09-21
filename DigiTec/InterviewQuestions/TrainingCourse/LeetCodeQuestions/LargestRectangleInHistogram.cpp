#include "stdafx.h"

// https://oj.leetcode.com/problems/largest-rectangle-in-histogram/
// I've provided two solves for this. The first is a divide and conquer with some nasty worst cases on certain inputs.
// The second is what I think is an O(n) level solution since we only push each value onto the stack once and we only
// do one computation per value.

int findMinOffset(vector<int>& height, int start, int end, bool& continueSearch)
{
    int min = height[start];
    int minOffset = start;

    while (++start <= end)
    {
        if (height[start] <= min)
        {
            min = height[start];
            minOffset = start;
        }
        else
        {
            continueSearch = true;
        }
    }
    return minOffset;
}

// First solve requires that we find the min, compute the area of the min rectangle, then
// decompose into a left and right solve. This fails miserably on slopes increasing/decreasing
// from left to right.
int largestRectangleAreaWorker(vector<int>& height, int start, int end, int currentMax)
{
    bool continueSearch = false;
    int minOffset = findMinOffset(height, start, end, continueSearch);
    currentMax = std::max(currentMax, ((end - start) + 1) * height[minOffset]);
    if (continueSearch)
    {
        if (start < minOffset)
        {
            currentMax = largestRectangleAreaWorker(height, start, minOffset - 1, currentMax);
        }
        if (minOffset < end)
        {
            currentMax = largestRectangleAreaWorker(height, minOffset + 1, end, currentMax);
        }
    }
    return currentMax;
}


// Second solve, relies on aspects of increasing sequeces to maintain a stack of rectangles
// that need to be computed and computes them all once we find a decreasing sequence or when
// we reach the end of the array. The offsets used are extremely tricky.
int largestRectangleAreaWorker2(vector<int>& height)
{
    int maxArea = 0;
    int currentOffset = 0;
    vector<int> offsets;

    while (currentOffset < height.size())
    {
        if (offsets.empty() || height[offsets.back()] <= height[currentOffset])
        {
            offsets.push_back(currentOffset++);
        }
        else
        {
            int prevOffset = offsets.back();
            offsets.pop_back();

            int width = currentOffset;
            if (!offsets.empty())
            {
                width -= offsets.back() + 1;
            }
            maxArea = max(maxArea, height[prevOffset] * width);
        }
    }

    int previousHeight;
    while (!offsets.empty())
    {
        int prevOffset = offsets.back();
        offsets.pop_back();

        int width = currentOffset;
        if (!offsets.empty())
        {
            width -= offsets.back() + 1;
        }
        maxArea = max(maxArea, height[prevOffset] * width);

        previousHeight = height[prevOffset];
    }
    return maxArea;
}

int largestRectangleArea(vector<int>& height)
{
    if (height.size() == 0) { return 0; }
    // Swap between these for different solves.
    // return largestRectangleAreaWorker(height, 0, height.size() - 1, 0);
    return largestRectangleAreaWorker2(height);
}