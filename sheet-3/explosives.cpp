#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>
using namespace std;

struct point
{
    int x, y;
};

double dist(const point &a, const point &b)
{
    // "plus 16 additional feet of cable.."
    return 16.0 + sqrt((double)(a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main()
{
    int n;
    while (cin >> n, n > 0)
    {
        vector<point> points;
        vector<int> point_indexes;
        for (int i = 1; i <= n; ++i)
        {
            point pt;
            cin >> pt.x >> pt.y;
            points.push_back(pt);
            point_indexes.push_back(i - 1);
        }

        // Loop over all permutations.
        vector<int> network;
        double min_fuze = numeric_limits<double>::max();
        do {
            double fuze = 0;
            for (int i = 0; i < n - 1; ++i)
                fuze += dist(points[point_indexes[i]], points[point_indexes[i + 1]]);

            if (fuze < min_fuze)
            {
                min_fuze = fuze;
            }
        }

        while (next_permutation(point_indexes.begin(), point_indexes.end()));
        cout << setprecision(2) << setiosflags(ios::fixed) << min_fuze << "\n";
    }
    return 0;
}
