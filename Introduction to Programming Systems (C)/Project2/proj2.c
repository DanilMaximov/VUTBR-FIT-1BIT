/* Find the working point of the diode.
Let's have a simple series connection of diode and resistor. 
We know Shockley's equation and its constants. Write a function 
that for a given input voltage U_0 and resistor R finds the working 
voltage of the diode corresponding to the specified accuracy. Next, 
write a program that, based on these input parameters, outputs the 
duty point of the diode, ie voltage and current. 

$ ./proj2 U0 R EPS
Up=XXXX V
Ip=YYYY A

*/

/******************************************************/
/* * *                  Projekt 2                 * * */
/* * *                                            * * */
/* * *                  Version 1                 * * */
/* * *                                            * * */
/* * *          Maksimov Danil (xmaksi01)         * * */
/* * *                 November 2019              * * */
/******************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const double I_0 = 1e-12;
const double U_t = 0.0258563;


/* double get_numb(char argv[]){
  int factor = 1;
  double number;
  int len = strlen(argv);
  for (int k = len - 1; k >= 0; k--){
    number = number + (argv[k]*factor);
    factor = factor*10;
  }
  return number;
} */


double get_value(char argv[]){
  double value;
  sscanf(argv,"%lg", &value);
  return value;
}

int error_check(int argc, char* argv[]){

    double eps = get_value(argv[3]);
    double R = get_value(argv[2]);
    double U_0 = get_value(argv[1]);
    if(argc != 4) //
      return -1;

    if(eps >= 1)
      return -1;

    char* inf = "inf";
    if(strcmp (argv[1],inf) == 0 || strcmp (argv[2],inf) == 0){
      printf("Up=inf V\n");
      printf("Ip=inf A\n");
      return 1;
    }


    if (eps >= 1 || R <= 0 || U_0 <=0)
      return -1;


    for(int i = 1; i <=3; i++){
      int len = strlen(argv[i]);
      for(int k = 0; k < len; k++){
        if ((argv[i][k] < '1' && argv[i][k] > '9' && argv[i][k] !='e' && argv[i][k] !='i' && argv[i][k]!= 'n' && argv[i][k]!='f' && argv[i][k] != '-') || argv[i][0] == '.' )
          return -1;
      }
    }

    return 0;
}

double equation_for_U(double U_p, double U_0, double R){
  return U_0 - I_0*R*(exp(U_p / U_t) - 1) - U_p;
}

double diode(double U_0, double R, double eps){
  double a = 0;
  double b = U_0;

    while(fabs(b-a) > eps){ // if the condition is not met, then again divide the segment, met - the point is found
      double c = (a + b) / 2; // mid interval
      double y1 = equation_for_U(a,U_0,R); // value of left point on segment
      double y2 = equation_for_U(c, U_0, R); // value of right point on segment


      if(y1*y2 < 0)
        b = c;
      else if (y1*y2 > 0)
        a = c;
    }
    return fabs((a+b)/2);
}

int main (int argc, char* argv[]){

    int error = error_check(argc,argv);

    if (error == -1){ // input control
      printf("error: invalid arguments\n");
      return -1;

    }
    else if (error == 1)
      return 0;

  double U_0, R, eps;

  U_0 = get_value(argv[1]);
  R = get_value(argv[2]);
  eps = get_value(argv[3]);
  if(eps < 1e-15) // if more then 15 numbers after ',' program will freeze
    eps = 1e-15;

  double U_p = diode(U_0,R,eps);

  printf("Up=%g V\n", U_p);
  printf("Ip=%g A\n", (U_0 - U_p) / R);

  return 0;
}