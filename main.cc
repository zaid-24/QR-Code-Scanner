#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
void display(Mat &im, Mat &points)
{
  int i;
  int n = points.rows;
  for(i = 0 ; i < n ; i++)
  {
    line(im, Point2i(points.at<float>(i,0), points.at<float>(i,1)),
    Point2i(points.at<float>((i+1)%n,0), points.at<float>((i+1)%n,1)), Scalar(255,0,0), 3);
  }
  imshow("windowName", im);
}
int main(int argc, char* argv[]) {
  Mat getImage;
  if(argc>1)
    getImage = imread(argv[1]);
  else
    getImage = imread("filename.jpg");
  QRCodeDetector qrDet = QRCodeDetector::QRCodeDetector();
  Mat points, rectImage;
  std::string data = qrDet.detectAndDecode(getImage, points, rectImage);
  if(data.length()>0)
  {
    cout << "Data after decoding: " << data << endl;
    display(getImage, points);
    rectImage.convertTo(rectImage, CV_8UC3);
    imshow("Rectified QRCode", rectImage);
    waitKey(0);
  }
  else {
    cout << "QR Code not detected" << endl;
  }
}