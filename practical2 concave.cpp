#include<iostream>
#include<graphics.h>
using namespace std;

class Polygon {
protected:
    int xy[10][2];
    int v;

public:
    void read();
    void display();
    void sort(int a[10], int n);
    virtual void scanlineFill() = 0; // Pure virtual function for scanline fill
};

class ColoredPolygon : public Polygon {
    int color;

public:
    void readColor();
    void scanlineFill() override;
};

void Polygon::read() {
    do {
        cout << "\nEnter the total number of vertices in polygon (minimum 3): ";
        cin >> v;
        if (v < 3)
            cout << "\nError: Polygon must have at least three vertices. Try again.";
    } while (v < 3);

    for (int i = 0; i < v; i++) {
        cout << "\nEnter vertex " << i + 1 << " coordinates (x y): ";
        cin >> xy[i][0] >> xy[i][1];
    }
}

void Polygon::display() {
    for (int j = 0; j < v - 1; j++) {
        line(xy[j][0], xy[j][1], xy[j + 1][0], xy[j + 1][1]);
    }
    line(xy[v - 1][0], xy[v - 1][1], xy[0][0], xy[0][1]); // Close the polygon
}

void Polygon::sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void ColoredPolygon::readColor() {
    cout << "\nEnter color code (0-15) to fill the polygon: ";
    cin >> color;
}

void ColoredPolygon::scanlineFill() {
    int ymin = xy[0][1], ymax = xy[0][1];
    for (int i = 1; i < v; i++) {
        if (ymin > xy[i][1]) ymin = xy[i][1];
        if (ymax < xy[i][1]) ymax = xy[i][1];
    }

    float slopes[10];
    for (int j = 0; j < v; j++) {
        int dx = xy[(j + 1) % v][0] - xy[j][0];
        int dy = xy[(j + 1) % v][1] - xy[j][1];
        slopes[j] = (dy == 0) ? 0 : (float) dx / dy;
    }

    int xIntersections[10];
    for (int y = ymin; y <= ymax; y++) {
        int cnt = 0;
        for (int i = 0; i < v; i++) {
            int y1 = xy[i][1], y2 = xy[(i + 1) % v][1];
            if ((y > y1 && y <= y2) || (y > y2 && y <= y1)) {
                int x = xy[i][0] + slopes[i] * (y - y1);
                xIntersections[cnt++] = x;
            }
        }

        sort(xIntersections, cnt);

        for (int k = 0; k < cnt; k += 2) {
            setcolor(color); // Set the desired color
            line(xIntersections[k], y, xIntersections[k + 1], y);
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    ColoredPolygon cp;
    cp.read();
    cp.readColor();

    cp.display();
    cp.scanlineFill();

    getch();
    closegraph();
    return 0;
}
