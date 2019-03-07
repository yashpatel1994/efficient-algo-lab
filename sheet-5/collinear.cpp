#include <bits/stdc++.h>
#include<unordered_map>
#include <iostream>
#include <limits>
#include <cstdio>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <ios>
using namespace std;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        return h1 ^ h2;
    }
};

float gcd(float a, float b)
{
    if (a < b)
        return gcd(b, a);

    if (fabs(b) < 0.001)
        return a;

    else
        return (gcd(b, a - floor(a / b) * b));
}

float max_point_on_line(vector< pair<float, float> > points)
{
    int N = points.size();
    if (N < 2)
        return N;

    float max_point = 0;
    float curr_max, same, vertical;

    // map to store slope pair
    unordered_map<pair<float, float>, float, pair_hash> slope_map;

    for (int i = 0; i < N; i++)
    {
        curr_max = same = vertical = 0;

        for (int j = i + 1; j < N; j++)
        {
            //  If both points are equal then just
            // increase overlap_point count
            if (points[i] == points[j])
                same++;

                // If x co-ordinate is same, then both
                // points are vertical to each other
            else if (points[i].first == points[j].first)
                vertical++;

            else
            {
                float y_diff = points[j].second - points[i].second;
                float x_diff = points[j].first - points[i].first;
                float g = gcd(x_diff, y_diff);

                // reducing the difference by their gcd
                y_diff /= g;
                x_diff /= g;

                // increasing the frequency of current slope
                // in map
                slope_map[make_pair(y_diff, x_diff)]++;
                curr_max = std::max(curr_max, slope_map[make_pair(y_diff, x_diff)]);
            }

            curr_max = max(curr_max, vertical_points);
        }

        // updating global maximum by current point's maximum
        max_point = max(max_point, curr_max + overlap_points + 1);

        slope_map.clear();
    }

    return max_point;
}
int main() {

    int n;
    float u, v;
    cin >> n;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    vector< pair<float, float> > points;

    for (int i = 0; i < n; i++) {
        cin >> u >> v;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        points.emplace_back(make_pair(u,v));
    }
   // int result = static_cast<int>(max_point_on_line(points));
    cout << max_point_on_line(points) << "\n";

    return 0;
}