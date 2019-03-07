#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

vector<string> split_string(string);
 
/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs(std::vector<long int> &X, std::vector<long int> &Y, int size)
{
 
    int L[2][size + 1];
 
    // Binary index, used to
    // index current row and
    // previous row.
    bool bi;
 
    for (int i = 0; i <= size; i++)
    {
         
        // Compute current 
        // binary index
        bi = i & 1;
 
        for (int j = 0; j <= size; j++)
        {
            if (i == 0 || j == 0)
                L[bi][j] = 0;
 
            else if (X[i-1] == Y[j-1])
                 L[bi][j] = L[1 - bi][j - 1] + 1;
 
            else
                L[bi][j] = max(L[1 - bi][j], 
                               L[bi][j - 1]);
        }
    }
 
    // Last filled entry contains
    // length of LCS
    // for X[0..n-1] and Y[0..m-1] 
    return L[bi][size];
}

int main()  {

    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);


    int tc;
    cin >> tc;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    for (int i = 0; i < tc; i++) {
        int size;
        cin >> size;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        string a,b;

        getline(cin,a);
        vector<string> a1 = split_string(a);
        vector<long int> A(size);

        for (int i = 0; i < size; i++) {
            long int A_item = stol(a1[i]);
            A[i] = A_item;
        }

        getline(cin,b);
        vector<string> b1 = split_string(b);
        vector<long int> B(size);

        for (int i = 0; i < size; i++) {
            long int B_item = stol(b1[i]);
            B[i] = B_item;
        }

        cout << lcs(A, B, size) << "\n";
    }
    return 0;
}


vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

2
5
2 3 5 4 4
1 3 1 1 5
8
1 5 3 3 5 4 2 3
5 4 5 2 1 3 5 5