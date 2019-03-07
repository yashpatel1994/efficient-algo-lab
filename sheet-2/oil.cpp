#include <iostream>
#include <limits>
#include <cstdio>
#include "bits/stdc++.h"
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <iterator>
#include <sstream>

using namespace std;

vector<string> split_string(string);

int maxSubArraySum(vector<int> &a)
{
    int max_so_far = a[0];
    int curr_max = a[0];
    int size = a.size();

    for (int i = 1; i < size; i++)
    {
        curr_max = max(a[i], curr_max+a[i]);
        max_so_far = max(max_so_far, curr_max);
    }
    return max_so_far;
}

int maxSubMatrixSum(vector <vector <int> > &mat){

    int col = mat[0].size();
    int row = mat.size();
    int max_sum = 0, summ;

    for (int i = 0; i < col; i++) {
        vector<int> temp(row);
        for (int j = i; j < col; j ++) {
            for (int k = 0; k < row; k++){
                temp[k] += mat[k][j];
            }
            summ = maxSubArraySum(temp);

            if (summ > max_sum){
                max_sum = summ;
            }
        }
    }
    return max_sum;
}
//
//vector<int> doit(string s) {
//    s.erase(remove(s.begin(), s.end(), ' '), s.end());
//    istringstream buf(s);
//    return vector<int>(istream_iterator<int>(buf), istream_iterator<int>());
//}

int main() {

    int n, enterNumber;
    cin >> n;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //int root_n = pow(n,2);

    std::string line;
    getline(cin, line);
//    line.erase(remove(line.begin(), line.end(), ' '), line.end());
//    vector<string> line1 = split_string(line);
//     //int m = stoi(line[0]);
//            vector<char> chars;
//
//            for (int i = 0; i < line1.size(); i++) {
//                string s = line1.at(i);
//                for (int j = 0; j < s.size(); j++) {
//                    chars.push_back(s[j]);
//                }
//            }
//    vector<int> line1 = doit(line);
    vector<int> numbers;

    std::istringstream iss(line);
    while (iss >> enterNumber) {
        numbers.push_back(enterNumber);
    }

    vector <vector<int> > mat(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
//            cout << line1[n*i + j];
//            int temp_item = stoi(line1[n*i + j]);
//            if (isdigit(chars[n*i + j])) {
                int temp_item = numbers[n*i + j];
                mat[i][j] = temp_item;

        }
    }


    int result = maxSubMatrixSum(mat);
    cout << result << '\n';

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