#include <stdio.h>

#define MAX_LENGTH 100

int main(void) {
    char name[MAX_LENGTH];
    int age;
    char hobby[MAX_LENGTH];

    // Prompt user for details
    printf("Please provide the following information:\n");

    printf("\tEnter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove trailing newline

    printf("\tEnter your age: ");
    scanf("%d", &age);
    getchar(); // Clear newline from input buffer

    printf("\tEnter your favorite hobby: ");
    fgets(hobby, sizeof(hobby), stdin);
    hobby[strcspn(hobby, "\n")] = 0; // Remove trailing newline

    // Display user's info
    printf("\n### Your Information ###\n");
    printf("Name     : %s\n", name);
    printf("Age      : %d years old\n", age);
    printf("Hobby    : %s\n", hobby);

    // Greeting message
    printf("\nGreeting: Hello, %s! You are %d years old and love %s.\n", name, age, hobby);

    return 0;
}
