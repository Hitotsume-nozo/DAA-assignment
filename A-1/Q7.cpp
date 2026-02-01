#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int findMedian(vector<int>& subarray) {
    vector<int> temp = subarray;
    sort(temp.begin(), temp.end());
    return temp[temp.size() / 2];
}

int medianRemovalSum(vector<int> arr, int n) {
    for (int op = 0; op < n; op++) {
        int minMedian = INT_MAX;
        
        // Find median of every odd-sized contiguous subarray > 2
        for (int len = 3; len <= arr.size(); len += 2) {
            for (int start = 0; start + len <= arr.size(); start++) {
                vector<int> subarray(arr.begin() + start, arr.begin() + start + len);
                int median = findMedian(subarray);
                minMedian = min(minMedian, median);
            }
        }
        
        // Remove first occurrence of minimum median
        if (minMedian != INT_MAX) {
            for (int i = 0; i < arr.size(); i++) {
                if (arr[i] == minMedian) {
                    arr.erase(arr.begin() + i);
                    break;
                }
            }
        }
    }
    
    // Return sum of remaining elements
    int sum = 0;
    for (int x : arr) sum += x;
    return sum;
}

int main() {
    vector<int> arr = {3, 1, 4, 1, 5};
    int n = 3;  // number of operations
    
    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    cout << "Sum of remaining elements: " << medianRemovalSum(arr, n) << endl;
    
    return 0;
}