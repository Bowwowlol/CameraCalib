#include "ImageCorrection.h"

void Image::image_correction_left()
{
	
	
	

k=1;
for (i=5;i<=315;i=i+5)
{
		IIx[k]=i;
        k=k+1;
	/*
		remove ("IIx.txt");
		fstream xx("IIx.txt",ios::app);
		for(int fuck=1;fuck<=63;fuck++)
		{
			xx << IIx[fuck] << endl;
		}		
			xx.close();
	*/
}
k=1;
for (j=5;j<=235;j=j+5)
{
	IIy[k]=j;
	k=k+1;
}
num=1;
for (i=1;i<=63;i++)
{
    for (j=1;j<=47;j++)
	{
        Ix[num]=IIx[i];
        Iy[num]=IIy[j];
        num=num+1;

		
	}
}
//块タ把计*********************************************
/*	
fstream in_Camera( "kc.txt", ios::in );
if(!in_Camera)	exit(1);
	while( in_Camera >> str >> value )
	{
		if ( !strcmp( str, "l_u0" ) )	                      l_u0						= value;
		else if ( !strcmp( str, "l_v0" ) )						  l_v0						= value;
		else if ( !strcmp( str, "l_fu" ) )                        l_fu						= value;
		else if ( !strcmp( str, "l_fv" ) )                        l_fv						= value;
		else if ( !strcmp( str, "r_u0" ) )						  r_u0						= value;
		else if ( !strcmp( str, "r_v0" ) )						  r_v0						= value;
		else if ( !strcmp( str, "r_fu" ) )                        r_fu						= value;
		else if ( !strcmp( str, "r_fv" ) )                        r_fv						= value;
		else if ( !strcmp( str, "l_kc[0]" ) )	                  l_kc[0]						= value;
		else if ( !strcmp( str, "l_kc[1]" ) )					  l_kc[1]						= value;
		else if ( !strcmp( str, "l_kc[2]" ) )                     l_kc[2]						= value;
		else if ( !strcmp( str, "l_kc[3]" ) )                     l_kc[3]						= value;
		else if ( !strcmp( str, "l_kc[4]" ) )					  l_kc[4]						= value;
		else if ( !strcmp( str, "r_kc[0]" ) )					  r_kc[0]						= value;
		else if ( !strcmp( str, "r_kc[1]" ) )					  r_kc[1]						= value;
		else if ( !strcmp( str, "r_kc[2]" ) )					  r_kc[2]						= value;
		else if ( !strcmp( str, "r_kc[3]" ) )					  r_kc[3]						= value;
		else if ( !strcmp( str, "r_kc[4]" ) )					  r_kc[4]						= value;
	}
	in_Camera.close();
	*/
//*********************************************************
for (num=0;num<2961;num++)
{
        fhxz[num]=(Ix[num]-l_u0);
        fhyz[num]=(Iy[num]-l_v0);
        
        hxz[num]=fhxz[num]/l_fu;
        hyz[num]=fhyz[num]/l_fv;
        r[num]=sqrt(pow(hxz[num],2)+pow(hyz[num],2));
        
       hcxz[num]=(1 + l_kc[0]*(pow(r[num],2)) + l_kc[1]*(pow(r[num],4)) + l_kc[4]*(pow(r[num],6)))*hxz[num] + 2*l_kc[2]*hxz[num]*hyz[num] + l_kc[3]*((pow(r[num],2)) + 2*(pow(hxz[num],2)));
       hcyz[num]=(1 + l_kc[0]*(pow(r[num],2)) + l_kc[1]*(pow(r[num],4)) + l_kc[4]*(pow(r[num],6)))*hyz[num] + l_kc[2]*((pow(r[num],2)) + 2*(pow(hyz[num],2))) + 2*l_kc[3]*hxz[num]*hyz[num];
        
       
}
//*************************************************************************


for (num=0;num<2961;num++)
{        
        r_dist[num]=pow(pow(hcxz[num],2)+pow(hcyz[num],2),0.5);
        u[0]=-hcxz[num]*(pow(r_dist[num],2));u[1]=-hcxz[num]*(pow(r_dist[num],4));u[2]=-2*hcxz[num]*hcyz[num];u[3]=-(pow(r_dist[num],2)+2*pow(hcxz[num],2));
		u[4]=4*(hxz[num]-hcxz[num])*pow(r_dist[num],2);u[5]=6*(hxz[num]-hcxz[num])*pow(r_dist[num],4);u[6]=8*(hxz[num]-hcxz[num])*hcyz[num];u[7]=8*(hxz[num]-hcxz[num])*hcxz[num];
		v[0]=-hcyz[num]*(pow(r_dist[num],2));v[1]=-hcyz[num]*(pow(r_dist[num],4));v[2]=-(pow(r_dist[num],2)+2*pow(hcyz[num],2));v[3]=-2*hcxz[num]*hcyz[num];
		v[4]=4*(hyz[num]-hcyz[num])*pow(r_dist[num],2);v[5]=6*(hyz[num]-hcyz[num])*pow(r_dist[num],4);v[6]=8*(hyz[num]-hcyz[num])*hcyz[num];v[7]=8*(hyz[num]-hcyz[num])*hcxz[num];

 
        for (k=0;k<8;k++)
		{
			
			T[2*num][k]=u[k];
            T[2*num+1][k]=v[k];
            e[2*num][0]=hcxz[num]-hxz[num];
			e[2*num+1][0]=hcyz[num]-hyz[num];
		}

}

	CvMat *_T=cvCreateMat(5382,8,CV_64FC1);
	CvMat *_e=cvCreateMat(5382,1,CV_64FC1);
	CvMat *_trans_T=cvCreateMat(8,5382,CV_64FC1);
	CvMat *_TT=cvCreateMat(8,8,CV_64FC1);
	CvMat *_inv_TT=cvCreateMat(8,8,CV_64FC1);
	CvMat *_itT=cvCreateMat(8,5382,CV_64FC1);
	CvMat *_p=cvCreateMat(8,1,CV_64FC1);
	cvSetData(_T,T,_T->step);
	cvSetData(_e,e,_e->step);


cvTranspose(_T,_trans_T);
cvmMul(_trans_T,_T,_TT);
cvInvert(_TT,_inv_TT,CV_LU);
cvmMul(_inv_TT,_trans_T,_itT);
cvmMul(_itT,_e,_p);

	for(int i=0;i<8;i++)
		{
		p[i]=cvmGet( _p, i, 0 );
		
		}


	fstream Data("Camera.txt", ios::app);
			Data << "l_coefficient[0]" << setw(40) << p[0] << endl << "l_coefficient[1]" << setw(40) << p[1] <<endl;
			Data << "l_coefficient[2]" << setw(40) << p[2] << endl << "l_coefficient[3]" << setw(40) << p[3] <<endl;
			Data << "l_coefficient[4]" << setw(40) << p[4] << endl << "l_coefficient[5]" << setw(40) << p[5] <<endl;
			Data << "l_coefficient[6]" << setw(40) << p[6] << endl << "l_coefficient[7]" << setw(40) << p[7] <<endl;
			Data << endl ;
			Data.close();
			

	cvReleaseMat(&_T);
    cvReleaseMat(&_e);
    cvReleaseMat(&_trans_T);
    cvReleaseMat(&_TT);
    cvReleaseMat(&_inv_TT);
	cvReleaseMat(&_itT);
	cvReleaseMat(&_p);
}






void Image::image_correction_right()
{
	
	

k=1;
for (i=5;i<=315;i=i+5)
{
		IIx[k]=i;
        k=k+1;
	
}
k=1;
for (j=5;j<=235;j=j+5)
{
	IIy[k]=j;
	k=k+1;
}
num=1;
for (i=1;i<=63;i++)
{
    for (j=1;j<=47;j++)
	{
        Ix[num]=IIx[i];
        Iy[num]=IIy[j];
        num=num+1;

		
	}
}
//块タ把计*********************************************
/*	
fstream in_Camera( "kc.txt", ios::in );
if(!in_Camera)	exit(1);
	while( in_Camera >> str >> value )
	{
		if ( !strcmp( str, "l_u0" ) )	                      l_u0						= value;
		else if ( !strcmp( str, "l_v0" ) )						  l_v0						= value;
		else if ( !strcmp( str, "l_fu" ) )                        l_fu						= value;
		else if ( !strcmp( str, "l_fv" ) )                        l_fv						= value;
		else if ( !strcmp( str, "r_u0" ) )						  r_u0						= value;
		else if ( !strcmp( str, "r_v0" ) )						  r_v0						= value;
		else if ( !strcmp( str, "r_fu" ) )                        r_fu						= value;
		else if ( !strcmp( str, "r_fv" ) )                        r_fv						= value;
		else if ( !strcmp( str, "l_kc[0]" ) )	                  l_kc[0]						= value;
		else if ( !strcmp( str, "l_kc[1]" ) )					  l_kc[1]						= value;
		else if ( !strcmp( str, "l_kc[2]" ) )                     l_kc[2]						= value;
		else if ( !strcmp( str, "l_kc[3]" ) )                     l_kc[3]						= value;
		else if ( !strcmp( str, "l_kc[4]" ) )					  l_kc[4]						= value;
		else if ( !strcmp( str, "r_kc[0]" ) )					  r_kc[0]						= value;
		else if ( !strcmp( str, "r_kc[1]" ) )					  r_kc[1]						= value;
		else if ( !strcmp( str, "r_kc[2]" ) )					  r_kc[2]						= value;
		else if ( !strcmp( str, "r_kc[3]" ) )					  r_kc[3]						= value;
		else if ( !strcmp( str, "r_kc[4]" ) )					  r_kc[4]						= value;
	}
	in_Camera.close();
*/
//*********************************************************
for (num=0;num<2961;num++)
{
        fhxz[num]=(Ix[num]-r_u0);
        fhyz[num]=(Iy[num]-r_v0);
        
        hxz[num]=fhxz[num]/r_fu;
        hyz[num]=fhyz[num]/r_fv;
        r[num]=sqrt(pow(hxz[num],2)+pow(hyz[num],2));
        
       hcxz[num]=(1 + r_kc[0]*(pow(r[num],2)) + r_kc[1]*(pow(r[num],4)) + r_kc[4]*(pow(r[num],6)))*hxz[num] + 2*r_kc[2]*hxz[num]*hyz[num] + r_kc[3]*((pow(r[num],2)) + 2*(pow(hxz[num],2)));
       hcyz[num]=(1 + r_kc[0]*(pow(r[num],2)) + r_kc[1]*(pow(r[num],4)) + r_kc[4]*(pow(r[num],6)))*hyz[num] + r_kc[2]*((pow(r[num],2)) + 2*(pow(hyz[num],2))) + 2*r_kc[3]*hxz[num]*hyz[num];
        
       
}
//*************************************************************************


for (num=0;num<2961;num++)
{        
        r_dist[num]=pow(pow(hcxz[num],2)+pow(hcyz[num],2),0.5);
        u[0]=-hcxz[num]*(pow(r_dist[num],2));
		u[1]=-hcxz[num]*(pow(r_dist[num],4));
		u[2]=-2*hcxz[num]*hcyz[num];
		u[3]=-(pow(r_dist[num],2)+2*pow(hcxz[num],2));
		u[4]=4*(hxz[num]-hcxz[num])*pow(r_dist[num],2);
		u[5]=6*(hxz[num]-hcxz[num])*pow(r_dist[num],4);
		u[6]=8*(hxz[num]-hcxz[num])*hcyz[num];
		u[7]=8*(hxz[num]-hcxz[num])*hcxz[num];
		v[0]=-hcyz[num]*(pow(r_dist[num],2));
		v[1]=-hcyz[num]*(pow(r_dist[num],4));
		v[2]=-(pow(r_dist[num],2)+2*pow(hcyz[num],2));
		v[3]=-2*hcxz[num]*hcyz[num];
		v[4]=4*(hyz[num]-hcyz[num])*pow(r_dist[num],2);
		v[5]=6*(hyz[num]-hcyz[num])*pow(r_dist[num],4);
		v[6]=8*(hyz[num]-hcyz[num])*hcyz[num];
		v[7]=8*(hyz[num]-hcyz[num])*hcxz[num];

 
        for (k=0;k<8;k++)
		{
			
			T[2*num][k]=u[k];
            T[2*num+1][k]=v[k];
            e[2*num][0]=hcxz[num]-hxz[num];
			e[2*num+1][0]=hcyz[num]-hyz[num];
		}

}

	CvMat *_T=cvCreateMat(5382,8,CV_64FC1);
	CvMat *_e=cvCreateMat(5382,1,CV_64FC1);
	CvMat *_trans_T=cvCreateMat(8,5382,CV_64FC1);
	CvMat *_TT=cvCreateMat(8,8,CV_64FC1);
	CvMat *_inv_TT=cvCreateMat(8,8,CV_64FC1);
	CvMat *_itT=cvCreateMat(8,5382,CV_64FC1);
	CvMat *_p=cvCreateMat(8,1,CV_64FC1);
	cvSetData(_T,T,_T->step);
	cvSetData(_e,e,_e->step);


cvTranspose(_T,_trans_T);
cvmMul(_trans_T,_T,_TT);
cvInvert(_TT,_inv_TT,CV_LU);
cvmMul(_inv_TT,_trans_T,_itT);
cvmMul(_itT,_e,_p);

	for(int i=0;i<8;i++)
		{
		p[i]=cvmGet( _p, i, 0 );
		
		}


	fstream Data("Camera.txt", ios::app);
			Data << "r_coefficient[0]" << setw(40) << p[0] << endl << "r_coefficient[1]" << setw(40) << p[1] <<endl;
			Data << "r_coefficient[2]" << setw(40) << p[2] << endl << "r_coefficient[3]" << setw(40) << p[3] <<endl;
			Data << "r_coefficient[4]" << setw(40) << p[4] << endl << "r_coefficient[5]" << setw(40) << p[5] <<endl;
			Data << "r_coefficient[6]" << setw(40) << p[6] << endl << "r_coefficient[7]" << setw(40) << p[7] <<endl;
			Data << endl ;
			Data.close();
			

	cvReleaseMat(&_T);
    cvReleaseMat(&_e);
    cvReleaseMat(&_trans_T);
    cvReleaseMat(&_TT);
    cvReleaseMat(&_inv_TT);
	cvReleaseMat(&_itT);
	cvReleaseMat(&_p);
}
