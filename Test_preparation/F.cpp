#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <vector>

using namespace std;

vector<int> new_vector(vector<int> a, int n){
    vector<int> b;
    for(int i = 0; i < n; ++i){
        b.push_back(a[i]);
    }
    for(int i = n+1; i < a.size(); ++i){
        b.push_back(a[i]);
    }

    return b;
}

vector<int> insert_new_vector(vector<int> a, int n, int ID){
    vector<int> b;
    for(int i = 0; i < n; ++i){
        b.push_back(a[i]);
    }
    b.push_back(ID);
    for(int i = n; i < a.size(); ++i){
        b.push_back(a[i]);
    }
    return b;
}

int main(){
    int N;
    cin >> N;
    vector<int> queue;
    vector<int> passed;
    for(int i = 0; i < N; ++i){
        char a;
        cin >> a;
        if( a == '+'){
            int b;
            cin >> b;
            queue.push_back(b);
        }
        if (a == '-'){
            passed.push_back(queue[0]);
            queue = new_vector(queue, 0);
        }
        if ( a == '*'){
            int ID;
            cin >> ID;
            if (int(queue.size()) % 2 == 0){
                queue = insert_new_vector(queue, int(queue.size()/2), ID);
            }
            else{
                queue = insert_new_vector(queue, int(queue.size()/2) + 1, ID);
            }
        }
    }
    
    for(auto i : passed){
        cout << i << endl;
    }

};
