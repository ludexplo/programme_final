#pragma warning(disable : 4996)
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>


#define TAILLE_BUF 4 //en général beaucoup plus grande

void ScanDegre(float, int*);


using namespace std;
using namespace cv;

int main(int arcg, char** argv)
{

    remove("C:/Users/ludoh/Desktop/projet_robot_pompier/Travail/programme final/programme_final/image.tiff");
    Mat frame;
    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // open the default camera using default API
    cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 1;             // 0 = open default camera
    int apiID = CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);

    FILE* pFile = new FILE ;
    unsigned short* buffer;
    size_t result, nombre_de_valeur = TAILLE_BUF;
    short int i;
    float degre, somme = 0;
    int total_moyenne, tour = 0, analyse[6] = { 0,0,0,0 };
    

    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }


        // show live and wait for a key with timeout long enough to show images
   
        imshow("Live", frame);
        
        if (waitKey(5) >= 0)
            break;
         
            
            
    }
    imwrite("C:/Users/ludoh/Desktop/projet_robot_pompier/Travail/programme final/programme_final/image.tiff",frame);
    buffer = (unsigned short*)malloc(sizeof(char) );
    for (i = 0; i < 160 * 120; i++)
    {
        
        nombre_de_valeur = fread(buffer, sizeof(short int), TAILLE_BUF, pFile);
        

        degre = (buffer[i + 4]-27315)/100;
        somme += degre;
        ScanDegre(degre, &analyse[0]);


    }
    // the camera will be deinitialized automatically in VideoCapture destructor
   
        int postion[160][120];
    return 0;
}

void ScanDegre(float degre, int* analyse) {


    if ((degre <= 40)) {
        printf("tout va bien\n");
        //cas 1
    }
    else if (degre >= 41 && degre <= 50) {
        printf("echauffement suspect\n");
        //cas 2
    }
    else if (degre >= 100)
    {
        printf("alerte incendie\n");
        //cas 3
    }

    // compter le nombre de 'pixel' > 30°  > 40 > 50  > 60  > 70 
    if (degre >= 30 && degre <= 40)
    {
        analyse[0] += 1;
    }
    if (degre >= 40 && degre <= 50)
    {
        analyse[1] += 1;
    }
    if (degre >= 50 && degre <= 60)
    {
        analyse[2] += 1;
    }
    if (degre >= 60 && degre <= 70)
    {
        analyse[3] += 1;
    }
    if (degre >= 70)
    {
        analyse[4] += 1;
    }
    printf("%f degre\n ", degre);

}
