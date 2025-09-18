#include <stdio.h>

int main() {

    printf("My name: John Doe\n");
    printf("My age: 25\n");
    printf("My favorite hobby: Programming\n\n");
    

    char name[50];
    int age;
    
    printf("Please enter your name: ");
    scanf("%49s", name); 
    
    printf("Please enter your age: ");
    scanf("%d", &age);
    
    printf("\nHello %s! ", name);
    printf("You are %d years old. ", age);
    printf("Welcome to C programming!\n");
    
    return 0;
}
