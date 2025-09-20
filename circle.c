#include <stdio.h>

int main() {
    float radius, area;
    float pi = 3.14;

    // Input radius
    printf("Enter radius of circle: ");
    scanf("%f", &radius);

    // Calculate area
    area = pi * radius * radius;

    // Output result
    printf("Area of circle = %.2f\n", area);

    return 0;
}
