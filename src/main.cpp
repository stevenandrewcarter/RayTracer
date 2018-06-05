#include "Image/Bitmap.h"
#include "Shapes/World.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        // We print argv[0] assuming it is the program name
        cout << "usage: " << argv[0] << " <filename>\n";
    } else {
        cout << "RayTracer starting... Saving to " << argv[1] << "\n";
        Bitmap image1;
        if (image1.create(1980, 1080)) {
            cout << "Image Created. [W:" << image1.getwidth() << " H:" << image1.getheight() << "]\n";
            // Camera is a ray as well, Source would be the position that the camera exists and
            // Direction would be where it is looking.
            World world(&image1);
            cout << "Saving Image...\n";
            image1.save(argv[1]);
        }
    }
    return 0;
}