// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: xxxxxx.cpp
// Last Modification Date: 07/04/2022
// Author1 and ID and Group: 20210031
// Author2 and ID and Group: 20210052
// Author3 and ID and Group: 20210056
// Teaching Assistant: Eng/ Hagar
// Purpose: For 6 filters in photoshop project



void invertImage(){
    for(int i=0; i<SIZE; i++){
        for (int j = 0; j <SIZE ; j++) {
            image[i][j]= 255-image[i][j];
        }
    }
}
//---------------------------------
void rotateImage() {

    int choice;
    cout << "Enter rotate value 90, 180 or 270: ";
    cin >> choice;
    if (choice == 270) {
        for (int x = 1; x <= 3; x++) {
            for (int i = 0; i < SIZE; i++) {        //Transpose the image(rows to columns)
                for (int j = i; j < SIZE; j++) {
                    int ele = image[i][j];
                    image[i][j] = image[j][i];
                    image[j][i] = ele;
                }
            }
            for (int i = 0; i < SIZE; i++) {      // Flip transpose  horizonatally
                for (int j = 0; j < SIZE / 2; j++) {
                    int ele = image[i][j];
                    image[i][j] = image[i][SIZE - 1 - j];
                    image[i][SIZE - 1 - j] = ele;
                }
            }
        }
    }
     else if (choice == 90) {   //rotate image by 90 deg
        for(int i=0 ; i<SIZE;i++){        //Transpose the image(rows to columns)
            for(int j=i ;j < SIZE; j++){
                int ele=image[i][j];
                image[i][j]=image[j][i];
                image[j][i]=ele;
            }
        }
        for(int i=0; i<SIZE; i++){      // Flip transpose  horizonatally
            for(int j=0; j<SIZE/2; j++){
                int ele = image[i][j];
                image[i][j]=image[i][SIZE-1-j];
                image[i][SIZE-1-j]=ele;
            }
        }
            }

    else if (choice == 180) {
        for (int x = 1; x <=2; x++) {
            for(int i=0 ; i<SIZE;i++){        //Transpose the image(rows to columns)
                for(int j=i ;j < SIZE; j++){
                    int ele=image[i][j];
                    image[i][j]=image[j][i];
                    image[j][i]=ele;
                }
            }
            for(int i=0; i<SIZE; i++){      // Flip transpose  horizonatally
                for(int j=0; j<SIZE/2; j++){
                    int ele = image[i][j];
                    image[i][j]=image[i][SIZE-1-j];
                    image[i][SIZE-1-j]=ele;
                }
            }
        }
    }
}





void Merge_Filter()
{
    LoadImage();
    char imageFileName2[100];
    cout << "Please enter name of image file to merge with:" << endl;
    cin>>imageFileName2;
    strcat(imageFileName2, ".bmp");
    readGSBMP(imageFileName2, image2);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            res[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
}
void Darken() {
    LoadImage();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            res[i][j] = image[i][j] / 2;
        }

    }
}
void Lighten() {
    LoadImage();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            res[i][j]=min(image[i][j]+50,255);
        }

    }
}

