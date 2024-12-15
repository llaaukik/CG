#include <graphics.h>
#include <iostream>
#include <cmath>

#define PI 3.14159265

void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (y >= x) {
        // Draw all eight octants
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        putpixel(xc + y, yc + x, WHITE);
        putpixel(xc - y, yc + x, WHITE);
        putpixel(xc + y, yc - x, WHITE);
        putpixel(xc - y, yc - x, WHITE);

        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}

void drawTriangle(int xc, int yc, int r) {
    // Approximate vertices of the equilateral triangle
    int x1 = xc, y1 = yc - r;
    int x2 = xc - r * cos(PI / 6), y2 = yc + r * sin(PI / 6);
    int x3 = xc + r * cos(PI / 6), y3 = yc + r * sin(PI / 6);

    // Draw the triangle using Bresenham's line algorithm
    line(x1, y1, x2, y2);  // Line from (x1, y1) to (x2, y2)
    line(x2, y2, x3, y3);  // Line from (x2, y2) to (x3, y3)
    line(x3, y3, x1, y1);  // Line from (x3, y3) to (x1, y1)
}

void drawInnerCircle(int xc, int yc, int r) {
    // The radius of the inscribed circle (incircle) in an equilateral triangle
    int innerRadius = (r * sqrt(3)) / 3.4;

    // The center of the inner circle remains the same as the outer circle
    drawCircle(xc, yc, innerRadius);  // Draw the inner circle
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int xc = getmaxx() / 2;
    int yc = getmaxy() / 2;
    int radius = 100;  // Radius of the circumcircle of the triangle

    drawCircle(xc, yc, radius);       // Draw outer circle
    drawTriangle(xc, yc, radius);     // Draw triangle
    drawInnerCircle(xc, yc, radius);  // Draw inner circle

    getch();  // Wait for key press
    closegraph();  // Close graphics mode
    return 0;
}