#include "cv.h"
#include "cxmisc.h"
#include "highgui.h"
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>

#include <fstream>
#include <iomanip>
#include <iostream>

#include <math.h>

using namespace std;


#ifndef _ImageCorrection_h_
#define _ImageCorrection_h_




class Image
{
public:
	

	double IIx[65],IIy[65],Ix[2961],Iy[2961];
	double fhxz[2961],fhyz[2961],hcxz[2961],hcyz[2961],r[2961],hyz[2961],hxz[2961];
	double T[2*2961][8],e[2961*2][1];
	double r_dist[2961];

	double l_u0;
	double l_v0;
	double l_fu;
	double l_fv;
	double l_kc[5];
	double r_u0;
	double r_v0;
	double r_fu;	
	double r_fv;
	double r_kc[5];
	double u[8],v[8];
	double p[8];

	char str[50];
	double value;

	int k;
	int num;
	int i,j;

	void image_correction_left();
	void Image::image_correction_right();
	
	
	

private:


};


#endif