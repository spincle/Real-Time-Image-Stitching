#ifndef MARKERSPLASH_H
#define MARKERSPLASH_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>

class MainWindow;
class CMarkerSplash : public QGraphicsView
{
    Q_OBJECT

    // Member Varaibles for GUI
public:
    MainWindow* m_pWnd;
    QGraphicsScene              m_hScene;
    QGraphicsOpacityEffect*     m_pEffect;
    QPropertyAnimation*         m_pAnim;


    // Member Functions
public:
    // Constructor & Initializing
    CMarkerSplash(MainWindow *parent = 0);

    // Override Events
    void mousePressEvent(QMouseEvent *event);

    // Operations

signals:

public slots:
    void hideSplash();

};

#endif // MARKERSPLASH_H
