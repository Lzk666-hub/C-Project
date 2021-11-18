#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;

void print_prompt() {
    cout << "Please enter the integer and the test number: ";
}

bool Arm(int integer){
    if(integer==1)   return true;
    for(int i=1;i<integer;i++){
        double a=(double)i;
        double b=(double)integer;
        int power=(int )pow(a,b);
        if((power%integer)!=i)	return false;
    }
    return true;
}

bool CJ(int integer){
    int inv=0;
    int bar=integer;
    while (bar){
        inv=inv*10+bar%10;
        bar/=10;
    }
    return integer==inv;
}

bool BPC(int integer){
    float r=(sqrt(24*integer+1)+1)/6;
    int r1=int((sqrt(24*integer+1)+1)/6);
    float r2=r1-r;
    return r2==0;
}

bool Aus(int integer){
    int divisor=0;
    for(int i=1;i<=integer/2;i++){
        if(integer%i==0){
            divisor+=i;

        }

    }return divisor>integer;


}
int main() {
    int integer=0;
    int test=0;
    print_prompt();
    cin>>integer>>test;
    while (integer<=0||integer>10000000||test>4||test<1){
        print_prompt();
        cin>>integer>>test;
    }
    if(test ==1){
        if (Arm(integer)){
            cout<<1;
        }else cout<<0;
    }
    else if(test==2){
        if(integer<0){
            integer=-integer;
        }
        if (CJ(integer)){
            cout<<1;
        }else cout<<0;
    }
    else if(test==3){
        if (BPC(integer)){
            cout<<1;
        }else cout<<0;
    }
    else if(test==4){
        if (Aus(integer)){
            cout<<1;
        }else cout<<0;
    }
}