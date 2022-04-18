// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: CS112-203-2nd – S17-20210031-20210052-20210056-A3-FULL.cpp
// Last Modification Date: 07/04/2022
// Author1 and ID and Group: 20210031
// Author2 and ID and Group: 20210052
// Author3 and ID and Group: 20210056
// Teaching Assistant: Eng/ Hagar
// Purpose: For 6 filters in photoshop project

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image1[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char result[SIZE][SIZE];


void loadImage(unsigned char arr[SIZE][SIZE]) {
    char imageFileName[100];

    cout << "Please Enter name of input image: " << endl;
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, arr);
}

void saveImage(unsigned char res_arr[SIZE][SIZE]) {
    char imageFileName[100];

    cout << "Please Enter name of output image: " << endl;
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, res_arr);
}

void invertImage() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 255 - image1[i][j];
        }
    }
}

//---------------------------------
void rotateImage() {

    int choice;
    cout << "Enter rotate value 90, 180 or 270: ";
    cin >> choice;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            result[i][j] = image1[i][j];
        }
    }
    if (choice == 270) {
        for (int x = 1; x <= 3; x++) {
            for (int i = 0; i < SIZE; i++) {        //Transpose the image(rows to columns)
                for (int j = i; j < SIZE; j++) {
                    int ele = result[i][j];
                    result[i][j] = result[j][i];
                    result[j][i] = ele;
                }
            }
            for (int i = 0; i < SIZE; i++) {      // Flip transpose  horizonatally
                for (int j = 0; j < SIZE / 2; j++) {
                    int ele = result[i][j];
                    result[i][j] = result[i][SIZE - 1 - j];
                    result[i][SIZE - 1 - j] = ele;
                }
            }
        }
    }
    else if (choice == 90) {   //rotate image by 90 deg
        for(int i=0 ; i<SIZE;i++){        //Transpose the image(rows to columns)
            for(int j=i ;j < SIZE; j++){
                int ele=result[i][j];
                result[i][j]=result[j][i];
                result[j][i]=ele;
            }
        }
        for(int i=0; i<SIZE; i++){      // Flip transpose  horizonatally
            for(int j=0; j<SIZE/2; j++){
                int ele = result[i][j];
                result[i][j]=result[i][SIZE-1-j];
                result[i][SIZE-1-j]=ele;
            }
        }
    }

    else if (choice == 180) {
        for (int x = 1; x <=2; x++) {
            for(int i=0 ; i<SIZE;i++){        //Transpose the image(rows to columns)
                for(int j=i ;j < SIZE; j++){
                    int ele=result[i][j];
                    result[i][j]=result[j][i];
                    result[j][i]=ele;
                }
            }
            for(int i=0; i<SIZE; i++){      // Flip transpose  horizonatally
                for(int j=0; j<SIZE/2; j++){
                    int ele = result[i][j];
                    result[i][j]=result[i][SIZE-1-j];
                    result[i][SIZE-1-j]=ele;
                }
            }
        }
    }
}


void Merge_Filter() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = (image1[i][j] + image2[i][j]) / 2;
        }
    }
}

void darkenImage() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = image1[i][j] / 2;
        }
    }
}

void lightenImage() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = min(image1[i][j] + 50, 255);
        }
    }
}

void BlackWhiteImage() {
    long long avg = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            avg += image1[i][j];
        }
    }
    avg /= (256 * 256);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (image1[i][j] > avg)
                result[i][j] = 255;
            else
                result[i][j] = 0;
        }
    }
}

void flipImageHorizontally() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            result[i][SIZE - j - 1] = image1[i][j];
        }
    }
}

void flipImageVertically() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            result[SIZE - i - 1][j] = image1[i][j];
        }
    }
}

void enlargeImage(){
    int choice;
    cout<<"Enter which q that you want to enlarge:";
    cin>>choice;
    if(choice==1) {

        for (int i = 0, x = 0; i < SIZE / 2; i++, x += 2) {
            for (int j = 0, y = 0; j < SIZE / 2; j++, y += 2) {
                result[x][y] = image1[i][j];
                result[x + 1][y] = image1[i][j];
                result[x][y + 1] = image1[i][j];
                result[x + 1][y + 1] = image1[i][j];
            }

        }
    } else if(choice==2){
        for (int i = 0, x = 0; i < SIZE / 2; i++, x += 2) {
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y += 2) {
                result[x][y] = image1[i][j];
                result[x + 1][y] = image1[i][j];
                result[x][y + 1] = image1[i][j];
                result[x + 1][y + 1] = image1[i][j];
            }

        }
    }


    else if(choice==3){
        for (int i = SIZE/2, x = 0; i < SIZE; i++, x += 2) {
            for (int j = 0, y = 0; j < SIZE / 2; j++, y += 2) {
                result[x][y] = image1[i][j];
                result[x + 1][y] = image1[i][j];
                result[x][y + 1] = image1[i][j];
                result[x + 1][y + 1] = image1[i][j];
            }

        }

    }
    else if(choice==4){
        for (int i = SIZE/2, x = 0; i < SIZE ; i++, x += 2) {
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y += 2) {
               result[x][y] = image1[i][j];
                result[x + 1][y] = image1[i][j];
                result[x][y + 1] = image1[i][j];
                result[x + 1][y + 1] = image1[i][j];
            }

        }
    }
}

int main() {
    int choice = 0;
    while (choice != -1) {
        cout << "Ahlan ya user ya habibi\n";
        cout << "1- Black & White Filter\n";
        cout << "2- Invert Filter\n";
        cout << "3- Merge Filter\n";
        cout << "4- Flip Image\n";
        cout << "5- Darken and Lighten Image\n";
        cout << "6- Rotate Image\n";
        cin >> choice;
        loadImage(image1);
        if (choice == 1) {
            BlackWhiteImage();
        } else if (choice == 2) {
            invertImage();
        } else if (choice == 3) {
            loadImage(image2);
            Merge_Filter();
        } else if (choice == 4) {
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
        } else if (choice == 5) {
            char choice;
            cout << " Do you want to (d)arken or (l)ighten?" << endl;
            cin >> choice;
            if (choice == 'd')
                darkenImage();
            else if (choice == 'l')
                lightenImage();
            else {
                cout << "Invalid input\n";
                continue;
            }

        } else if (choice == 6) {
            rotateImage();
        }
        saveImage(result);
    }
}
