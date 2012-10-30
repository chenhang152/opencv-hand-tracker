//============================================================================
// Name        : hand_tracker.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "libconfig.h++"
#include "opencv2/opencv.hpp"
#include <tclap/CmdLine.h>
#include <GL/glut.h>
#include <pthread.h>

using namespace std;
using namespace libconfig;
using namespace cv;

//============================================================================
//Roba necessaria
//============================================================================

#define	HMIN 0
#define HMAX 1
#define SMIN 2
#define SMAX 3
#define VMIN 4
#define VMAX 5
#define ERODEELEM 6
#define	ERODESIZE 7

Mat hsvImage;
struct fingerConf
{
	string name;
	int data[8];
	string color;
};
//============================================================================



//============================================================================
//GLOBALS
//============================================================================
vector<string> fingers_name;
vector<string> entries_name;
vector<fingerConf> fingers_data;
vector<Point3i> fingers_3d;

Config cfg;

Mat depthMap;
Mat bgrImage=Mat::zeros(640,480,CV_8UC3);

int zmin=0;
int zmax=5000;
int registration=0;

string openglWIN ="OpenGL";
string configFile;
float glRotateParam=0;
int Pause=0;


//============================================================================

//KEYBOARD EVENTS
//============================================================================
void keyboard_Events(char key,VideoCapture &capObj)
{
	switch(key)
	{
	case 'q':
		exit(0);
		break;
	case 'p':
		if(Pause==0) {printf("Paused\n");Pause=1;}
		else{printf("Play\n");Pause=0;}
		break;
	case 'r':
		if (registration==0) {
			registration=1;
			capObj.set(CV_CAP_PROP_OPENNI_REGISTRATION,registration);
			printf("Activating pixel registration\n");
		}

		else
		{
			registration=0;
			capObj.set(CV_CAP_PROP_OPENNI_REGISTRATION,registration);
			printf("De-Activating pixel registration\n");
		}
		break;
	}
}
//============================================================================


//============================================================================
//Configuration file access
//============================================================================

void read_conf_file(int debug)
{
	//INIZIALIZZO LE DITA
	//============================================================================
	fingers_name.push_back("index");
	fingers_name.push_back("middle");
	fingers_name.push_back("ring");
	fingers_name.push_back("pinky");
	fingers_name.push_back("thumb");

	//INIZIALIZZO I CAMPI DEL FILE DI CONF
	//============================================================================
	entries_name.push_back("hmin");
	entries_name.push_back("hmax");
	entries_name.push_back("smin");
	entries_name.push_back("smax");
	entries_name.push_back("vmin");
	entries_name.push_back("vmax");
	entries_name.push_back("erodeElem");
	entries_name.push_back("erodeSize");
	entries_name.push_back("color");

	//ACCEDO AL FILE DI CONF
	//============================================================================
	cfg.readFile(configFile.c_str());

	//PER OGNI DITO CREO UNA STRUTTURA E LA POPOLO CON OGNI VALORE PRESENTE NEL FILE DI CONF
	//============================================================================
	for(int i=0;i<fingers_name.size();i++)
	{
		//istanzio il dito
		fingerConf theFinger;
		//salvo il nome del dito nella stringa adatta
		theFinger.name=fingers_name[i];


		//inizio il ciclo per salvare i valori numerici
		for(int j=0;j<entries_name.size()-1;j++)
		{
			char path[50];
			sprintf(path,"%s.%s",fingers_name[i].c_str(),entries_name[j].c_str());
			Setting& s = cfg.lookup(path);

			theFinger.data[j]=s;
		}

		//mi resta solo da salvare il nome del colore nell'ultimo campo string
		char path[50];
		sprintf(path,"%s.%s",fingers_name[i].c_str(),entries_name[entries_name.size()-1].c_str());
		Setting& s = cfg.lookup(path);
		string tmp=s;
		theFinger.color=tmp;

		//a questo punto posso salvare il dito nel vettore
		fingers_data.push_back(theFinger);

	}

	//DEBUG, VERIFICO DI AVER LETTO E SALVATO CORRETTAMENTE
	//============================================================================
	if(debug)
	{
		printf("Fingers: %d \n",(int)fingers_data.size());
		for(int i=0;i<(int)fingers_data.size();i++)
		{
			printf("Dito:\t%s\tColore:\t%s \n",fingers_data[i].name.c_str(),fingers_data[i].color.c_str());
		}
	}
}
//============================================================================



//============================================================================
//OPENCV INIT
//============================================================================
void opencv_init(VideoCapture &cap)
{
	//INIZIALIZZO FINESTRA OPENCV
	cap.set(CV_CAP_PROP_OPENNI_REGISTRATION,registration);
	namedWindow("RGB",CV_WINDOW_AUTOSIZE | CV_WINDOW_NORMAL);
	namedWindow(openglWIN,CV_WINDOW_OPENGL | CV_WINDOW_AUTOSIZE);

	createTrackbar( "Z min", "RGB", &zmin, 5000,  NULL);
	createTrackbar( "Z max", "RGB", &zmax, 5000,  NULL);
}
//============================================================================



//============================================================================
//Help function
//============================================================================

void help()
{
	printf("\nEntering main loop...\n");
	printf("==================================================\n");
	printf("#Commands:b\n");
	printf("q) quit \n");
	printf("r) toggle pixel registration \n");
	printf("==================================================\n");
}

//============================================================================


//============================================================================
//OPENGL CALLBACK
//============================================================================

void DrawAxes(float length)
{
	glPushMatrix();
	glScalef(length, length, length);

	glLineWidth(2.f);
	glBegin(GL_LINES);

	// x red
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(1.f, 0.f, 0.f);

	// y green
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 1.f, 0.f);

	// z blue
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 1.f);

	glColor3f(1.0f,1.0f,1.0f);

	glEnd();
	glLineWidth(1.f);

	glPopMatrix();
}

void openGL(void* param)
{

	glEnable(GL_DEPTH_TEST);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-640,640,-480,480,-1000,1000);

	gluLookAt(320,240,320,
			0,0,0,
			0,1,0);


	/*
	glPushMatrix();
	glRotatef(glRotateParam,0,1,0);
	glutWireCube(100.0f);
	glPopMatrix();
	 */

	glBegin(GL_LINES);
	glVertex3f(0,50,-200);
	glVertex3f(0,50,-300);
	glEnd();

	glPushMatrix();
	glTranslatef(0,50,-200);
	glutWireCone(10,30,5,5);
	glPopMatrix();

	for(int i=0;i<(int)fingers_3d.size();i++)
	{
		glPushMatrix();
		glTranslatef(fingers_3d[i].x,fingers_3d[i].y,0);
		glutWireSphere(10,10,10);
		glPopMatrix();
	}

	glPushMatrix();
	DrawAxes(100);
	glPopMatrix();

}


void miniImage(Mat &dest,Mat &source,Point tl, Point br)
{
	for(int i=1;i<120;i++)
	{

		for(int j=1;j<160;j++)
		{

			dest.at<Vec3b>(j+i*dest.cols)[0]=source.at<uchar>(j+i*source.cols);
			dest.at<Vec3b>(j+i*dest.cols)[1]=source.at<uchar>(j+i*source.cols);
			dest.at<Vec3b>(j+i*dest.cols)[2]=source.at<uchar>(j+i*source.cols);

		}
	}

	rectangle(bgrImage, tl, br,Scalar(0,0,255));
}

int main(int argc, char** argv) {

	//COMMAND LINE PARSING
	//============================================================================
	try {

		TCLAP::CmdLine cmd("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nHand tracker - Maurilio Di Cicco, Jacopo Serafin\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", ' ', "0.1");
		TCLAP::ValueArg<std::string> confArg("c","configFile","Config file to open",false,"color.cfg","string");
		cmd.add( confArg );
		cmd.parse( argc, argv );
		configFile = confArg.getValue();
		std::cout << "Config file requested is: " << configFile << std::endl;

	}
	catch (TCLAP::ArgException &e)
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}
	//============================================================================

	//Leggo il file di configurazione
	read_conf_file(1);

	//Inizializzo openCV
	VideoCapture capture(CV_CAP_OPENNI);
	opencv_init(capture);

	//GLUT INIT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glClearColor(0,0,0,0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//Prints help messages
	help();

	resizeWindow(openglWIN, 640, 480);
	setOpenGlDrawCallback(openglWIN, openGL);

	while(1)
	{

		capture.grab();
		capture.retrieve( depthMap, CV_CAP_OPENNI_DEPTH_MAP );
		capture.retrieve( bgrImage, CV_CAP_OPENNI_BGR_IMAGE );

		int cols=depthMap.cols;
		int rows=depthMap.rows;

		int t[2];
		t[0]=depthMap.cols;
		t[1]=depthMap.rows;

		for(int i=0;i<rows;i++)
		{
			for(int j=0;j<cols;j++)
			{
				if(depthMap.at<short>(j+i*cols)>zmax || depthMap.at<short>(j+i*cols)<zmin)
				{
					bgrImage.at<Vec3b>(j+i*cols)[0]=0;
					bgrImage.at<Vec3b>(j+i*cols)[1]=0;
					bgrImage.at<Vec3b>(j+i*cols)[2]=0;
				}
			}
		}

		//Converto l'immagine BGR in HSV
		cvtColor(bgrImage,hsvImage, CV_BGR2HSV);

		//Istanzio la mini-image per mostrare la maschera

		Mat maskImage=Mat::zeros(480,640,CV_8UC1);

		for(int i =0; i<(int)fingers_data.size();i++)
		{


			Mat tmpHSV=hsvImage;
			//Filtro l'immagine hsv per ottere una binaria con i parametri di ogni dito
			inRange(tmpHSV,
					Scalar(fingers_data[i].data[HMIN],fingers_data[i].data[SMIN],fingers_data[i].data[VMIN]),
					Scalar(fingers_data[i].data[HMAX],fingers_data[i].data[SMAX],fingers_data[i].data[VMAX]),tmpHSV);


			//EROSIONE
			//============================================================================
			int erosion_type;
			if( fingers_data[i].data[ERODEELEM] == 0 ){ erosion_type = MORPH_RECT; }
			else if( fingers_data[i].data[ERODEELEM] == 1 ){ erosion_type = MORPH_CROSS; }
			else if( fingers_data[i].data[ERODEELEM] == 2) { erosion_type = MORPH_ELLIPSE; }


			Mat element = getStructuringElement( erosion_type,
					Size( 2*fingers_data[i].data[ERODESIZE] + 1, 2*fingers_data[i].data[ERODESIZE]+1 ),
					Point( fingers_data[i].data[ERODESIZE], fingers_data[i].data[ERODESIZE] ) );

			erode( tmpHSV, tmpHSV, element );
			//============================================================================

			//Aggiungo i pixel mascherati alla maschera totale

			maskImage+=tmpHSV;

			//BLOB
			//============================================================================
			SimpleBlobDetector::Params parametri;
			parametri.filterByArea=1;
			parametri.maxArea=10000;
			parametri.minArea=2;
			SimpleBlobDetector *blobDetector=new SimpleBlobDetector(parametri);
			blobDetector->create("SimpleBlobDetector");
			vector<KeyPoint> punti;
			blobDetector->detect(tmpHSV,punti);

			Point2i mediaBlob;
			mediaBlob.x=0;
			mediaBlob.y=0;


			//Disegno i cerchi facendo la media delle coordinate utili
			//============================================================================
			int size=(int)punti.size();

			if(size!=0)
			{
				for(int i=0;i<size;i++)
				{
					mediaBlob.x+=punti[i].pt.x;
					mediaBlob.y+=punti[i].pt.y;
				}
				mediaBlob.x=(int)(mediaBlob.x/size);
				mediaBlob.y=(int)(mediaBlob.y/size);
				circle(bgrImage,mediaBlob,10,Scalar(0,0,255));

				Point3i dito3d;
				dito3d.x=mediaBlob.x;
				dito3d.y=mediaBlob.y;

				fingers_3d.push_back(dito3d);
			}


		}


		resize(maskImage,maskImage,Size(160,120),0,0,INTER_NEAREST);
		miniImage(bgrImage,maskImage,Point(0,0),Point(160,120));

		if(Pause==0)
		{
			imshow("RGB",bgrImage);
		}

		//update GL window
		updateWindow(openglWIN);
		fingers_3d.clear();

		//Keyboard event routine
		keyboard_Events(waitKey(33),capture);
	}

	return 0;
}