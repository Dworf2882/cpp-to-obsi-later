#include <iostream>

using namespace std;

int main(){
    int a = 10;
    int& link = a;

    int* ptr = &a;

    cout << a << endl;
    cout << link << endl;
    cout << *ptr;
 }