/**
 * @file MatchTemplate_Demo.cpp
 * @brief Sample code to use the function MatchTemplate
 * @author OpenCV team
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/// Global Variables
Mat img; Mat templ; Mat result;
const char* image_window = "Source Image";
const char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;

/// Function Headers
void MatchingMethod( int, void* );

/**
 * @function main
 */
int main( int argc,  char** argv )
{

  //check input

  if (argc != 5)
    {
    std::cerr << "command line error, help: /MatchTemplate_Demo input_img templ_img startrows startcols" << std::endl;
    return -1;
    }
  /// Load image and template
  img = imread( argv[1], 1 );
  templ = imread( argv[2], 1 );


  //Put zero values in template region
  const  int startrows = atoi(argv[3]);
  const  int startcols= atoi(argv[4]);
	   	
  const int nbTemplateRows = templ.rows;
  const int nbTemplateCols = templ.cols;

  std::cout << "templ rows and cols " << nbTemplateRows << "," << nbTemplateCols << std::endl;
  std::cout << "start templs rows and cols " << startrows << "," << startcols << std::endl;	

   for(int counter_cols=0; counter_cols<nbTemplateCols;counter_cols++){
  	for(int counter_rows=0; counter_rows<nbTemplateRows; counter_rows++){
	Vec3b & color = img.at<Vec3b>(counter_rows+startrows,counter_cols+startcols);
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
  	}
  }		
  /////////////////////////////////////////////////////////////
  /// Create windows
  //namedWindow( image_window, WINDOW_AUTOSIZE );
  //namedWindow( result_window, WINDOW_AUTOSIZE );

  /// Create Trackbar
  //const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
  //createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );

  //MatchingMethod( 0, 0 );

  //waitKey(0);
  /////////////////////////////////////////////////////////////


  //test here to compare result
  /// Create the result matrix
  int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create( result_cols, result_rows, CV_32FC1 );
	
  matchTemplate( img, templ, result, 0 );

  //normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
	
  std::cout << "Min value / Max value: " << minVal << " / " << maxVal << std::endl;
  return 0;
}

/**
 * @function MatchingMethod
 * @brief Trackbar callback
 */
void MatchingMethod( int, void* )
{
  /// Source image to display
  Mat img_display;
  img.copyTo( img_display );

  /// Create the result matrix
  int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create( result_cols, result_rows, CV_32FC1 );

  /// Do the Matching and Normalize
  matchTemplate( img, templ, result, match_method );
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );


  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
  if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }

  /// Show me what you got
  rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
  rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );

  imshow( image_window, img_display );
  imshow( result_window, result );

  return;
}
