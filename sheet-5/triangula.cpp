#include <iostream>
#include <limits>
#include <cstdio>
#include <bits/stdc++.h>
#include <sstream>
#include <cmath>
#include <cstdlib>
#define MAX 1000000.000

using namespace std;

struct Point {
    float x;
    float y;
    Point() : x(0), y(0) {}
    Point(float a, float b) : x(a), y(b) {}
};

float min(float x, float y) {
    return (x<=y) ? x : y;
}

float dist(Point p1, Point p2) {
    return  sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

float cost(vector<Point> &points, int i, int j) {
    Point p1 = points[i], p2 = points[j];
    return dist(p1,p2);
}

float minCPT(vector<Point> &points, int i, int j) {

    if (j < i+2) {return 0.000;}

    float res = MAX;

    for (int k = i+1; k < j; k++) {
        res = min(res, cost(points, i, k) + cost(points, k, j));
    }
    return res;
}

float perimeterP(vector<Point> &points) {

    int n = points.size();

    float per = 0.000, dx, dy;

    for (int i = 0; i < n; ++i) {
        dx = points[(i+1)%n].x - points[i].x;
        dy = points[(i+1)%n].y - points[i].y;
        per += sqrt(dx*dx + dy*dy);
    }
    return per;
}

int main() {

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Point> points;

    for (int i = 0; i < n; i++) {
        float u, v;
        cin >> u >> v;
        points.push_back(Point(u,v));
    }

//    int a = points.size()/2;
    float result = minCPT(points, 0, n-1);
    float per = perimeterP(points);

    cout << result << "\n";
}