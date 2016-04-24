#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

int main(){
    int mem = 55838;
    //int num32 = 32;
    //int num64 = 64;
    int teste1 = mem >> 5;
    cout << "Divisao por 32: " << teste1 << endl;
    int teste2 = teste1 >> 6;
    cout << "Divisao por 64: " << teste2 << endl;
    return 0;
}
