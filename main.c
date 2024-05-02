#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

typedef struct {

    int n; // modulus
    int e; // public exponent
    int d; // private exponent

}Keys;

int modInverse(int a, int m); 

int gcd(int x, int y){
    if(y == 0){
        return y;
    }
    return gcd(x, (x % y));
}

Keys initKeys(int p, int q, int e){
    Keys keys;
    keys.n = p*q;
    int phi = (p-1)*(q-1);
    keys.d = modInverse(e, phi);
    keys.e = e;

    return keys;

}

int encrypt(int m, int e, int n) {
    int c = 1;

    for (int i = 0; i < e; ++i)
        c = (c * m) % n;
    return c;
}


int decrypt(int c, int d, int n) {
    int m = 1;

    for (int i = 0; i < d; ++i)
        m = (m * c) % n;
    return m;
}

int modInverse(int a, int m) {
    int m0 = m;
    int y = 0, x = 1;
    int gcd = 1;
    
    while (a > 1) {
        int q = a / m;
        int t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    
    if (x < 0)
        x += m0;
    
    return x;
}




int main(){

    int p = 3, q = 11, e = 7, m = 2;

    printf("enter number for p");
    scanf("%d ", &p);

    printf("enter number for q");
    scanf("%d ", &q);

    printf("enter number for e");
    scanf("%d ", &e);

    printf("enter number for m");
    scanf("%d ", &m);

    Keys keys = initKeys(p, q, e);

    int cipher = encrypt(m, keys.e, keys.n);
    printf("encrypted message: %d\n", cipher);

    
    int decrypted_message = decrypt(cipher, keys.d, keys.n);
    printf("decrypted message: %d\n", decrypted_message);
   



    return 0; 
}