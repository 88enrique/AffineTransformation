/**
    Opencv example code: geometric transformation through matrix operations
    Enrique Marin
    88enrique@gmail.com
*/

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(){

    // Variables
    cvNamedWindow("Original", CV_WINDOW_NORMAL);
    cvNamedWindow("Transformation", CV_WINDOW_NORMAL);

    // Load an image
    Mat src = imread("../Images/stewie.jpg");
    if( !src.data ){
        return -1;
    }

    // Data
    float width = src.cols;
    float height = src.rows;
    float sx = 1;
    float sy = 1;
    float alpha = 0;
    float tx = -width/2;
    float ty = -height/2;
    float a = 0;
    float perspx = 0;
    float perspy = 0;

    // Keys for changing image features
    printf("Traslation: t, f, g, h\n"
           "Rotation: n, m\n"
           "Scale: z, x\n"
           "Skew: o, p\n"
           "Perspective: w, a, s, d\n");

    // Continuous transformation
    while (1){

        // Copy original image
        Mat tmp = Mat(src.cols, src.rows, src.type());

        // Affine Transformation Matrix (Matrix H)
        Mat K = (Mat_<float>(3,3) << 1,0,width/2,0,1,height/2,0,0,1);
        Mat T = (Mat_<float>(3,3) << 1,0,tx,0,1,ty,0,0,1);
        Mat R = (Mat_<float>(3,3) << cos(alpha),-sin(alpha),0,sin(alpha),cos(alpha),0,0,0,1);
        Mat S = (Mat_<float>(3,3) << sx,0,0,0,sy,0,0,0,1);
        Mat P = (Mat_<float>(3,3) << 1,a,0,0,1,0,0,0,1);
        Mat A = (Mat_<float>(3,3) << 1,0,0,0,1,0,perspx,perspy,1);

        // Compute Transformation Matrix H
        Mat H = K*S*R*T*P*A;

        // Transformation of the points
        warpPerspective(src, tmp, H, cvSize(src.cols, src.rows));

        // Show the transformated template in the image
        imshow("Transformation", tmp);
        imshow("Original", src);

        // Read commands
        int c = cvWaitKey(10) & 255;
        switch(c){
        // m rotate CC (right)
        case 109:
            alpha += 0.1;
            break;
        // n rotate CCW (left)
        case 110:
            alpha -= 0.1;
            break;
        // o skew left
        case 112:
            a += 0.1;
            break;
        // p skew right
        case 111:
            a -= 0.1;
            break;
        // x zoom in
        case 120:
            sx += 0.1;
            sy += 0.1;
            break;
        // z zoom out
        case 122:
            sx -= 0.1;
            sy -= 0.1;
            break;
        // t move up
        case 116:
            ty -= 10;
            break;
        // g move down
        case 103:
            ty += 10;
            break;
        // f move left
        case 102:
            tx -= 10;
            break;
        // h move right
        case 104:
            tx += 10;
            break;
        // a: persp x -
        case 97:
            perspx += 0.0001;
            break;
        // d: persp x +
        case 100:
            perspx -= 0.0001;
            break;
        // w: persp y +
        case 119:
            perspy += 0.0001;
            break;
        // s: persp y -
        case 115:
            perspy -= 0.0001;
            break;
        case 27:
            return 0;
            break;
        }
    }

    // Release memory
    src.release();

    return 0;
}
