
#include "MarkerSplash.h"
#include "MainWindow.h"

/////////////////////////////////////////////////////////////////////////////////////
/// \brief CMarkerSplash::CMarkerSplash
/// \param mw
/////////////////////////////////////////////////////////////////////////////////////
CMarkerSplash::CMarkerSplash(MainWindow *mw) :
    QGraphicsView()
{
    m_pWnd = mw;

    // Create Scene.
    setScene(&m_hScene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Create the effect of Animation
    m_pEffect = new QGraphicsOpacityEffect;
    m_pEffect->setOpacity(1);
    m_pEffect->setEnabled(true);

    // Create Splash Screen as a GraphicsPixmapItem
    QGraphicsPixmapItem* pSplashPixmapItem = NULL;
    QPixmap pixmap = QPixmap("./Res/Splash.png");
    //pixmap = pixmap.scaled(800, 800, Qt::KeepAspectRatio);

    pSplashPixmapItem = m_hScene.addPixmap(pixmap);
    pSplashPixmapItem->setGraphicsEffect(m_pEffect);

    // Create Animation
    m_pAnim = new QPropertyAnimation(m_pEffect, "opacity", this);
    m_pAnim->setDuration(4000);
    m_pAnim->setEasingCurve(QEasingCurve::OutExpo);
    m_pAnim->setStartValue(0.3);
    m_pAnim->setEndValue(1);
    m_pAnim->setDirection(QAbstractAnimation::Forward);
    m_pAnim->start();

    connect(m_pAnim, SIGNAL(finished()), SLOT(hideSplash()));

    // Set Window Flag
    setRenderHint(QPainter::Antialiasing, true);
    setFrameStyle(QFrame::NoFrame);

    this->setFixedSize(pixmap.size());
}

/////////////////////////////////////////////////////////////////////////////////////
/// \brief When User click on Splash, then it will disappear soon.
/////////////////////////////////////////////////////////////////////////////////////
void CMarkerSplash::mousePressEvent(QMouseEvent *)
{
    hideSplash();
}

/////////////////////////////////////////////////////////////////////////////////////
/// Hide Splash and show MainWindow
/////////////////////////////////////////////////////////////////////////////////////
void CMarkerSplash::hideSplash()
{
    hide();

    if (m_pWnd != NULL)
    {
        m_pWnd->show();
    }
}
