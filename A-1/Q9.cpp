#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Rectangle {
    int width, height;
};

bool canFit(vector<Rectangle>& rects, int size) {
    int currentRowWidth = 0;
    int currentRowHeight = 0;
    int totalHeightUsed = 0;
    
    for (int i = 0; i < rects.size(); i++) {
        if (rects[i].width > size || rects[i].height > size) {
            return false;
        }
        
        if (currentRowWidth + rects[i].width <= size) {
            currentRowWidth += rects[i].width;
            currentRowHeight = max(currentRowHeight, rects[i].height);
        } else {
            totalHeightUsed += currentRowHeight;
            currentRowWidth = rects[i].width;
            currentRowHeight = rects[i].height;
        }
    }
    
    totalHeightUsed += currentRowHeight;
    return totalHeightUsed <= size;
}

int minSquareSize(vector<Rectangle>& rects) {
    int maxWidth = 0, maxHeight = 0;
    int totalWidth = 0, totalHeight = 0;
    
    for (auto& r : rects) {
        maxWidth = max(maxWidth, r.width);
        maxHeight = max(maxHeight, r.height);
        totalWidth += r.width;
        totalHeight += r.height;
    }
    
    int low = max(maxWidth, maxHeight);
    int high = max(totalWidth, totalHeight);
    int result = high;
    
    while (low <= high) {
        int mid = (low + high) / 2;
        
        if (canFit(rects, mid)) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    return result;
}

int main() {
    vector<Rectangle> rects = {{2, 3}, {4, 2}, {3, 3}, {1, 4}};
    
    cout << "Rectangles (width x height):" << endl;
    for (auto& r : rects) {
        cout << r.width << " x " << r.height << endl;
    }
    
    cout << "Minimum square size: " << minSquareSize(rects) << endl;
    
    return 0;
}