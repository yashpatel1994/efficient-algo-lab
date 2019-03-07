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

struct Point {
         float x;
         float y;
         Point() : x(0), y(0) {}
         Point(float a, float b) : x(a), y(b) {}
    };

int maxPoints(vector<Point> &points) {
    int n = points.size();
    if (n<=2){return n;}
    vector<double> k; //vector to store the slops for one point with all the other points
    int res = 0;

    for (int i=0;i<n;i++){
        k.clear();
        int dup = 1; // number of the duplicates with current point
        for (int j=0;j<n;j++){
            if (i!=j){ // for every other point
                if (points[i].x - points[j].x == 0){ // if the slope is a vertical line
                    if (points[i].y - points[j].y == 0){ // if the point j is the same as point i
                        dup++;
                    }else{
                        k.push_back(99999); //store the vertical line to a specific slope
                    }
                }else{ // if it is the regular slop between point i and j
                    k.push_back(10000*(points[i].y-points[j].y)/(points[i].x-points[j].x)); // store the slope
                }
            }
        }

        sort(k.begin(),k.end()); //sort the slopes for counting

        int pp = 1; //number of points in the same line of the point i
        if (k.empty()){pp=0;}

        for (int jj=1;jj<k.size();jj++){ //count pp
            if (k[jj]==k[jj-1]){
                pp++;
            }else{
                if (pp+dup>res){res=pp+dup;} // res = pp + the number of duplicates
                pp = 1;
            }
        }
        if (pp+dup>res){res = pp+dup;}
    }

    return res;
}

int main() {

    int n;
    float u, v;
    cin >> n;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    vector<Point> points;

    for (int i = 0; i < n; i++) {
        cin >> u >> v;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        points.push_back(Point(u,v));
    }
    // int result = static_cast<int>(max_point_on_line(points));
    cout << maxPoints(points) << "\n";

    return 0;
}