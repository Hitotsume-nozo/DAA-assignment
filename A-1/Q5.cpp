#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canDivide(vector<int>& arr, int k, int maxOr) {
    int segments = 1;
    int currentOr = 0;
    
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] > maxOr) return false;
        
        if ((currentOr | arr[i]) <= maxOr) {
            currentOr |= arr[i];
        } else {
            segments++;
            currentOr = arr[i];
        }
    }
    
    return segments <= k;
}

int minMaxBitwiseOr(vector<int>& arr, int k) {
    int totalOr = 0;
    int maxElement = 0;
    
    for (int num : arr) {
        totalOr |= num;
        maxElement = max(maxElement, num);
    }
    
    int low = maxElement;
    int high = totalOr;
    int result = high;
    
    while (low <= high) {
        int mid = (low + high) / 2;
        
        if (canDivide(arr, k, mid)) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    return result;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    int k = 3;
    
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    cout << "K = " << k << endl;
    cout << "Minimum Maximum Bitwise OR: " << minMaxBitwiseOr(arr, k) << endl;
    
    return 0;
}