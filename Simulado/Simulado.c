//Exercicio 860 do leetcode

#include <stdbool.h>

bool lemonadeChange(int* bills, int billsSize) {
    
    int num5 = 0, num10 = 0;

    if ( bills[0] != 5 ) {
        return false;
    } else {
        num5++;
    }

    for ( int i = 1; i < billsSize; i++ ) {
        if ( bills[i] == 5 ) {
            num5++;
        } else if ( bills[i] == 10 ) {
            if ( num5 > 0 ) {
                num5--;
                num10++;
            } else {
                return false;
            }
        } else {
            if ( num10 > 0 && num5 > 0 ) {
                num5--;
                num10--;
            } else if ( num5 >= 3 ) {
                num5 -= 3;
            } else {
                return false;
            }
        }
    }

    return true;
}