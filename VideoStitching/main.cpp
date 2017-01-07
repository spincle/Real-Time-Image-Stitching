#include "MainWindow.h"
#include "MarkerSplash.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Creating an Application
    QApplication app(argc, argv);
    app.setStyle("Windows XP");

    // Display the Color Tracking Window
    MainWindow w;
    //w.setFixedSize(880, 688);
    w.setWindowIcon(QIcon(":/Res/AppIcon.png"));
    w.setWindowFlags(Qt::CustomizeWindowHint);

    // First Display the Splash With Smooth Effect
    CMarkerSplash splash(&w);
    splash.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Video Stitching!"));
    splash.setWindowFlags(Qt::SplashScreen);
    splash.show();

    return app.exec();
}
