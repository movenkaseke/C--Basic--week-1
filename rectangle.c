#include <stdio.h>

int main() {
    int length, width, area;

    // Input from user
    printf("Enter length of rectangle: ");
    scanf("%d", &length);

    printf("Enter width of rectangle: ");
    scanf("%d", &width);

    // Calculate area
    area = length * width;

    // Output result
    printf("Area of rectangle = %d\n", area);

    return 0;
}

