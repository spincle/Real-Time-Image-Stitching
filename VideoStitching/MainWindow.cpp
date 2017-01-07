#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <opencv2/stitching.hpp>
#include <opencv2/stitching/warpers.hpp>
#include <QDebug>
#include <QFileDialog>
#include <QGraphicsScene>


/************************************************************************************
 *
 * Initializing - Values, Instances and Connects.
 *
************************************************************************************/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    InitValue();
    Initialize();
    InitConnects();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::InitValue
/// Initialize all Values
/////////////////////////////////////////////////////////////////////////////////////
void MainWindow::InitValue()
{
    m_fZoom		=	1.0f;
	m_nIndex	=	0;
	m_bRun		=	false;
	m_bCameraMode=	false;
}

/////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::Initialize
/// Initialize the Instances and UI Settings
/////////////////////////////////////////////////////////////////////////////////////
void MainWindow::Initialize()
{
    // Initializing
    m_pTimer = new QTimer();
    ui->setupUi(this);
    ui->m_pFrameView->setScene(&m_hFrameScene);
    ui->m_pStitchView->setScene(&m_hStitchScene);
    // UI Settings.
    ui->m_pFrameView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->m_pStitchView->setDragMode(QGraphicsView::ScrollHandDrag);
}


/////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::InitConnects
/// Initialize the Connects
/////////////////////////////////////////////////////////////////////////////////////
void MainWindow::InitConnects()
{
    connect(m_pTimer,           SIGNAL(timeout()),      this, SLOT(OnTimer()));
    connect(ui->m_btnClose,     SIGNAL(clicked(bool)),  this, SLOT(OnClose()));
    connect(ui->m_btnOpen,      SIGNAL(clicked(bool)),  this, SLOT(OnOpen()));
    connect(ui->m_btnPlay,      SIGNAL(clicked(bool)),  this, SLOT(OnStart()));
    connect(ui->m_btnSnapshot,  SIGNAL(clicked(bool)),  this, SLOT(OnSnapshot()));
	connect(ui->m_btncamera,	SIGNAL(clicked(bool)),  this, SLOT( onCamera()) );
}

/////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::OnStart
/// Start Stitching
/////////////////////////////////////////////////////////////////////////////////////
void MainWindow::OnStart()
{
	GetKeyFrames();
}

/////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::OnOpen
/// Open the New Video File
/////////////////////////////////////////////////////////////////////////////////////
void MainWindow::OnOpen()
{
	if(m_bCameraMode==true)
		m_pTimer->stop();
    QString strFile = QFileDialog::getOpenFileName(
                            this, tr("Select a Video"),
                            "", tr("All Video Files (*.avi *.mp4 *.mpg *.mov)"));
    if (strFile.isEmpty())
        return;

    m_strVideoFile = strFile;
    LoadVideo();
}

/////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::OnSnapshot
/// Save the Stitched Image to the File.
/////////////////////////////////////////////////////////////////////////////////////
void MainWindow::OnSnapshot()
{
	Stitch();

	QString strFile = QFileDialog::getSaveFileName(this, tr("Select Snapshot File Name"),
		"", tr("PNG Files (*.png);;JPEG Files (*.jpg);;Bitmap Files (*.bmp)"));

	if (strFile.isEmpty())
		return;

	QPixmap pixmap = m_pStitchedItem->pixmap();
	pixmap.save(strFile);
}

/////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::OnClose
/////////////////////////////////////////////////////////////////////////////////////
void MainWindow::OnClose()
{
    exit(0);
}


/////////////////////////////////////////////////////////////
/// \brief MainWindow::mousePressEvent : Used for Windows Moving
/// \param event
/////////////////////////////////////////////////////////////
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    m_LastPos = event->pos();
}


/////////////////////////////////////////////////////////////
/// \brief MainWindow::mouseMoveEvent : Used for Windows Moving
/// \param event
/////////////////////////////////////////////////////////////
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint trans = event->pos() - m_LastPos;
    QPoint curPos = this->pos();
    curPos += trans;
    if (event->buttons() == Qt::LeftButton)
    {
        this->move(curPos);
    }
}

///////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::mouseDoubleClickEvent : Reset the scale of Stitched Image.
/// \param event
///////////////////////////////////////////////////////////////////////////////////////
void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        ui->m_pStitchView->scale(1.0f/m_fZoom, 1.0f/m_fZoom);
        m_fZoom = 1.0f;
    }

    qDebug() <<  m_fZoom;
}

///////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::wheelEvent : Zoom in or Zoom out the Stitched Image.
/// \param event
///////////////////////////////////////////////////////////////////////////////////////
void MainWindow::wheelEvent(QWheelEvent *event)
{
    if ((event->modifiers() & Qt::ControlModifier) != Qt::ControlModifier)
        return;

    if (event->delta() > 0)
    {
        m_fZoom *= 1.1f;
        ui->m_pStitchView->scale(1.1f, 1.1f);
    }
    else
    {
        m_fZoom /= 1.1f;
        ui->m_pStitchView->scale(0.9091f, 0.9091f);
    }
    qDebug() <<  m_fZoom;
}

///////////////////////////////////////////////////////////////////////////////////////
/// \brief MainWindow::SetStatus : Set the Status
/// \param strMsg : Text to set as the Status
///////////////////////////////////////////////////////////////////////////////////////
void MainWindow::SetStatus(QString strMsg)
{
    ui->m_lblStatus->setText(strMsg);
}


void MainWindow::onCamera()
{
	LoadCamera();
}
