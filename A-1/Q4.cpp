#include <iostream>
#include <climits>
using namespace std;

int maxSubarraySum(int arr[], int n, int &start, int &end) {
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;
    int tempStart = 0;
    
    for (int i = 0; i < n; i++) {
        maxEndingHere += arr[i];
        
        if (maxSoFar < maxEndingHere) {
            maxSoFar = maxEndingHere;
            start = tempStart;
            end = i;
        }
        
        if (maxEndingHere < 0) {
            maxEndingHere = 0;
            tempStart = i + 1;
        }
    }
    
    return maxSoFar;
}

int main() {
    int arr[] = {-2, -5, 6, -2, -3, 1, 5, -6};
    int n = 8;
    int start = 0, end = 0;
    
    int maxSum = maxSubarraySum(arr, n, start, end);
    
    cout << "Maximum subarray sum: " << maxSum << endl;
    cout << "Subarray: ";
    for (int i = start; i <= end; i++)
        cout << arr[i] << " ";
    cout << endl;
    
    return 0;
}