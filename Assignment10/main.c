// main.c

#include <stdio.h>
#include "circle.h"
#include "square.h"
#include "rectangle.h"

int main() {
    // Test the circle area function
    double radius = 5.0;
    double circle_area = area_of_circle(radius);
    printf("Area of circle with radius %.2f: %.2f\n", radius, circle_area);

    // Test the square area function
    double side = 4.0;
    double square_area = area_of_square(side);
    printf("Area of square with side %.2f: %.2f\n", side, square_area);

    // Test the rectangle area function
    double length = 6.0;
    double width = 3.0;
    double rectangle_area = area_of_rectangle(length, width);
    printf("Area of rectangle with length %.2f and width %.2f: %.2f\n", length, width, rectangle_area);

    return 0;
}

