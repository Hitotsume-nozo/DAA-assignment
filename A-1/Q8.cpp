#include <iostream>
#include <vector>
#include <set>
using namespace std;

int specialtySum(vector<int>& arr) {
    int n = arr.size();
    set<int> specialNumbers;
    
    for (int x = 1; x <= n; x++) {
        bool isSpecial = false;
        
        // Check all subarrays
        for (int i = 0; i < n && !isSpecial; i++) {
            for (int j = i; j < n && !isSpecial; j++) {
                int countGreater = 0;
                
                for (int k = i; k <= j; k++) {
                    if (arr[k] > x) {
                        countGreater++;
                    }
                }
                
                if (countGreater == x) {
                    isSpecial = true;
                    specialNumbers.insert(x);
                }
            }
        }
    }
    
    int sum = 0;
    cout << "Special numbers: ";
    for (int num : specialNumbers) {
        cout << num << " ";
        sum += num;
    }
    cout << endl;
    
    return sum;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    cout << "Sum of special numbers: " << specialtySum(arr) << endl;
    
    return 0;
}