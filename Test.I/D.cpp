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

struct Passenger{
    int time_stamp;
    int id;
    float vit_d;
    float acat;
    float anti_tg;
    float neural_activity;
    float mch;
    float delta;
};

int main(){
    int N, k = -1, l = -1, m = -1;
    float min1 = 1000000, min2 = 1000000, min3 = 1000000;
    int arr[3] = {0, 0, 0};
    cin >> N;
    vector<Passenger>passengers(N);
    
    
    for (int i = 0; i < N; i++){
        cin >> passengers[i].time_stamp;
        cin >> passengers[i].id;
        cin >> passengers[i].vit_d;
        cin >> passengers[i].acat;
        cin >> passengers[i].anti_tg;
        cin >> passengers[i].neural_activity;
        cin >> passengers[i].mch;
    }
    
    for (int i = 0; i < N; i++){
        passengers[i].time_stamp = 0;
        passengers[i].vit_d = 0;
        passengers[i].acat = 0;
        passengers[i].anti_tg = 0;
        passengers[i].mch = 0;
        passengers[i].delta = 10000000;
    }
    
    for(int i = 0 ; i < N - 1; i++) {
         for(int j = 0 ; j < N - i - 1; j++) {
             if(passengers[j].id > passengers[j+1].id) {
                 int temp1 = passengers[j].id;
                 passengers[j].id = passengers[j+1].id;
                 passengers[j+1].id = temp1;
                 
                 float temp2 = passengers[j].neural_activity;
                 passengers[j].neural_activity = passengers[j+1].neural_activity;
                 passengers[j+1].neural_activity = temp2;
             }
         }
     }
    
    if (passengers[0].id != passengers[1].id){
        passengers[0].id = 0;
        passengers[0].neural_activity = 0;
    }
    
    for(int i = 1; i < N; i++) {
        if ((passengers[i].id != passengers[i+1].id) && (passengers[i].id != passengers[i-1].id)){
            passengers[i].id = 0;
            passengers[i].neural_activity = 0;
        }
    }
    
    for (int i = 0; i < N; i++){
        if (passengers[i].id == passengers[i+1].id){
            if (abs(passengers[i].neural_activity - passengers[i+1].neural_activity) < passengers[i].delta){
                passengers[i].delta = abs(passengers[i].neural_activity - passengers[i+1].neural_activity);
                passengers[i+1].delta = abs(passengers[i].neural_activity - passengers[i+1].neural_activity);
                
            }
        }
    }
    
    for(int i = 1; i < N; i++){
        if ((min1 > passengers[i].delta) && (passengers[i].id != 0)) {
            min1 = passengers[i].delta;
            k = i;
        }
    }
    
    for(int i = 1; i < N; i++){
        if ((min2 > passengers[i].delta) && (passengers[i].id != passengers[k].id)  && (passengers[i].id != 0)) {
            min2 = passengers[i].delta;
            l = i;
        }
    }
    
    for(int i = 1; i < N; i++){
        if ((min3 > passengers[i].delta) && (passengers[i].id != passengers[k].id) && (passengers[i].id != passengers[l].id)  && (passengers[i].id != 0)) {
            min3 = passengers[i].delta;
            m = i;
        }
    }
    
    if (k != -1){
        arr[0] = passengers[k].id;
    }
        
    if (l != -1){
        arr[1] = passengers[l].id;
    }
        
    if (m != -1){
        arr[2] = passengers[m].id;
    }
        
    for(int i = 0 ; i < 2; i++) {
        for(int j = 0 ; j < 2 - i; j++) {
            if(arr[j] > arr[j+1]) {
                int temp1 = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp1;
            }
        }
    }
        
    for (int i = 0; i < 3; i++){
        if (arr[i] != 0){
            cout << arr[i] << ' ';
        }
    }
    
    if ((k == -1) && (m == -1) && (l == -1)) {cout << k;}
}
