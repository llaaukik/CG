#include <graphics.h>
#include <math.h>
#include <iostream>
using namespace std;

int cube[8][3] = {
    {-50, -50, -50}, {50, -50, -50}, {50, 50, -50}, {-50, 50, -50},
    {-50, -50, 50},  {50, -50, 50},  {50, 50, 50},  {-50, 50, 50}
};

float scale = 1.0;  // Scale factor
int tx = 0, ty = 0; // Translation values
float angle = 0.0;  // Rotation angle (in degrees)

// Function to apply transformations
void transformCube(int &x, int &y, int z) {
    // Apply scaling
    x = static_cast<int>(x * scale);
    y = static_cast<int>(y * scale);

    // Apply translation
    x += tx;
    y += ty;

    // Apply rotation around the Z-axis
    float rad = angle * (M_PI / 180.0); // Convert to radians
    int tempX = x; // Temporary variable to hold x value
    x = static_cast<int>(tempX * cos(rad) - z * sin(rad));
    z = static_cast<int>(tempX * sin(rad) + z * cos(rad));
}

// Function to draw the cube
void drawCube() {
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    for (int i = 0; i < 12; i++) {
        int x1 = cube[edges[i][0]][0];
        int y1 = cube[edges[i][0]][1];
        int z1 = cube[edges[i][0]][2];
        int x2 = cube[edges[i][1]][0];
        int y2 = cube[edges[i][1]][1];
        int z2 = cube[edges[i][1]][2];

        // Transform points
        transformCube(x1, y1, z1);
        transformCube(x2, y2, z2);

        // Draw the line between the transformed points
        line(x1 + getmaxx() / 2, getmaxy() / 2 - y1, x2 + getmaxx() / 2, getmaxy() / 2 - y2);
    }
}

// Main function
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)""); // Ensure the path to BGI is correct

    // Perform transformations
    cout << "Enter scale factor: ";
    cin >> scale;
    cout << "Enter translation (tx ty): ";
    cin >> tx >> ty;
    cout << "Enter rotation angle (degrees): ";
    cin >> angle;

    cleardevice(); // Clear the screen
    drawCube();    // Draw the cube

    getch(); // Wait for user input
    closegraph(); // Close graphics window
    return 0;
}