#include <stdio.h>
#include <math.h> 
//f = 2^((p-69)/12) * 440

int main(){
    int C4 = 60, A4 = 69;
    double fC4 = pow(2, (C4 - 69) / 12.0) * 440.0;
    double fA4 = pow(2, (A4 - 69) / 12.0) * 440.0;

    printf("The MIDI pitch for C4 is %d with a frequency of %.2f Hz\n", C4, fC4);
    printf("The MIDI pitch for A4 is %d with a frequency of %.2f Hz\n", A4, fA4);
    
    return 0;
}