#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cfloat>
using namespace std;

struct Point {
    double x, y;
};

double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + 
                (p1.y - p2.y) * (p1.y - p2.y));
}

bool compareX(Point a, Point b) {
    return a.x < b.x;
}

bool compareY(Point a, Point b) {
    return a.y < b.y;
}

double bruteForce(vector<Point>& points, int left, int right, Point& p1, Point& p2) {
    double minDist = DBL_MAX;
    
    for (int i = left; i <= right; i++) {
        for (int j = i + 1; j <= right; j++) {
            double d = distance(points[i], points[j]);
            if (d < minDist) {
                minDist = d;
                p1 = points[i];
                p2 = points[j];
            }
        }
    }
    return minDist;
}

double stripClosest(vector<Point>& strip, double d, Point& p1, Point& p2) {
    double minDist = d;
    
    sort(strip.begin(), strip.end(), compareY);
    
    for (int i = 0; i < strip.size(); i++) {
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; j++) {
            double dist = distance(strip[i], strip[j]);
            if (dist < minDist) {
                minDist = dist;
                p1 = strip[i];
                p2 = strip[j];
            }
        }
    }
    
    return minDist;
}

double closestUtil(vector<Point>& points, int left, int right, Point& p1, Point& p2) {
    if (right - left <= 2) {
        return bruteForce(points, left, right, p1, p2);
    }
    
    int mid = (left + right) / 2;
    Point midPoint = points[mid];
    
    Point p1L, p2L, p1R, p2R;
    double dL = closestUtil(points, left, mid, p1L, p2L);
    double dR = closestUtil(points, mid + 1, right, p1R, p2R);
    
    double d;
    if (dL < dR) {
        d = dL;
        p1 = p1L;
        p2 = p2L;
    } else {
        d = dR;
        p1 = p1R;
        p2 = p2R;
    }
    
    // Build strip
    vector<Point> strip;
    for (int i = left; i <= right; i++) {
        if (abs(points[i].x - midPoint.x) < d) {
            strip.push_back(points[i]);
        }
    }
    
    Point p1S, p2S;
    double dS = stripClosest(strip, d, p1S, p2S);
    
    if (dS < d) {
        p1 = p1S;
        p2 = p2S;
        return dS;
    }
    
    return d;
}

double closestPair(vector<Point>& points, Point& p1, Point& p2) {
    sort(points.begin(), points.end(), compareX);
    return closestUtil(points, 0, points.size() - 1, p1, p2);
}

int main() {
    vector<Point> points = {
        {2, 3}, {12, 30}, {40, 50}, {5, 1},
        {12, 10}, {3, 4}, {7, 8}, {15, 20},
        {25, 35}, {8, 9}, {1, 2}, {6, 7},
        {14, 16}, {22, 28}, {33, 44}, {9, 11}
    };
    
    cout << "Points:" << endl;
    for (int i = 0; i < points.size(); i++) {
        cout << "(" << points[i].x << ", " << points[i].y << ")" << endl;
    }
    
    Point p1, p2;
    double minDist = closestPair(points, p1, p2);
    
    cout << "\nClosest pair: (" << p1.x << ", " << p1.y << ") and (" 
         << p2.x << ", " << p2.y << ")" << endl;
    cout << "Minimum distance: " << minDist << endl;
    
    return 0;
}