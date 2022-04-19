#include <iostream>
#include "bmplib.cpp"
using namespace std;
unsigned char image1[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
unsigned char res[SIZE][SIZE];
unsigned char result[SIZE][SIZE][RGB];
int gx[3][3] = {{-1, 0, 1},
                {-2, 0, 2},
                {-1, 0, 1}};
int gy[3][3] = {{-1, -2, -1},
                {0, 0, 0},
                {1, 2, 1}};
//---------------------------------
void loadImage(unsigned char arr[SIZE][SIZE][RGB]) {
    char imageFileName[100];

    cout << "Please Enter name of input image: " << endl;
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, arr);
}
//---------------------------------
void saveImageRGB(unsigned char res_arr[SIZE][SIZE][RGB]) {
    char imageFileName[100];

    cout << "Please Enter name of output image: " << endl;
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, res_arr);
}
//---------------------------------
void saveImageBW(unsigned char res_arr[SIZE][SIZE]) {
    char imageFileName[100];

    cout << "Please Enter name of output image: " << endl;
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, res_arr);
}
//---------------------------------
void BlackWhiteImage(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int avg = image1[i][j][0] * 0.299 +  image1[i][j][1] * 0.587 +  image1[i][j][2] * 0.114;
            if(avg > 127)
                result[i][j][0] = result[i][j][1] = result[i][j][2] = 255;
            else
                result[i][j][0] = result[i][j][1] = result[i][j][2] = 0;
        }
    }
}
//---------------------------------
void flipImageHorizontally() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < 3; ++k) {
                result[i][SIZE - j - 1][k] = image1[i][j][k];
            }

        }
    }
}
//---------------------------------
void flipImageVertically() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < 3; ++k) {
                result[SIZE - i - 1][j][k] = image1[i][j][k];
            }

        }
    }
}
//---------------------------------
void mirrorImage(char c){
    if (c == 'l')
    {
        for (int i = 0; i < SIZE ; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < 3; ++k) {
                    result[i][j][k] = image1[i][j][k];
                    result[i][SIZE / 2 + j][k] = image1[i][SIZE / 2 - j][k];
                }
            }
        }
    }
    else if (c == 'r')
    {
        for (int i = 0; i < SIZE; ++i) {
            int curr = SIZE;
            for (int j = SIZE / 2; j < SIZE; ++j) {
                for (int k = 0; k < 3; ++k) {
                    result[i][j][k] = image1[i][j][k];
                    result[i][j - SIZE / 2][k] = image1[i][curr][k];
                }
                curr--;
            }
        }
    }
    else if (c == 'u')
    {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < 3; ++k) {
                    result[i][j][k] = image1[i][j][k];
                    result[SIZE / 2 + i][j][k] = image1[SIZE / 2 - i][j][k];
                }
            }
        }
    }
    else if (c == 'd')
    {
        int curr = SIZE;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            curr--;
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < 3; ++k) {
                    result[i][j][k] = image1[i][j][k];
                    result[i - SIZE / 2][j][k] = image1[curr][j][k];
                }
            }
        }
    }
}

int main() {
    char choice = '0';
    while (choice != -1) {
        cout << "Ahlan ya user ya habibi\n";
        cout << "1- Black & White Filter\n";
        cout << "2- Invert Filter\n";
        cout << "3- Merge Filter\n";
        cout << "4- Flip Image\n";
        cout << "5- Darken and Lighten Image\n";
        cout << "6- Rotate Image\n";
        cout << "7- Detect Image Edges\n";
        cout << "8- Enlarge Image\n";
        cout << "9- Shrink Image\n";
        cout << "a- Mirror 1/2 Image\n";
        cin >> choice;
        loadImage(image1);
        if (choice == '1') {
            BlackWhiteImage();
        }
        else if (choice == '4') {
            char choice;
            cout << " Flip (h)orizontally or (v)ertically ?" << endl;
            cin >> choice;
            if (choice == 'h')
                flipImageHorizontally();
            else if (choice == 'v')
                flipImageVertically();
            else {
                cout << "Invalid input\n";
                continue;
            }
        }
        else if (choice == 'a')
        {
            cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n";
            char dir;
            cin >> dir;
            mirrorImage(dir);
        }
        saveImageRGB(result);
    }
}
