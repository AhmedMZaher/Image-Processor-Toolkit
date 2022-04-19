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

void invertimageRGB(){
    for(int i=0; i<SIZE; i++){
        for (int j = 0; j <SIZE ; j++) {
            for(int n=0;n<RGB;n++){
            result[i][j][n]=255-image1[i][j][n];
            }
        }
    }
}

//----------------------------------------
void rotateImageRGB() {

    int choice;
    cout << "Enter rotate value 90, 180 or 270: ";
    cin >> choice;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int n = 0; n < RGB; n++) {
                result[i][j][n] = image1[i][j][n];
            }
        }
    }
    if (choice == 270) {
        for (int x = 1; x <= 3; x++) {
            for (int i = 0; i < SIZE; i++) {        //Transpose the image(rows to columns)
                for (int j = i; j < SIZE; j++) {
                    for (int n = 0; n < RGB; n++) {


                        int ele = result[i][j][n];
                        result[i][j][n] = result[j][i][n];
                        result[j][i][n] = ele;
                    }
                }
            }
            for (int i = 0; i < SIZE; i++) {      // Flip transpose  horizonatally
                for (int j = 0; j < SIZE / 2; j++) {
                    for (int n = 0; n < RGB; n++) {

                        int ele = result[i][j][n];
                        result[i][j][n] = result[i][SIZE - 1 - j][n];
                        result[i][SIZE - 1 - j][n] = ele;
                    }
                }
            }
        }
    }

    else if (choice == 90) {
            for (int i = 0; i < SIZE; i++) {        //Transpose the image(rows to columns)
                for (int j = i; j < SIZE; j++) {
                    for(int n=0;n<RGB;n++){


                        int ele = result[i][j][n];
                        result[i][j][n] = result[j][i][n];
                        result[j][i][n] = ele;
                    }}
            }
            for (int i = 0; i < SIZE; i++) {      // Flip transpose  horizonatally
                for (int j = 0; j < SIZE / 2; j++) {
                    for(int n=0;n<RGB;n++){

                        int ele = result[i][j][n];
                        result[i][j][n] = result[i][SIZE - 1 - j][n];
                        result[i][SIZE - 1 - j][n] = ele;
                    }}
            }
        }

    else if (choice == 180) {
        for (int x = 1; x <= 2; x++) {
            for (int i = 0; i < SIZE; i++) {        //Transpose the image(rows to columns)
                for (int j = i; j < SIZE; j++) {
                    for(int n=0;n<RGB;n++){


                        int ele = result[i][j][n];
                        result[i][j][n] = result[j][i][n];
                        result[j][i][n] = ele;
                    }}
            }
            for (int i = 0; i < SIZE; i++) {      // Flip transpose  horizonatally
                for (int j = 0; j < SIZE / 2; j++) {
                    for(int n=0;n<RGB;n++){

                        int ele = result[i][j][n];
                        result[i][j][n] = result[i][SIZE - 1 - j][n];
                        result[i][SIZE - 1 - j][n] = ele;
                    }}
            }
        }
    }
    }
//--------------------------------------------


void enlargeImageRGB() {
    int choice;
    cout << "Enter which q that you want to enlarge:";
    cin >> choice;
    if (choice == 1) {

        for (int i = 0, x = 0; i < SIZE / 2; i++, x += 2) {
            for (int j = 0, y = 0; j < SIZE / 2; j++, y += 2) {
                for (int n = 0, w = 0; n < RGB; n++, w += 1) {

                    result[x][y][w] = image1[i][j][n];
                    result[x + 1][y][w] = image1[i][j][n];
                    result[x][y + 1][w] = image1[i][j][n];
                    result[x + 1][y + 1][w] = image1[i][j][n];
                }
            }
        }
    }
    if (choice == 2) {

        for (int i = 0, x = 0; i < SIZE/2; i++, x += 2) {
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y += 2) {
                for (int n = 0, w = 0; n < RGB; n++, w += 1) {

                    result[x][y][w] = image1[i][j][n];
                    result[x + 1][y][w] = image1[i][j][n];
                    result[x][y + 1][w] = image1[i][j][n];
                    result[x + 1][y + 1][w] = image1[i][j][n];
                }
            }
        }
    }

    if (choice == 3) {

        for (int i = SIZE/2, x = 0; i < SIZE; i++, x += 2) {
            for (int j = 0, y = 0; j < SIZE/2; j++, y += 2) {
                for (int n = 0, w = 0; n < RGB; n++, w += 1) {

                    result[x][y][w] = image1[i][j][n];
                    result[x + 1][y][w] = image1[i][j][n];
                    result[x][y + 1][w] = image1[i][j][n];
                    result[x + 1][y + 1][w] = image1[i][j][n];
                }
            }
        }
    }

    if (choice == 4) {

        for (int i = SIZE/2, x = 0; i < SIZE; i++, x += 2) {
            for (int j = SIZE/2, y = 0; j < SIZE; j++, y += 2) {
                for (int n = 0; n < RGB; n++) {

                   result[x][y][n] = image1[i][j][n];
                    result[x + 1][y][n] = image1[i][j][n];
                    result[x][y + 1][n] = image1[i][j][n];
                    result[x + 1][y + 1][n] = image1[i][j][n];
                }
            }
        }
    }

}

void shuffleImageRGB() {
    string shuffle;
    cout<<"Enter the new order:";
    getline(cin>> ws,shuffle);
    shuffle.erase(remove(shuffle.begin(),shuffle.end(),' '), shuffle.end());
    int i_start, i_end, j_start, j_end, new_i_start, new_i_end, new_j_start, new_j_end;
    for(int a=0;a<4;a++){
        if(shuffle[a]=='1'){
            i_start= j_start= 0;
            j_end= i_end= SIZE/2;
        }
        else if(shuffle[a]=='2'){
            i_start=0; i_end=SIZE/2; j_start=SIZE/2; j_end=SIZE;
        } else if(shuffle[a]=='3'){
            i_start=SIZE/2; i_end=SIZE;
            j_start=0; j_end=SIZE/2;
        }
        else{
            i_start=j_start=SIZE/2; i_end=j_end=SIZE;
        }
        if(a==0){
            new_i_start=new_j_start=0; new_i_end=new_j_end=SIZE/2;
        }
        else if(a==1){
            new_i_start=0;new_j_start=SIZE/2;
        }
        else if(a==2){
            new_i_start=SIZE/2; new_j_start=0;
        }
        else{
            new_i_start=new_j_start=SIZE/2;
        }
        for(int i=i_start, new_i=new_i_start; i<i_end; i++,new_i++){
            for(int j=j_start,new_j=new_j_start; j<j_end;j++,new_j++){
                for(int n=0; n<RGB;n++) {
                    result[new_i][new_j][n] = image1[i][j][n];
                }
            }
        }
    }
}
void Merge_Filter_RGB()
{
    LoadImage_RGB();
    char imageFileName2[100];
    cout << "Please enter name of image file to merge with:" << endl;
    cin>>imageFileName2;
    strcat(imageFileName2, ".bmp");
    readRGBBMP(imageFileName2, image2_RGB);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            for (int m = 0; m < RGB; m++) {
            res_RGB[i][j][m] = (image_RGB[i][j][m] + image2_RGB[i][j][m]) / 2;
        }
    }
}
void Darken_RGB() {
    LoadImage_RGB();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            for (int m = 0; m < RGB; m++) {
            res_RGB[i][j][m] = image_RGB[i][j][m] / 2;
        }

    }
}
void Lighten_RGB() {
    LoadImage_RGB();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            for (int m = 0; m < RGB; m++) {
            res_RGB[i][j][m]=min(image_RGB[i][j][m]+50,255);
        }

    }
}
void shrink_RGB() {
    string choose1;
    LoadImage_RGB();
    cout << "Shrink to (1/2), (1/3) or (1/4)?" << endl;
    cin >> choose1;
    if (choose1 == "1/2") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++)
                for (int m = 0; m < RGB; m++) {
                res_RGB[i / 2][j / 2][m] = (image_RGB[i][j][m] + image_RGB[i + 1][j][m] + image_RGB[i][j + 1][m] + image_RGB[i + 1][j + 1][m]) / 4;
            }
        }
    }
    else if (choose1 == "1/3") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++)
                for (int m = 0; m < RGB; m++){
                res_RGB[i / 3][j / 3][m] = (image_RGB[i][j][m] + image_RGB[i + 1][j][m] + image_RGB[i][j + 1][m] + image_RGB[i + 1][j + 1][m]) / 4;
            }
        }
    }
    else if (choose1 == "1/4") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++)
                for (int m = 0; m < RGB; m++){
                res_RGB[i / 4][j / 4][m] = (image_RGB[i][j][m] + image_RGB[i + 1][j][m] + image_RGB[i][j + 1][m] + image_RGB[i + 1][j + 1][m]) / 4;
            }
        }
    }
}
void blur_RGB(){
    LoadImage_RGB();
    for (int i = 0; i <SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                res_RGB[i][j][k] =
                        (image_RGB[i][j][k] + image_RGB[i][j + 1][k] + image_RGB[i][j + 2][k] + image_RGB[i][j + 3][k] +
                         image_RGB[i][j + 4][k] + image_RGB[i + 1][j][k] + image_RGB[i + 1][j + 1][k] +
                         image_RGB[i + 1][j + 2][k] + image_RGB[i + 1][j + 3][k] + image_RGB[i + 1][j + 4][k] +
                         image_RGB[i + 2][j][k] + image_RGB[i + 2][j + 1][k] + image_RGB[i + 2][j + 2][k] +
                         image_RGB[i + 2][j + 3][k] + image_RGB[i + 2][j + 4][k] + image_RGB[i + 3][j][k] +
                         image_RGB[i + 3][j + 1][k] + image_RGB[i + 3][j + 2][k] + image_RGB[i + 3][j + 3][k] +
                         image_RGB[i + 4][j][k] + image_RGB[i + 4][j + 1][k] + image_RGB[i + 4][j + 2][k] +
                         image_RGB[i + 4][j + 3][k] + image_RGB[i + 4][j + 4][k]) / 25;
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
