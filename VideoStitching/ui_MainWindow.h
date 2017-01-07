/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *mainWidget;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *m_pMainLayout;
    QHBoxLayout *m_pTitleLayout;
    QLabel *m_lblTitle;
    QToolButton *m_btnClose;
    QHBoxLayout *m_pCentralLayout;
    QGraphicsView *m_pFrameView;
    QVBoxLayout *m_pStitchedLayout;
    QGraphicsView *m_pStitchView;
    QHBoxLayout *m_pButtonLayout;
    QToolButton *m_btnOpen;
    QToolButton *m_btncamera;
    QToolButton *m_btnPlay;
    QToolButton *m_btnSnapshot;
    QLabel *m_lblStatus;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(912, 589);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(78, 78, 78, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        MainWindow->setPalette(palette);
        MainWindow->setAutoFillBackground(true);
        mainWidget = new QWidget(MainWindow);
        mainWidget->setObjectName(QStringLiteral("mainWidget"));
        verticalLayoutWidget_2 = new QWidget(mainWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 10, 901, 571));
        m_pMainLayout = new QVBoxLayout(verticalLayoutWidget_2);
        m_pMainLayout->setSpacing(10);
        m_pMainLayout->setContentsMargins(11, 11, 11, 11);
        m_pMainLayout->setObjectName(QStringLiteral("m_pMainLayout"));
        m_pMainLayout->setContentsMargins(0, 0, 0, 0);
        m_pTitleLayout = new QHBoxLayout();
        m_pTitleLayout->setSpacing(6);
        m_pTitleLayout->setObjectName(QStringLiteral("m_pTitleLayout"));
        m_pTitleLayout->setContentsMargins(-1, 0, 10, -1);
        m_lblTitle = new QLabel(verticalLayoutWidget_2);
        m_lblTitle->setObjectName(QStringLiteral("m_lblTitle"));
        m_lblTitle->setMinimumSize(QSize(0, 80));
        m_lblTitle->setMaximumSize(QSize(160000, 16777215));
        QPalette palette1;
        QBrush brush2(QColor(245, 231, 27, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        QBrush brush3(QColor(120, 120, 120, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        m_lblTitle->setPalette(palette1);
        QFont font;
        font.setFamily(QStringLiteral("Monotype Corsiva"));
        font.setPointSize(40);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        m_lblTitle->setFont(font);
        m_lblTitle->setAlignment(Qt::AlignCenter);

        m_pTitleLayout->addWidget(m_lblTitle);

        m_btnClose = new QToolButton(verticalLayoutWidget_2);
        m_btnClose->setObjectName(QStringLiteral("m_btnClose"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Res/Exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_btnClose->setIcon(icon);
        m_btnClose->setIconSize(QSize(32, 32));
        m_btnClose->setAutoRaise(true);

        m_pTitleLayout->addWidget(m_btnClose);


        m_pMainLayout->addLayout(m_pTitleLayout);

        m_pCentralLayout = new QHBoxLayout();
        m_pCentralLayout->setSpacing(0);
        m_pCentralLayout->setObjectName(QStringLiteral("m_pCentralLayout"));
        m_pCentralLayout->setContentsMargins(10, 0, 0, 0);
        m_pFrameView = new QGraphicsView(verticalLayoutWidget_2);
        m_pFrameView->setObjectName(QStringLiteral("m_pFrameView"));
        m_pFrameView->setMinimumSize(QSize(150, 300));
        m_pFrameView->setMaximumSize(QSize(150, 16777215));
        QPalette palette2;
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush4);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        m_pFrameView->setPalette(palette2);

        m_pCentralLayout->addWidget(m_pFrameView);

        m_pStitchedLayout = new QVBoxLayout();
        m_pStitchedLayout->setSpacing(6);
        m_pStitchedLayout->setObjectName(QStringLiteral("m_pStitchedLayout"));
        m_pStitchedLayout->setContentsMargins(10, 0, 10, 0);
        m_pStitchView = new QGraphicsView(verticalLayoutWidget_2);
        m_pStitchView->setObjectName(QStringLiteral("m_pStitchView"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Base, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        m_pStitchView->setPalette(palette3);

        m_pStitchedLayout->addWidget(m_pStitchView);

        m_pButtonLayout = new QHBoxLayout();
        m_pButtonLayout->setSpacing(6);
        m_pButtonLayout->setObjectName(QStringLiteral("m_pButtonLayout"));
        m_pButtonLayout->setContentsMargins(10, 0, -1, -1);
        m_btnOpen = new QToolButton(verticalLayoutWidget_2);
        m_btnOpen->setObjectName(QStringLiteral("m_btnOpen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Res/Open.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_btnOpen->setIcon(icon1);
        m_btnOpen->setIconSize(QSize(48, 48));
        m_btnOpen->setAutoRaise(true);

        m_pButtonLayout->addWidget(m_btnOpen);

        m_btncamera = new QToolButton(verticalLayoutWidget_2);
        m_btncamera->setObjectName(QStringLiteral("m_btncamera"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Res/Camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_btncamera->setIcon(icon2);
        m_btncamera->setIconSize(QSize(48, 48));
        m_btncamera->setAutoRaise(true);

        m_pButtonLayout->addWidget(m_btncamera);

        m_btnPlay = new QToolButton(verticalLayoutWidget_2);
        m_btnPlay->setObjectName(QStringLiteral("m_btnPlay"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Res/Play.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_btnPlay->setIcon(icon3);
        m_btnPlay->setIconSize(QSize(48, 48));
        m_btnPlay->setAutoRaise(true);

        m_pButtonLayout->addWidget(m_btnPlay);

        m_btnSnapshot = new QToolButton(verticalLayoutWidget_2);
        m_btnSnapshot->setObjectName(QStringLiteral("m_btnSnapshot"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Res/SnapShot.png"), QSize(), QIcon::Normal, QIcon::Off);
        m_btnSnapshot->setIcon(icon4);
        m_btnSnapshot->setIconSize(QSize(48, 48));
        m_btnSnapshot->setAutoRaise(true);

        m_pButtonLayout->addWidget(m_btnSnapshot);


        m_pStitchedLayout->addLayout(m_pButtonLayout);


        m_pCentralLayout->addLayout(m_pStitchedLayout);


        m_pMainLayout->addLayout(m_pCentralLayout);

        m_lblStatus = new QLabel(verticalLayoutWidget_2);
        m_lblStatus->setObjectName(QStringLiteral("m_lblStatus"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        m_lblStatus->setPalette(palette4);
        QFont font1;
        font1.setFamily(QStringLiteral("Segoe UI Emoji"));
        font1.setPointSize(12);
        m_lblStatus->setFont(font1);

        m_pMainLayout->addWidget(m_lblStatus);

        MainWindow->setCentralWidget(mainWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        m_lblTitle->setText(QApplication::translate("MainWindow", "     Video Stitching v1.0", 0));
        m_btnClose->setText(QString());
        m_btnOpen->setText(QApplication::translate("MainWindow", "...", 0));
        m_btncamera->setText(QString());
        m_btnPlay->setText(QString());
        m_btnSnapshot->setText(QString());
        m_lblStatus->setText(QApplication::translate("MainWindow", "Welcome To Our Program!", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
