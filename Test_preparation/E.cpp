 #include <iostream>
 #include <string>
 #include <stack>
 #include <vector>
 using namespace std;
 int main(){
     stack<int> nums;
     vector<int> in_nums;
     int s;
     while(cin >> s){
         in_nums.push_back(s);
         if(s == 0)
             break;
     }
     for(auto i : in_nums){
         if(i > 0)
             nums.push(i);
         if(i < 0){
             if(!nums.empty()){
                 if(-i < nums.top())
                     nums.top()+=i;
                 else nums.pop();}
         }
     }
     if(!nums.empty())
         cout << nums.size() << " " << nums.top();
     else cout << "0 -1";
 }
