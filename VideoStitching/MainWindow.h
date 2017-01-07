#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPoint>
#include <QTimer>
#include <QVector>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "./opencv2/opencv.hpp"

using namespace std;
using namespace cv;

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit				MainWindow(QWidget *parent = 0);
	~MainWindow();

	void					InitValue();
	void					Initialize();
	void					InitConnects();

	// Used for Window Moving
	void					wheelEvent(QWheelEvent *e);
	void					mousePressEvent(QMouseEvent *e);
	void					mouseMoveEvent(QMouseEvent *e);
	void					mouseDoubleClickEvent(QMouseEvent *e);

	// Status
	void					SetStatus(QString strMsg);

	// Member Variables
public:
	// Thread Values
	QTimer                  *m_pTimer;

	// Control UI Value
	Ui::MainWindow			*ui;
	QGraphicsScene			m_hStitchScene;
	QGraphicsScene			m_hFrameScene;
	QGraphicsPixmapItem		*m_pStitchedItem;
	QGraphicsTextItem       *m_pStatusItem;

	// Used for Window Moving
	QPoint  m_LastPos;

	// Scale Factor
	float					m_fZoom;
	bool					m_bRun;

	// Interface Values
	vector<Mat>				m_aryImages;
	VideoCapture			m_hCapture;
	QString					m_strVideoFile;

	cv::Mat					m_CurFrame;
	cv::Mat					m_PrevKeyFrame;
	cv::Mat					m_PrevFrame;
	cv::Mat					m_Frame;

	int						m_nFPS;
	int						m_nWidth;
	int						m_nHeight;
	int						m_nFrameCount;
	int						m_nIndex;
	bool					m_bCameraMode;
	bool					m_bCameraStart;
	bool					m_bEndFlag;
public:

	QImage					cvMatToQImage(cv::Mat inMat);

	void					AddFrame(cv::Mat frame);
	void					Stitch();
	void					LoadVideo();
	void					LoadCamera();
	void					GetKeyFrames();
	void					Stitch2Images(cv::Mat image1, cv::Mat image2);

	public slots:
		void					OnOpen();
		void					OnClose();
		void					OnSnapshot();
		void					OnStart();
		void					OnTimer();
		void					onCamera();
};

#endif // MAINWINDOW_H
