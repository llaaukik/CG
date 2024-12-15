#include <graphics.h>
#include <iostream>
using namespace std;

// Function to draw a circle using Bresenham’s algorithm
void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    // Draw the circle using symmetry
    while (x <= y) {
        // Draw points for all octants
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        putpixel(xc + y, yc + x, WHITE);
        putpixel(xc - y, yc + x, WHITE);
        putpixel(xc + y, yc - x, WHITE);
        putpixel(xc - y, yc - x, WHITE);

        // Update x and y
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

int main() {
    int xc, yc, r;
    cout << "Enter the center coordinates of the circle (x, y): ";
    cin >> xc >> yc;
    cout << "Enter the radius of the circle: ";
    cin >> r;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Draw the circle
    drawCircle(xc, yc, r);

    getch();
    closegraph();
    return 0;
}
