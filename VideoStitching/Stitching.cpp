#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

#include "./opencv2/core/core.hpp"
#include "./opencv2/features2d/features2d.hpp"
#include "./opencv2/highgui/highgui.hpp"
#include "./opencv2/calib3d/calib3d.hpp"
#include "./opencv2/imgproc/imgproc.hpp"
#include "./opencv2/xfeatures2d.hpp"
#include "./opencv2/xfeatures2d/nonfree.hpp"
#include "./opencv2/stitching.hpp"

using namespace cv;
using namespace cv::xfeatures2d;

#define THUMBNAIL_WIDTH     130
#define THUMBNAIL_HEIGHT    150
#define MARGIN              15

// OpenCV Libraries
#ifdef _DEBUG
#pragma comment(lib, "../OpenCV/x86/lib/opencv_calib3d300d.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_core300d.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_features2d300d.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_flann300d.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_highgui300d.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_imgcodecs300d.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_imgproc300d.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_photo300d.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_stitching300d.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_videoio300d.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_video300d.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_xfeatures2d300d.lib")

#else
#pragma comment(lib, "../OpenCV/x86/lib/opencv_calib3d300.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_core300.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_features2d300.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_flann300.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_highgui300.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_imgcodecs300.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_imgproc300.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_photo300.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_stitching300.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_videoio300.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_video300.lib")
#pragma comment(lib, "../OpenCV/x86/lib/opencv_xfeatures2d300.lib")
#endif

/**************************** Image Stitching Steps ****************************
* 1. Video Parsing.
* 2. Stitch First 2 Images.
* 3. Calculate the rotation and transformation based on the former image.
* 4. Calculate the overall rotation and transformation relative to the First Image.
* 5. Create the Whole Image.
********************************************************************************/

/////////////////////////////////////////////////////////////////////////////////
/// \brief Load the Video and make thumbnails.
/////////////////////////////////////////////////////////////////////////////////

void MainWindow::LoadVideo()
{
	// Clear the Old Images
	m_nIndex = 0;
	m_aryImages.clear();

	// Clear the Scenes
	m_hFrameScene.clear();
	m_hStitchScene.clear();

	char strPath[1024] = "";
	strcpy_s(strPath, (const char*)m_strVideoFile.toLocal8Bit());
	
	if (!m_hCapture.open(strPath))
	{
		qDebug() << strPath;
		SetStatus(tr("Could Not File Found : %1").arg(m_strVideoFile));
		return;
	}

	m_nFPS			= (int) m_hCapture.get(CV_CAP_PROP_FPS);
	m_nWidth		= (int) m_hCapture.get(CV_CAP_PROP_FRAME_WIDTH);
	m_nHeight		= (int) m_hCapture.get(CV_CAP_PROP_FRAME_HEIGHT);
	m_nFrameCount	= (int) m_hCapture.get(CV_CAP_PROP_FRAME_COUNT);

	ui->m_lblStatus->setText(tr("  FPS: %1, Width: %2, Height: %3, Frames: %4, Path: %5")
		.arg(m_nFPS)
		.arg(m_nWidth)
		.arg(m_nHeight)
		.arg(m_nFrameCount)
		.arg(strPath));

	cv::Mat frame;
	m_hCapture >> frame;

	if (frame.empty())
	{
		m_bEndFlag = true;
		ui->m_lblStatus->setText(tr("Video Empty."));
		m_pTimer->stop();
		return;
	}
	
	int w = frame.cols;
	int h = frame.rows;

	if (w < 320|| h < 240)
	{
		m_Frame= frame;
	}
	else
	{
		float wscale = w / 240.0f;
		float hscale = h / 240.0f;

		float scale = wscale < hscale ? wscale:hscale;
		w = w / scale;
		h = h / scale;

		cv::resize(frame, m_Frame, cv::Size(w, h));
	}


	cv::Mat inMat = m_Frame.clone();
	cv::cvtColor(inMat, inMat, CV_BGR2RGB);
	m_pStitchedItem = m_hStitchScene.addPixmap(QPixmap::fromImage(cvMatToQImage(inMat)));

	cv::resize(m_Frame,m_CurFrame,cv::Size(w/2, h/2));

	m_PrevFrame		= m_Frame.clone();   
	m_PrevKeyFrame	= m_CurFrame.clone();

	m_bCameraMode	=	false;
	m_bCameraStart	=	false;
	m_bEndFlag		=	false;
	return;
}

void MainWindow::LoadCamera()
{
	m_nIndex = 0;
	m_aryImages.clear();

	// Clear the Scenes
	m_hFrameScene.clear();
	m_hStitchScene.clear();	

	m_hCapture.open(0);

	cv::Mat frame;
	m_hCapture >> frame;

	if (frame.empty())
	{
		m_bEndFlag = true;
		ui->m_lblStatus->setText(tr("  %1 Frame Processed.").arg(m_nIndex));
		m_pTimer->stop();
		return;
	}
	
	int w = frame.cols;
	int h = frame.rows;

	if (w < 320|| h < 240)
	{
		m_Frame= frame;
	}
	else
	{
		float wscale = w / 240.0f;
		float hscale = h / 240.0f;

		float scale = wscale < hscale ? wscale:hscale;
		w = w / scale;
		h = h / scale;

		cv::resize(frame, m_Frame, cv::Size(w, h));
	}
	    
	cv::Mat inMat = m_Frame.clone();
	cv::cvtColor(inMat, inMat, CV_BGR2RGB);
	m_pStitchedItem = m_hStitchScene.addPixmap(QPixmap::fromImage(cvMatToQImage(inMat)));

	cv::resize(m_Frame,m_CurFrame,cv::Size(w/2, h/2));

	

	m_PrevFrame=m_Frame.clone();   
	m_PrevKeyFrame=m_CurFrame.clone();

	m_bEndFlag		=	false;	
	m_bCameraMode	=	true;
	m_bCameraStart	=	false;
	m_pTimer->start(1);
}
/////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::Stitch
/// Stitch 2 Images
/////////////////////////////////////////////////////////////////////////////////
void MainWindow::GetKeyFrames()
{
	if (m_bEndFlag == true)
		return;

	if (m_bRun == false)/*click 'PLAY'*/
	{		
		m_aryImages.clear();
		m_hFrameScene.clear();
	
		/*Show StopIcon*/
		QIcon icon;
		icon.addFile(QStringLiteral(":/Res/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
		ui->m_btnPlay->setIcon(icon);
		
		m_bRun=true;/*STOP available*/

		if (m_hCapture.isOpened() == false)
			return;

		if(m_bCameraMode==true)
			m_bCameraStart = true;  //Camera start

		m_pTimer->start(1);        
		return;
	}
	else/*click 'STOP'*/
	{		
		QIcon icon;
		icon.addFile(QStringLiteral(":/Res/Play.png"), QSize(), QIcon::Normal, QIcon::Off);
		ui->m_btnPlay->setIcon(icon);

		if(m_bCameraMode==true)
		{
			m_bCameraStart = false;	//Camera stop
		}
		else
		{
			m_pTimer->stop();
		}

		m_bRun=false; //PLAY available
	}
}

void MainWindow::Stitch()
{
	if(m_bRun==true)
	{
		ui->m_lblStatus->setText(tr("After click stop button, press snapshot button!"));
		return;
	}

	// Save the Panorama Result
	Mat panorama;
	
	// Create the Warper - Sphere, Cylinder, Plane
	Stitcher stitcher = Stitcher::createDefault();
//	SphericalWarper* warper = new SphericalWarper();
// 	PlaneWarper* warper = new PlaneWarper();
	CylindricalWarper* warper = new CylindricalWarper();

	// Set the Warper
	stitcher.setWarper(warper);
	
	// Estimate perspective transforms between images
	Stitcher::Status status;
	try
	{
		status = stitcher.estimateTransform(this->m_aryImages);
	}
	catch(Exception e)
	{
		ui->m_lblStatus->setText(tr("Cannot understand Camera Location and Rotation"));
		return;
	}

	switch (status)
	{
	case Stitcher::ERR_NEED_MORE_IMGS  :
		{
			ui->m_lblStatus->setText(tr("Needed The More Images..."));
			return;

		}
	case Stitcher::ERR_CAMERA_PARAMS_ADJUST_FAIL :
		{
			ui->m_lblStatus->setText(tr("Please Adjust Camera Param!"));
			return;
		}
	case Stitcher::ERR_HOMOGRAPHY_EST_FAIL:
		{
			ui->m_lblStatus->setText(tr("Can Not Join The Images!"));
			return;
		}
	}
	

	// Make panorama
	try
	{
		//stitcher.setBlender(new detail::MultiBandBlender());
		stitcher.setBlender(new detail::FeatherBlender());
		status = stitcher.composePanorama(panorama);
	}
	catch(Exception e)
	{
		ui->m_lblStatus->setText(tr("Cannot understand Camera Location and Rotation"));
		return;
	}

	switch (status)
	{
	case Stitcher::ERR_NEED_MORE_IMGS  :
		{
			ui->m_lblStatus->setText(tr("Needed The More Images..."));
			return;

		}
	case Stitcher::ERR_CAMERA_PARAMS_ADJUST_FAIL :
		{
			ui->m_lblStatus->setText(tr("Please Adjust Camera!"));
			return;
		}
	case Stitcher::ERR_HOMOGRAPHY_EST_FAIL:
		{
			ui->m_lblStatus->setText(tr("Cannot understand Camera Location and Rotation"));
			return;
		}
	}

	cv::cvtColor(panorama, panorama, CV_BGR2RGB);

	// Save to the file.
	m_pStitchedItem->setPixmap( QPixmap::fromImage(cvMatToQImage(panorama)) );
}

/**************************** Image Stitching Steps ****************************
* The main parts of stitching algorithm are as follows.
* 1. Finding Surf descriptors in both images.
* 2. Matching the surf descriptors between two images.
* 3. Using  RANSAC to estimate the homography matrix using the matched surf descriptors.
* 4. Warping the images based on the homography matrix.
********************************************************************************/
////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::Stitch2Images
/// \param image1[in]   : Input Image1
/// \param image2[in]   : Input Image2
/// return [out]        : Rotation and Transformation of Image2 Based on the Image1
////////////////////////////////////////////////////////////////////////////////////
void MainWindow::Stitch2Images(cv::Mat image1, cv::Mat image2)
{
	// Convert to Grayscale
	cv::Mat gray_image1, gray_image2;
	cvtColor( image1, gray_image1, CV_RGB2GRAY );
	cvtColor( image2, gray_image2, CV_RGB2GRAY );

	// If failed, return.
	if( !gray_image1.data || !gray_image2.data )
	{
		return;
	}

	//-- Step 1: Detect the keypoints using SURF Detector
	int minHessian = 400;
	Ptr<SIFT> detector = SIFT::create(minHessian);

	vector< KeyPoint > keypoints_object, keypoints_scene;

	detector->detect( gray_image1, keypoints_object );
	detector->detect( gray_image2, keypoints_scene );

	//-- Step 2: Calculate descriptors (feature vectors)
	Ptr<SIFT> extractor = SIFT::create();

	Mat descriptors_object, descriptors_scene;

	extractor->compute( gray_image1, keypoints_object, descriptors_object );
	extractor->compute( gray_image2, keypoints_scene, descriptors_scene );

	//-- Step 3: Matching descriptor vectors using FLANN matcher
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match( descriptors_object, descriptors_scene, matches );

	double max_dist = 0; double min_dist = 10000;

	//-- Quick calculation of max and min distances between keypoints
	for( int i = 0; i < descriptors_object.rows; i++ )
	{
		double dist = matches[i].distance;
		
		if( dist < min_dist ) min_dist = dist;
		if( dist > max_dist ) max_dist = dist;
	}

	if(min_dist==0) return;

	//-- Use only "good" matches (i.e. whose distance is less than 3*min_dist )
	std::vector< DMatch > good_matches;
	for( int i = 0; i < descriptors_object.rows; i++ )
	{
		if( matches[i].distance <= 3*min_dist )
		{
			good_matches.push_back( matches[i]);
		}
	}

	if (good_matches.size() == 0) {
		m_bRun = true;

		OnStart();
		qWarning()<<"warning is 0";

	    return;
	}

	int i = 0;
	std::vector< Point2f > obj;
	std::vector< Point2f > scene;
	int dx = 0;
	int dy = 0;

	for( i = 0; i < (int)good_matches.size(); i++ )
	{
		//-- Get the keypoints from the good matches
		obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
		scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );

		dx += abs(keypoints_scene[ good_matches[i].trainIdx ].pt.x - keypoints_object[ good_matches[i].queryIdx ].pt.x);
		dy += abs(keypoints_scene[ good_matches[i].trainIdx ].pt.y - keypoints_object[ good_matches[i].queryIdx ].pt.y);
	}

	dx = dx/good_matches.size();
	dy = dy/good_matches.size();

	if ((dx>image1.cols*0.7) || (dy>image1.rows*0.7 ))
	{
		m_bRun = true;

		OnStart();
		qWarning()<<"warning is 1";

	    return;
	}

	if ((obj.size()<4) || (scene.size()<4))
	{
		return;
	}

	// Find the Homography Matrix
	Mat H = findHomography( obj, scene, CV_RANSAC );
	if ((H.cols==0) || (H.rows==0))
	{
		m_bRun = true;

		OnStart();
		qWarning()<<"warning is 2";

		return;
	}

	cv::Mat inMat = m_Frame.clone();
	cv::cvtColor(inMat, inMat, CV_BGR2RGB);
	m_pStitchedItem->setPixmap(QPixmap::fromImage(cvMatToQImage(inMat)));
	
	if ( (dx>image1.cols*0.5) || (dy>image1.rows*0.5) )
	{
	    cv::resize(m_PrevFrame,m_PrevKeyFrame,cv::Size(m_PrevFrame.cols/2, m_PrevFrame.rows/2));

		AddFrame(m_PrevFrame);
        m_PrevFrame = m_Frame.clone();

	    return;
	}
	m_PrevFrame=m_Frame.clone();
}


void MainWindow::AddFrame(cv::Mat frame)
{
	cv::Mat inMat = frame.clone();

	int nIndex = m_aryImages.size();
	m_aryImages.push_back(frame.clone());

	cv::cvtColor(inMat, inMat, CV_BGR2RGB);
	/*if (frame.channels() == 3)
	{
		cv::cvtColor(inMat, inMat, CV_BGR2RGB);
	}
	else if (frame.channels() == 4)
	{
		cv::cvtColor(inMat, inMat, CV_BGRA2RGBA);
	}*/

	QPixmap pixmap = QPixmap::fromImage(cvMatToQImage(inMat));
	if (pixmap.width() > pixmap.height())
	{
	 cv::Mat inMat = m_Frame.clone();
 cv::cvtColor(inMat, inMat, CV_BGR2RGB);
 m_pStitchedItem->setPixmap(QPixmap::fromImage(cvMatToQImage(inMat)));	pixmap = pixmap.scaledToWidth(THUMBNAIL_WIDTH - MARGIN*2);
	}
	else
	{
		pixmap = pixmap.scaledToHeight(THUMBNAIL_WIDTH - MARGIN*2);
	}

	QGraphicsPixmapItem *pItem = m_hFrameScene.addPixmap(pixmap);
	pItem->setX( (THUMBNAIL_WIDTH - pixmap.width())/2 );
	pItem->setY( (pixmap.height() + MARGIN) * nIndex + MARGIN);
	pItem->setFlag(QGraphicsItem::ItemIsSelectable, true);

	m_pStitchedItem->setPixmap(QPixmap::fromImage(cvMatToQImage(inMat)));
	inMat.release();
}


QImage MainWindow::cvMatToQImage(cv::Mat inMat )
{
	switch ( inMat.type() )
	{
		// 8-bit, 4 channel
	case CV_8UC4:
		{
			return QImage( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );;
		}

		// 8-bit, 3 channel
	case CV_8UC3:
		{
			return QImage( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );
		}

		// 8-bit, 1 channel
	case CV_8UC1:
		{
			static QVector<QRgb>  sColorTable;

			// only create our color table once
			if ( sColorTable.isEmpty() )
			{
				for ( int i = 0; i < 256; ++i )
					sColorTable.push_back( qRgb( i, i, i ) );
			}

			QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );
			image.setColorTable( sColorTable );

			return image;
		}

	default:
		break;
	}

	return QImage();
}


/**************************** Image Stitching Steps ****************************
* 1. Load Videos
* 2. Select every 5 frames.
* 3. Do the Optical Flow to get the homograph.
* 4.
* 3. Calculate the rotation and transformation based on the former image.
* 4. Calculate the overall rotation and transformation relative to the First Image.
* 5. Create the Whole Image.
********************************************************************************/

/////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::OnTimer
/////////////////////////////////////////////////////////////////////////////////
void MainWindow::OnTimer()
{	
	if(m_bCameraMode==true && m_bCameraStart==false)
	{
		cv::Mat frame;
		m_hCapture>>frame;
	
		int w = frame.cols;
		int h = frame.rows;

		if (w < 320 || h < 240)
			m_Frame = frame;
		else
		{
			float wscale = w / 240.0f;
			float hscale = h / 240.0f;

			float scale = wscale < hscale ? wscale:hscale;
			w = w / scale;
			h = h / scale;
			cv::resize(frame, m_Frame, cv::Size(w, h));
		}

		cv::Mat inMat = m_Frame.clone();
		//cv::cvtColor(inMat, inMat, CV_BGR2RGB);
	    m_pStitchedItem = m_hStitchScene.addPixmap(QPixmap::fromImage(cvMatToQImage(inMat)));

		return;
	}
	cv::Mat frame;
	m_hCapture >> frame;

	if (frame.empty())
	{
		ui->m_lblStatus->setText(tr("Processed all frames. Please merge panorama!"));
		m_bRun = true;
		OnStart();
		m_bEndFlag = true;
		return;
	}

	int w = frame.cols;
	int h = frame.rows;

	if (w < 320 || h < 240)
		m_Frame = frame;
	else
	{
		float wscale = w / 240.0f;
		float hscale = h / 240.0f;

		float scale = wscale < hscale ? wscale:hscale;
		w = w / scale;
		h = h / scale;
		cv::resize(frame, m_Frame, cv::Size(w, h));
	}
	cv::resize(m_Frame, m_CurFrame, cv::Size(w/2, h/2));
	// Increase the Read Frame Count.

	m_nIndex++;
	if (m_aryImages.size() == 0)
	{
		AddFrame(m_Frame);

		if(m_bCameraMode)
			ui->m_lblStatus->setText(tr("  %1 Frame Processed.").arg(m_nIndex));
		else
			ui->m_lblStatus->setText(tr("  %1 / %2 Frame Processed.").arg(m_nIndex).arg(m_nFrameCount));

		return;
	}
	 
	Stitch2Images(m_CurFrame, m_PrevKeyFrame);
	m_PrevFrame=m_Frame.clone();

	// Set the Status.
	if(m_bCameraMode)
		ui->m_lblStatus->setText(tr("  %1 Frame Processed.").arg(m_nIndex));
	else
		ui->m_lblStatus->setText(tr("  %1 / %2 Frame Processed.").arg(m_nIndex).arg(m_nFrameCount));

	return;
}
