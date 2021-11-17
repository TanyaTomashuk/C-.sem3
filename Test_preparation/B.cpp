#include <iostream>
#include <fstream>
#include <string.h>
#include <set>
#include <stack>
#include <cmath>
#include <vector>
#include <sstream>
#include <list>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main() {
    set<string, greater<string>> A;
    string str;
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++){
        cin >> str;
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        A.insert(str);
    }
 
    for(auto i : A)
    cout << i << " ";
}
