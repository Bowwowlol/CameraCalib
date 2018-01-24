#include "cv.h"
#include "cxmisc.h"
#include "highgui.h"
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>

#include <direct.h>

#include <fstream>
#include <iomanip>
#include <iostream>

#include <math.h>

#include "..//ImageCorrection//ImageCorrection.h"
using namespace std;


#ifndef _StereoCalib_h_
#define _StereoCalib_h_




class Stereo
{
public:
	Image Ima;
	
	int nx;
	int ny;
    float squareSize;

    
	
	
	//CvSize imageSize;
	void StereoCalib(const char* imageList, int useUncalibrated);
	

private:


};


#endif