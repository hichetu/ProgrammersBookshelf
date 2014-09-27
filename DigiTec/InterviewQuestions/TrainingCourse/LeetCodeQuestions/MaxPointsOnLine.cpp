#include "stdafx.h"

namespace MaxPointsOnLine
{
    struct Point
    {
        int x;
        int y;
        Point() : x(0), y(0)
        {
        }
        Point(int a, int b) : x(a), y(b)
        {
        }
    };
    /**
    * Definition for a point.
    * struct Point {
    *     int x;
    *     int y;
    *     Point() : x(0), y(0) {}
    *     Point(int a, int b) : x(a), y(b) {}
    * };
    */
    class Solution
    {
    public:
        int maxPoints(vector<Point> &points)
        {
            // If we have 0 points, we have no points on a line
            int maxPointsOnLine = 0;
            if (points.size() > 0)
            {
                // As soon as we have 1 point, that point can be on any line, so we
                // have one point on a line.
                maxPointsOnLine = 1;

                // Later we iterate starting at point[0] through point[n-2] using this
                // as the base point. We then calculate all slopes of this point with
                // all remaining points and store the slope counts for comparison.
                for (int i = 0; i < points.size() - 1; i++)
                {
                    int equalPoints = 1;

                    unordered_map<float, int> slopes;
                    for (int j = i + 1; j < points.size(); j++)
                    {
                        if (points[i].x != points[j].x || points[i].y != points[j].y)
                        {
                            float curSlope = slope(points[i], points[j]);
                            slopes[curSlope]++;
                        }
                        else
                        {
                            equalPoints++;
                        }
                    }
                    for (const pair<float, int>& slopeVal : slopes)
                    {
                        maxPointsOnLine = max(maxPointsOnLine, slopeVal.second + equalPoints);
                    }
                    maxPointsOnLine = max(maxPointsOnLine, equalPoints);
                }
            }
            return maxPointsOnLine;
        }

        float slope(const Point& point1, const Point& point2)
        {
            if (point2.x - point1.x == 0)
            {
                return numeric_limits<float>::infinity();
            }
            return (point2.y - (float)point1.y) / (point2.x - (float)point1.x);
        }
    };

    void RunTests()
    {
        Solution s;

        vector<Point> t1 = {};
        _ASSERT(s.maxPoints(t1) == 0);

        vector<Point> t2 = { { 1, 1 } };
        _ASSERT(s.maxPoints(t2) == 1);

        vector<Point> t3 = { { 1, 1 }, { 2, 2 } }; // slope 1
        vector<Point> t4 = { { 1, 1 }, { 1, 1 } }; // same point
        vector<Point> t5 = { { 1, 1 }, { 2, 1 } }; // denominator 0
        vector<Point> t6 = { { 1, 1 }, { 1, 2 } }; // slope 0

        _ASSERT(s.maxPoints(t3) == 2);
        _ASSERT(s.maxPoints(t4) == 2);
        _ASSERT(s.maxPoints(t5) == 2);
        _ASSERT(s.maxPoints(t6) == 2);

        // Judge 1 failure due to integer calculations in slope formula
        vector<Point> j1 = { { -4, 1 }, { -7, 7 }, { -1, 5 }, { 9, -25 } };
        _ASSERT(s.maxPoints(j1) == 3);

        // Judge 2 failure for similar reasons to Judge 1 failure, needed proper (float) casting.
        vector<Point> j2 = { { 84, 250 }, { 0, 0 }, { 1, 0 }, { 0, -70 }, { 0, -70 }, { 1, -1 }, { 21, 10 }, { 42, 90 }, { -42, -230 } };
        _ASSERT(s.maxPoints(j2) == 6);
    }
}