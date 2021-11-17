#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cmath>
#include <vector>
#include <sstream>
#include <list>
#include <stdio.h>
#include <cstdlib>

using namespace std;

int main(){
    long long n, arr[1000000], counter = 0;
    
    cin >> n;
  
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    for(int i = 0 ; i < n - 1; i++) {
        for(int j = 0 ; j < n - i - 1; j++) {
            if(arr[j] > arr[j+1]) {
                long long temp = arr[j];
                arr[j] = arr[j+1] ;
                arr[j+1] = temp;
            }
        }
    }
    
    for (int i = 0; i < n; i++){
        if (arr[i] != arr[i + 1]){
                counter += 1;
        }
    }
    
    cout << counter;
}
