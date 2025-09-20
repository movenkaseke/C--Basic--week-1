#include <stdio.h>

int main() {
    float radius, height, volume;
    float pi = 3.14;

    // Input radius and height
    printf("Enter radius of cylinder: ");
    scanf("%f", &radius);

    printf("Enter height of cylinder: ");
    scanf("%f", &height);

    // Calculate volume
    volume = pi * radius * radius * height;

    // Output result
    printf("Volume of cylinder = %.2f\n", volume);

    return 0;
}
