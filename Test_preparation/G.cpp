#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <vector>

int main(){
std::stack<int> stoparic;
std::string s;
char* p;

    while (std::cin >> s) {
    int x = std::strtol(s.c_str(), &p, 10);
    if (*p){
        int b = stoparic.top();
        stoparic.pop();
        int a = stoparic.top();
        stoparic.pop();

        if (s == "+")
            x = a + b;
        if (s == "-")
            x = a - b;
        if (s == "*")
            x = a * b;
        if (s == "/")
            x = a / b;
    }
    stoparic.push(x);
}
std::cout << stoparic.top();

return 0;
}
