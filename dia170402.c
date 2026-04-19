#include <stdio.h>

int main()
{
    int bills[5] = {5, 5, 5, 10, 20};
    int notas5 = 0;   
    int notas10 = 0;
    int cont = 0;
    int i;
    
    for ( i = 0; i < 5; i++ ) {
        if ( bills [ i ] == 5 ) {
            notas5++; 
        }
        
        if ( bills [ i ] == 10 ) {
            if ( notas5 > 0 ) {
                notas5--;
                notas10++;
            } else {
                cont = 1;
            }
        }

        if ( bills [ i ] == 20 ) {
            if ( notas10 > 0 && notas5 > 0 ) {
                notas10--;
                notas5--;
            } 
            else if ( notas5 >= 3 ) {
                notas5 -= 3;
            } else {
                cont = 1;
            }
        }
    }
   
    if (cont == 1 ) {
        printf ( "false\n " );
    } else {
        printf ( " true\n " );
    }

    return 0;
}
