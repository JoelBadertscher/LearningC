/*
This programm uses the formula °C=(5/9)(F°-32) to print the following table of Fahrenheit
temperatures and ther centigrade or Celsius equivalents.
*/

#include <stdio.h>

/* print Fahrenheit-Celsius table
for fahr = 0, 20, ... , 300 */

int main (void){

int fahr, celsius;
int lower, upper, step;

lower = 0;	// lower limit of temperatore scale
upper = 300;	// upper limit
step = 20;	// step size

fahr = lower; 
while (fahr <= upper) {
    celsius = 5 * (fahr-32) / 9;
    printf("%d\t%d\n", fahr, celsius);
    fahr = fahr + step;
   }
}
