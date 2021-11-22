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
#include <map>

using namespace std;

int main() {
    int N, M;
    cin >> N;
    vector<pair<string, int>> a;

    while (N--){
        int day, month, year, quant;
        scanf("%d.%d.%d %d", &day, &month, &year, &quant);
        pair<string, int> temporary;
        
        temporary.first = to_string(year) + (month < 10 ? "0" : "") + to_string(month) +
                     (day < 10 ? "0" : "") + to_string(day);
        temporary.second = quant;
        a.push_back(temporary);
    }

    sort(a.begin(), a.end());

    for (int i = 1; i < a.size(); ++i){
        a[i].second = max(a[i - 1].second, a[i].second);
    }

    cin >> M;

    while (M--){
        int day, month, year;
        scanf("%d.%d.%d", &day, &month, &year);
        pair<string, int> temporary;
        
        temporary.first = to_string(year) + (month < 10 ? "0" : "") + to_string(month) +
                     (day < 10 ? "0" : "") + to_string(day);
        temporary.second = 1000000;
        
        if (a.back().first <= temporary.first){
            cout << a.back().second << endl;
            continue;
        }
        
        auto temporary2 = lower_bound(a.begin(), a.end(), temporary) - a.begin();
        
        if (temporary2 == 0){
            cout << 0 << endl;
        }
        else{
            cout << a[temporary2 - 1].second << endl;
        }
    }
}
