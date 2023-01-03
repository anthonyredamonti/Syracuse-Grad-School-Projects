// Program to create a simple calculator
#include <stdio.h>

enum colors {R, O, Y, G, B, I, V};

struct Circle {
double radius, width, x, y;
};


int main() {

    enum colors colorss; 

    for(int colorss = R; colorss <= V; colorss++){
        if(colorss == 0){
            printf("Red\n");
        }
        if(colorss == 1){
            printf("Orange\n");
        }
        if(colorss == 2){
            printf("Yellow\n");
        }
        if(colorss > 2)
        {
            printf("Unknown\n");
        }
    }

    char operator;
    double n1, n2;

    printf("Enter an operator (+, -, *, /): ");
    scanf("%c", &operator);
    printf("Enter two operands: ");
    scanf("%lf %lf",&n1, &n2);

    switch(operator)
    {
        case '+':
            printf("%.1lf + %.1lf = %.1lf",n1, n2, n1+n2);

        case '-':
            printf("%.1lf - %.1lf = %.1lf",n1, n2, n1-n2);
            break;

        case '*':
            printf("%.1lf * %.1lf = %.1lf",n1, n2, n1*n2);
            break;

        case '/':
            printf("%.1lf / %.1lf = %.1lf",n1, n2, n1/n2);
            break;

        // operator doesn't match any case constant +, -, *, /
        default:
            printf("Error! operator is not correct");
    }

    return 0;
}