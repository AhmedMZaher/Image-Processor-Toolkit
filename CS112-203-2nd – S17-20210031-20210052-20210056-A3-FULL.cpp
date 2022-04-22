// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: xxxxxx.cpp
// Last Modification Date: 07/04/2022
// Author1 and ID and Group: 20210031
// Author2 and ID and Group: 20210052
// Author3 and ID and Group: 20210056
// Teaching Assistant: Eng/ Hagar
// Purpose: For 6 filters in photoshop project
#include <iostream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image1[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char result[SIZE][SIZE];
int Gx[3][3] = {{-1, 0, 1},
                {-2, 0, 2},
                {-1, 0, 1}};
int Gy[3][3] = {{-1, -2, -1},
                {0,  0,  0},
                {1,  2,  1}};

void loadImage(unsigned char arr[SIZE][SIZE]) {
    char imageFileName[100];

    cout << "Please Enter name of input image: " << endl;
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, arr);
}

//---------------------------------
void saveImage(unsigned char res_arr[SIZE][SIZE]) {
    char imageFileName[100];

    cout << "Please enter target file name: " << endl;
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, res_arr);
}

//---------------------------------
void invertImage(unsigned char in[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 255 - in[i][j];
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
            for (int i = 0; i < SIZE; i++) {      //Flip transpose  horizontally
                for (int j = 0; j < SIZE / 2; j++) {
                    int ele = result[i][j];
                    result[i][j] = result[i][SIZE - 1 - j];
                    result[i][SIZE - 1 - j] = ele;
                }
            }
        }
    } else if (choice == 90) {   //rotate image by 90 deg
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
    } else if (choice == 180) {
        for (int x = 1; x <= 2; x++) {
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
}

//---------------------------------
void Merge_Filter() {
    char imageFileNameToMerge[100];

    cout << "Please enter name of image file to merge with: " << endl;
    cin >> imageFileNameToMerge;
    strcat(imageFileNameToMerge, ".bmp");
    readGSBMP(imageFileNameToMerge, image2);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = (image1[i][j] + image2[i][j]) / 2; //add two images and divided them by 2
        }
    }
}

//---------------------------------
void darkenImage() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = image1[i][j] / 2;
            divide
            image1
            by
            2
            to
            darken it
        }
    }
}

//---------------------------------
void lightenImage() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = min(image1[i][j] + 50, 255);//Add 50 pixels to  white pixels in image1
        }
    }
}

//---------------------------------
void BlackWhiteImage() {
    // This variable to get average of all pixels in the array
    long long avg = 0;
    // Itreate over array to calcualte average
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            avg += image1[i][j];
        }
    }
    // divide by size of array
    avg /= (256 * 256);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            // check if current pixel greater than average of all pixels
            if (image1[i][j] > avg)
                result[i][j] = 255;
            else
                result[i][j] = 0;
        }
    }
}

//---------------------------------
void flipImageHorizontally() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            // change every pixel in column from start to its corrseponding in the end
            // for example i change pixel [0][255] --> pixel [0][0] and so on
            result[i][SIZE - j - 1] = image1[i][j];
        }
    }
}

//---------------------------------
void flipImageVertically() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            // change every pixel in row from start to its corrseponding in the end
            // for example i change pixel [0][255] --> pixel [0][0] and so on
            result[SIZE - i - 1][j] = image1[i][j];
        }
    }
}

//---------------------------------
void edgeDetection() {
    // Two variables to carry value of sobel's array of x and y
    int Gx_sum = 0;
    int Gy_sum = 0;
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            // This loop to itreate over array of sobel's value directions
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    Gx_sum += Gx[k][l] * image1[i + k - 1][j + l - 1];
                    Gy_sum += Gy[k][l] * image1[i + k - 1][j + l - 1];
                }
            }
            int pixel = abs(Gx_sum) + abs(Gy_sum);
            // becasue pixel value maybe is greater than maximum (255) or less than (0)
            pixel = pixel > 255 ? 255 : pixel;
            pixel = pixel < 0 ? 0 : pixel;
            result[i][j] = pixel;
            Gx_sum = 0;
            Gy_sum = 0;
        }
    }
    invertImage(result);
}

//---------------------------------
void mirrorImage(char c) {
    // Mirror image in left direction
    if (c == 'l') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                result[i][j] = image1[i][j];
                result[i][SIZE / 2 + j] = image1[i][SIZE / 2 - j];
            }
        }
        // Mirror image in right direction
    } else if (c == 'r') {
        for (int i = 0; i < SIZE; ++i) {
            int curr = SIZE;
            for (int j = SIZE / 2; j < SIZE; ++j) {
                result[i][j] = image1[i][j];
                result[i][j - SIZE / 2] = image1[i][curr];
                curr--;
            }
        }
        // Mirror image in upper direction
    } else if (c == 'u') {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result[i][j] = image1[i][j];
                result[SIZE / 2 + i][j] = image1[SIZE / 2 - i][j];
            }
        }
        // Mirror image in down direction
    } else if (c == 'd') {
        int curr = SIZE;
        for (int i = SIZE / 2; i < SIZE; ++i) {
            curr--;
            for (int j = 0; j < SIZE; ++j) {
                result[i][j] = image1[i][j];
                result[i - SIZE / 2][j] = image1[curr][j];
            }
        }
    }
}

//---------------------------------
void enlargeImage() {
    int choice;
    cout << "Enter which q that you want to enlarge:"; //user enter the q to enlarge
    cin >> choice;
    if (choice == 1) {

        for (int i = 0, x = 0; i < SIZE / 2; i++, x += 2) {    //loop in the first quarter
            for (int j = 0, y = 0; j < SIZE / 2; j++, y += 2) {
                result[x][y] = image1[i][j];                //pixel in loop repeats 4 times in different places
                result[x + 1][y] = image1[i][j];
                result[x][y + 1] = image1[i][j];
                result[x + 1][y + 1] = image1[i][j];
            }

        }
    } else if (choice == 2) {
        for (int i = 0, x = 0; i < SIZE / 2; i++, x += 2) {  //loop in the second quarter
            for (int j = SIZE / 2, y = 0; j < SIZE; j++, y += 2) {
                result[x][y] = image1[i][j];           //pixel in loop repeats 4 times in different places
                result[x + 1][y] = image1[i][j];
                result[x][y + 1] = image1[i][j];
                result[x + 1][y + 1] = image1[i][j];
            }

        }
    } else if (choice == 3) {
        for (int i = SIZE / 2, x = 0; i < SIZE; i++, x += 2) {  //loop in the third quarter
            for (int j = 0, y = 0; j < SIZE / 2; j++, y += 2) {
                result[x][y] = image1[i][j];  // pixel in loop repeats 4 times in different places
                result[x + 1][y] = image1[i][j];
                result[x][y + 1] = image1[i][j];
                result[x + 1][y + 1] = image1[i][j];
            }

        }

    } else if (choice == 4) {
        for (int i = SIZE / 2, x = 0; i < SIZE; i++, x += 2) {  //loop in the fourth quarter
            for (int j = SIZE / 2, y = 0; j < SIZE; j++, y += 2) {
                result[x][y] = image1[i][j];  //pixel in loop repr=eats 4 times in different places
                result[x + 1][y] = image1[i][j];
                result[x][y + 1] = image1[i][j];
                result[x + 1][y + 1] = image1[i][j];
            }

        }
    }
}

//---------------------------------
void shrinkImage() {
    string choose1;
    cout << "Shrink to (1/2), (1/3) or (1/4)?" << endl;
    cin >> choose1;
    if (choose1 == "1/2") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                result[i / 2][j / 2] = (image1[i][j] + image1[i + 1][j] + image1[i][j + 1] + image1[i + 1][j + 1]) /
                                       4;// getting the avg of matrix 2 *2 and divide every pixel by 2 to get the photo shrinked by 1/2
            }
        }
    } else if (choose1 == "1/3") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                result[i / 3][j / 3] = (image1[i][j] + image1[i + 1][j] + image1[i][j + 1] + image1[i + 1][j + 1]) /
                                       4;// getting the avg of matrix 2 *2 and divide every pixel by 3 to get the photo shrinked by 1/2
            }
            3
        }
    } else if (choose1 == "1/4") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                result[i / 4][j / 4] = (image1[i][j] + image1[i + 1][j] + image1[i][j + 1] + image1[i + 1][j + 1]) /
                                       4;// getting the avg of matrix 2 *2 and divide every pixel by 4 to get the photo shrinked by 1/4
            }
        }
    }
}

//---------------------------------
void shuffleImage() {
    string shuffle;
    cout << "Enter the new order:";
    getline(cin >> ws, shuffle); //user enter the new order to arrange image
    shuffle.erase(remove(shuffle.begin(), shuffle.end(), ' '), shuffle.end());  //remove spaces between numbers
    int i_start, i_end, j_start, j_end, new_i_start, new_i_end, new_j_start, new_j_end;
    for (int a = 0; a < 4; a++) {  //loop 4 times
        if (shuffle[a] == '1') {  // if shuffle =1 i start, end , j start,end = the values of the first quarter
            i_start = j_start = 0;
            j_end = i_end = SIZE / 2;
        } else if (shuffle[a] == '2') { // if shuffle =2 i start, end , j start,end = the values of the second quarter
            i_start = 0;
            i_end = SIZE / 2;
            j_start = SIZE / 2;
            j_end = SIZE;
        } else if (shuffle[a] == '3') { // if shuffle =3 i start, end , j start,end = the values of the third quarter
            i_start = SIZE / 2;
            i_end = SIZE;
            j_start = 0;
            j_end = SIZE / 2;
        } else {  // if shuffle =4 i start, end , j start,end = the values of the fourth quarter
            i_start = j_start = SIZE / 2;
            i_end = j_end = SIZE;
        } //array that image will load in.
        if (a == 0) {  //if a=0 new i start,end , new j start,end = the  value of the first quarter
            new_i_start = new_j_start = 0;
            new_i_end = new_j_end = SIZE / 2;
        } else if (a == 1) { //if a=1 new i start,end , new j start,end = the  value of the second quarter
            new_i_start = 0;
            new_j_start = SIZE / 2;
        } else if (a == 2) {  //if a=2 new i start,end , new j start,end = the  value of the third quarter
            new_i_start = SIZE / 2;
            new_j_start = 0;
        } else { //if a=3 new i start,end , new j start,end = the  value of the fourth quarter
            new_i_start = new_j_start = SIZE / 2;
        }
        for (int i = i_start, new_i = new_i_start; i < i_end; i++, new_i++) {
            for (int j = j_start, new_j = new_j_start; j < j_end; j++, new_j++) {
                result[new_i][new_j] = image1[i][j]; //load the image in result array
            }
        }
    }
}

//---------------------------------
void blurImage() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = (image1[i][j] + image1[i][j + 1] + image1[i][j + 2] + image1[i][j + 3] + image1[i][j + 4] +
                            image1[i + 1][j] + image1[i + 1][j + 1] + image1[i + 1][j + 2] + image1[i + 1][j + 3] +
                            image1[i + 1][j + 4] + image1[i + 2][j] + image1[i + 2][j + 1] + image1[i + 2][j + 2] +
                            // getting the avg for a matrix  5 * 5  to blur the image
                            image1[i + 2][j + 3] + image1[i + 2][j + 4] + image1[i + 3][j] + image1[i + 3][j + 1] +
                            image1[i + 3][j + 2] + image1[i + 3][j + 3] + image1[i + 4][j] + image1[i + 4][j + 1] +
                            image1[i + 4][j + 2] + image1[i + 4][j + 3] + image1[i + 4][j + 4]) / 25;
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
        cout << "b- Shuffle Image\n";
        cout << "c- Blur Image\n";
        cout << "s- Save the image to a file\n";
        cout << "0- Exit\n";
        cin >> choice;
        if (choice != 's')
            loadImage(image1);
        if (choice == '1') {
            BlackWhiteImage();
        } else if (choice == '2') {
            invertImage(image1);
        } else if (choice == '3') {
            Merge_Filter();
        } else if (choice == '4') {
            char direction;
            cout << " Flip (h)orizontally or (v)ertically ?" << endl;
            cin >> direction;
            if (direction == 'h')
                flipImageHorizontally();
            else if (direction == 'v')
                flipImageVertically();
            else {
                cout << "Invalid input\n";
                continue;
            }
        } else if (choice == '5') {
            char c;
            cout << " Do you want to (d)arken or (l)ighten?" << endl;
            cin >> c;
            if (choice == 'd')
                darkenImage();
            else if (choice == 'l')
                lightenImage();
            else {
                cout << "Invalid input\n";
                continue;
            }
        } else if (choice == '6') {
            rotateImage();
        } else if (choice == '7') {
            edgeDetection();
        } else if (choice == '8') {
            enlargeImage();
        } else if (choice == '9') {
            shrinkImage();
        } else if (choice == 'a') {
            cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n";
            char dir;
            cin >> dir;
            mirrorImage(dir);
        } else if (choice == 'b') {
            shuffleImage();
        } else if (choice == 'c') {
            blurImage();
        } else if (choice == 's') {
            saveImage(result);
        } else if (choice == '0') {
            return 0;
        } else {
            cout << "Invalid Input, please try again" << endl;
            continue;
        }
    }
}
