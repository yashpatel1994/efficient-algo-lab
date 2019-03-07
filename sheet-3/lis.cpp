#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int ceil_array(std::vector<int> &arr1, int l, int r, int x) {  // returns ceil of "x" in a sorted array (i.e. smallest element >= x).

    while (r - l > 1) {
    	int m = l + (r - l)/2;
    	if (arr1[m] >= x)
    		r = m;
    	else 
    		l = m;
    }
        return r;
}

int lis(std::vector<int> &arr2) {
	if (arr2.size() == 0)
		return 0;

	std::vector<int> tail(arr2.size(), 0);
	int length = 1; //always points empty slot in tail

	tail[0] = arr2[0];
	for (size_t i = 1; i < arr2.size(); i ++) {
		if (arr2[i] < tail[0])
			// new smallest value
			tail[0] = arr2[i];
		else if (arr2[i] > tail[length-1])
            // arr2[i] extends largest subsequence
            tail[length++] = arr2[i];
        else
            // arr2[i] will become end candidate of an existing subsequence or
            // Throw away larger elements in all LIS, to make room for upcoming grater elements than arr2[i]
            // (and also, arr2[i] would have already appeared in one of LIS, identify the location and replace it)
            tail[ceil_array(tail, -1, length-1, arr2[i])] = arr2[i];
	}

	return length;
}

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	std::vector<int> arr;
	int i;

	while (!cin.eof()) {
		cin >> i;
		arr.push_back(i);
	}	
	
    int result = lis(arr);

    cout << result << "\n";

	return 0;
}
