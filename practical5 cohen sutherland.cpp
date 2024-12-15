#include <iostream>
#include <graphics.h>
using namespace std;

// Constants for region codes
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Define clipping window
int xmin, ymin, xmax, ymax;

// Function to compute region code for a point (x, y)
int computeCode(int x, int y) {
    int code = INSIDE;

    if (x < xmin)       // to the left of rectangle
        code |= LEFT;
    else if (x > xmax)  // to the right of rectangle
        code |= RIGHT;
    if (y < ymin)       // below the rectangle
        code |= BOTTOM;
    else if (y > ymax)  // above the rectangle
        code |= TOP;

    return code;
}

// Cohen-Sutherland line clipping algorithm
void cohenSutherlandClip(int &x1, int &y1, int &x2, int &y2) {
    // Compute region codes for P1, P2
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // Both endpoints lie within rectangle
            accept = true;
            break;
        } else if (code1 & code2) {
            // Both endpoints are outside rectangle in the same region
            break;
        } else {
            // Some segment of the line lies within the rectangle
            int codeOut;
            int x, y;

            // At least one endpoint is outside the rectangle, pick it
            if (code1 != 0)
                codeOut = code1;
            else
                codeOut = code2;

            // Find intersection point using formula y = y1 + slope * (x - x1) or x = x1 + (1 / slope) * (y - y1)
            if (codeOut & TOP) { // Point is above the clip rectangle
                x = x1 + (x2 - x1) * (ymax - y1) / float(y2 - y1);
                y = ymax;
            } else if (codeOut & BOTTOM) { // Point is below the rectangle
                x = x1 + (x2 - x1) * (ymin - y1) / float(y2 - y1);
                y = ymin;
            } else if (codeOut & RIGHT) { // Point is to the right of rectangle
                y = y1 + (y2 - y1) * (xmax - x1) / float(x2 - x1);
                x = xmax;
            } else if (codeOut & LEFT) { // Point is to the left of rectangle
                y = y1 + (y2 - y1) * (xmin - x1) / float(x2 - x1);
                x = xmin;
            }

            // Replace point outside rectangle with intersection point and recompute region code
            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        // Draw the clipped line
        setcolor(RED);
        line(x1, y1, x2, y2);
    } else {
        cout << "Line rejected\n";
    }
}

// Main program
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Input clipping window coordinates
    cout << "Enter the clipping window coordinates (xmin, ymin, xmax, ymax): ";
    cin >> xmin >> ymin >> xmax >> ymax;

    rectangle(xmin, ymin, xmax, ymax); // Draw the clipping rectangle

    // Input the endpoints of the line
    int x1, y1, x2, y2;
    cout << "Enter the endpoints of the line (x1, y1, x2, y2): ";
    cin >> x1 >> y1 >> x2 >> y2;

    setcolor(WHITE);
    line(x1, y1, x2, y2); // Draw original line in white
    getch();

    // Clear the screen for clipping process
    cleardevice(); // Clear screen but keep the window

    // Draw the clipping rectangle again
    rectangle(xmin, ymin, xmax, ymax);

    // Apply Cohen-Sutherland line clipping algorithm
    cohenSutherlandClip(x1, y1, x2, y2);

    getch();
    closegraph();
    return 0;
}
