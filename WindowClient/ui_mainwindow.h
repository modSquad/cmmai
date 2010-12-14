/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Dec 13 22:49:06 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QListWidget *LogView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *PiecesDock;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QGroupBox *PiecesCount;
    QGridLayout *gridLayout_3;
    QHBoxLayout *PiecesLayout;
    QVBoxLayout *AcceptedLayout;
    QLabel *AcceptedNumber;
    QLabel *AcceptedLabel;
    QFrame *SeparationLine;
    QVBoxLayout *RejectedLayout;
    QLabel *RejectedNumber;
    QLabel *RejectedLabel;
    QProgressBar *RejectedBar;
    QDockWidget *dockWidgetConnection;
    QWidget *ServerConnectionLayout;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout;
    QLabel *ConnectionLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *ConnectionButton;
    QLineEdit *AddressLine;
    QDockWidget *configurationDock;
    QWidget *configurationWidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *configurationLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *OperatorCodeLayout;
    QLabel *operatoCodeLabel;
    QLineEdit *operatorCode;
    QHBoxLayout *thresholdLayout;
    QLabel *thresholdLabel;
    QLineEdit *threshold;
    QHBoxLayout *bundleReferenceLayout;
    QLabel *bundleReferenceLabel;
    QLineEdit *bundleReference;
    QHBoxLayout *numberOfBoxLayout;
    QLabel *numberOfBoxLabel;
    QLineEdit *numberOfBox;
    QHBoxLayout *piecesBoxLayout;
    QLabel *piecesBoxLavbel;
    QLineEdit *piecesBox;
    QHBoxLayout *sendConfigButtonLayout;
    QSpacerItem *sendConfigButtonSpacer;
    QPushButton *sendConfigButton;
    QDockWidget *controlDock;
    QWidget *controlWidget;
    QGridLayout *gridLayout_4;
    QGroupBox *controlLayout;
    QGridLayout *gridLayout_6;
    QPushButton *stopButton;
    QPushButton *launchButton;
    QPushButton *resumeButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1008, 749);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        LogView = new QListWidget(centralWidget);
        LogView->setObjectName(QString::fromUtf8("LogView"));
        LogView->setFrameShape(QFrame::StyledPanel);
        LogView->setFrameShadow(QFrame::Sunken);
        LogView->setLineWidth(1);
        LogView->setMidLineWidth(0);
        LogView->setAlternatingRowColors(true);
        LogView->setMovement(QListView::Static);
        LogView->setFlow(QListView::TopToBottom);
        LogView->setProperty("isWrapping", QVariant(false));
        LogView->setResizeMode(QListView::Adjust);
        LogView->setLayoutMode(QListView::SinglePass);
        LogView->setSpacing(0);
        LogView->setUniformItemSizes(false);

        gridLayout->addWidget(LogView, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1008, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        PiecesDock = new QDockWidget(MainWindow);
        PiecesDock->setObjectName(QString::fromUtf8("PiecesDock"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout_2 = new QGridLayout(dockWidgetContents);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 11, 0, 1, 1);

        PiecesCount = new QGroupBox(dockWidgetContents);
        PiecesCount->setObjectName(QString::fromUtf8("PiecesCount"));
        gridLayout_3 = new QGridLayout(PiecesCount);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        PiecesLayout = new QHBoxLayout();
        PiecesLayout->setSpacing(6);
        PiecesLayout->setObjectName(QString::fromUtf8("PiecesLayout"));
        AcceptedLayout = new QVBoxLayout();
        AcceptedLayout->setSpacing(6);
        AcceptedLayout->setObjectName(QString::fromUtf8("AcceptedLayout"));
        AcceptedNumber = new QLabel(PiecesCount);
        AcceptedNumber->setObjectName(QString::fromUtf8("AcceptedNumber"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AcceptedNumber->sizePolicy().hasHeightForWidth());
        AcceptedNumber->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(30);
        AcceptedNumber->setFont(font);
        AcceptedNumber->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        AcceptedLayout->addWidget(AcceptedNumber);

        AcceptedLabel = new QLabel(PiecesCount);
        AcceptedLabel->setObjectName(QString::fromUtf8("AcceptedLabel"));
        AcceptedLabel->setAutoFillBackground(false);
        AcceptedLabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        AcceptedLayout->addWidget(AcceptedLabel);


        PiecesLayout->addLayout(AcceptedLayout);

        SeparationLine = new QFrame(PiecesCount);
        SeparationLine->setObjectName(QString::fromUtf8("SeparationLine"));
        SeparationLine->setFrameShape(QFrame::VLine);
        SeparationLine->setFrameShadow(QFrame::Sunken);

        PiecesLayout->addWidget(SeparationLine);

        RejectedLayout = new QVBoxLayout();
        RejectedLayout->setSpacing(6);
        RejectedLayout->setObjectName(QString::fromUtf8("RejectedLayout"));
        RejectedNumber = new QLabel(PiecesCount);
        RejectedNumber->setObjectName(QString::fromUtf8("RejectedNumber"));
        RejectedNumber->setFont(font);
        RejectedNumber->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        RejectedLayout->addWidget(RejectedNumber);

        RejectedLabel = new QLabel(PiecesCount);
        RejectedLabel->setObjectName(QString::fromUtf8("RejectedLabel"));
        RejectedLabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        RejectedLayout->addWidget(RejectedLabel);


        PiecesLayout->addLayout(RejectedLayout);

        RejectedBar = new QProgressBar(PiecesCount);
        RejectedBar->setObjectName(QString::fromUtf8("RejectedBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(RejectedBar->sizePolicy().hasHeightForWidth());
        RejectedBar->setSizePolicy(sizePolicy1);
        RejectedBar->setValue(0);
        RejectedBar->setOrientation(Qt::Vertical);

        PiecesLayout->addWidget(RejectedBar);


        gridLayout_3->addLayout(PiecesLayout, 0, 0, 1, 1);


        gridLayout_2->addWidget(PiecesCount, 10, 0, 1, 1);

        PiecesDock->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), PiecesDock);
        dockWidgetConnection = new QDockWidget(MainWindow);
        dockWidgetConnection->setObjectName(QString::fromUtf8("dockWidgetConnection"));
        ServerConnectionLayout = new QWidget();
        ServerConnectionLayout->setObjectName(QString::fromUtf8("ServerConnectionLayout"));
        gridLayout_5 = new QGridLayout(ServerConnectionLayout);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        ConnectionLabel = new QLabel(ServerConnectionLayout);
        ConnectionLabel->setObjectName(QString::fromUtf8("ConnectionLabel"));

        horizontalLayout->addWidget(ConnectionLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ConnectionButton = new QPushButton(ServerConnectionLayout);
        ConnectionButton->setObjectName(QString::fromUtf8("ConnectionButton"));

        horizontalLayout->addWidget(ConnectionButton);


        gridLayout_5->addLayout(horizontalLayout, 1, 0, 1, 1);

        AddressLine = new QLineEdit(ServerConnectionLayout);
        AddressLine->setObjectName(QString::fromUtf8("AddressLine"));

        gridLayout_5->addWidget(AddressLine, 0, 0, 1, 1);

        dockWidgetConnection->setWidget(ServerConnectionLayout);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidgetConnection);
        configurationDock = new QDockWidget(MainWindow);
        configurationDock->setObjectName(QString::fromUtf8("configurationDock"));
        configurationDock->setEnabled(true);
        configurationWidget = new QWidget();
        configurationWidget->setObjectName(QString::fromUtf8("configurationWidget"));
        verticalLayout_2 = new QVBoxLayout(configurationWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        configurationLayout = new QGroupBox(configurationWidget);
        configurationLayout->setObjectName(QString::fromUtf8("configurationLayout"));
        configurationLayout->setEnabled(true);
        verticalLayout = new QVBoxLayout(configurationLayout);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        OperatorCodeLayout = new QHBoxLayout();
        OperatorCodeLayout->setSpacing(6);
        OperatorCodeLayout->setObjectName(QString::fromUtf8("OperatorCodeLayout"));
        operatoCodeLabel = new QLabel(configurationLayout);
        operatoCodeLabel->setObjectName(QString::fromUtf8("operatoCodeLabel"));

        OperatorCodeLayout->addWidget(operatoCodeLabel);

        operatorCode = new QLineEdit(configurationLayout);
        operatorCode->setObjectName(QString::fromUtf8("operatorCode"));

        OperatorCodeLayout->addWidget(operatorCode);


        verticalLayout->addLayout(OperatorCodeLayout);

        thresholdLayout = new QHBoxLayout();
        thresholdLayout->setSpacing(6);
        thresholdLayout->setObjectName(QString::fromUtf8("thresholdLayout"));
        thresholdLabel = new QLabel(configurationLayout);
        thresholdLabel->setObjectName(QString::fromUtf8("thresholdLabel"));

        thresholdLayout->addWidget(thresholdLabel);

        threshold = new QLineEdit(configurationLayout);
        threshold->setObjectName(QString::fromUtf8("threshold"));

        thresholdLayout->addWidget(threshold);


        verticalLayout->addLayout(thresholdLayout);

        bundleReferenceLayout = new QHBoxLayout();
        bundleReferenceLayout->setSpacing(6);
        bundleReferenceLayout->setObjectName(QString::fromUtf8("bundleReferenceLayout"));
        bundleReferenceLabel = new QLabel(configurationLayout);
        bundleReferenceLabel->setObjectName(QString::fromUtf8("bundleReferenceLabel"));

        bundleReferenceLayout->addWidget(bundleReferenceLabel);

        bundleReference = new QLineEdit(configurationLayout);
        bundleReference->setObjectName(QString::fromUtf8("bundleReference"));

        bundleReferenceLayout->addWidget(bundleReference);


        verticalLayout->addLayout(bundleReferenceLayout);

        numberOfBoxLayout = new QHBoxLayout();
        numberOfBoxLayout->setSpacing(6);
        numberOfBoxLayout->setObjectName(QString::fromUtf8("numberOfBoxLayout"));
        numberOfBoxLabel = new QLabel(configurationLayout);
        numberOfBoxLabel->setObjectName(QString::fromUtf8("numberOfBoxLabel"));

        numberOfBoxLayout->addWidget(numberOfBoxLabel);

        numberOfBox = new QLineEdit(configurationLayout);
        numberOfBox->setObjectName(QString::fromUtf8("numberOfBox"));

        numberOfBoxLayout->addWidget(numberOfBox);


        verticalLayout->addLayout(numberOfBoxLayout);

        piecesBoxLayout = new QHBoxLayout();
        piecesBoxLayout->setSpacing(6);
        piecesBoxLayout->setObjectName(QString::fromUtf8("piecesBoxLayout"));
        piecesBoxLavbel = new QLabel(configurationLayout);
        piecesBoxLavbel->setObjectName(QString::fromUtf8("piecesBoxLavbel"));

        piecesBoxLayout->addWidget(piecesBoxLavbel);

        piecesBox = new QLineEdit(configurationLayout);
        piecesBox->setObjectName(QString::fromUtf8("piecesBox"));

        piecesBoxLayout->addWidget(piecesBox);


        verticalLayout->addLayout(piecesBoxLayout);

        sendConfigButtonLayout = new QHBoxLayout();
        sendConfigButtonLayout->setSpacing(6);
        sendConfigButtonLayout->setObjectName(QString::fromUtf8("sendConfigButtonLayout"));
        sendConfigButtonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        sendConfigButtonLayout->addItem(sendConfigButtonSpacer);

        sendConfigButton = new QPushButton(configurationLayout);
        sendConfigButton->setObjectName(QString::fromUtf8("sendConfigButton"));

        sendConfigButtonLayout->addWidget(sendConfigButton);


        verticalLayout->addLayout(sendConfigButtonLayout);


        verticalLayout_2->addWidget(configurationLayout);

        configurationDock->setWidget(configurationWidget);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), configurationDock);
        controlDock = new QDockWidget(MainWindow);
        controlDock->setObjectName(QString::fromUtf8("controlDock"));
        controlDock->setEnabled(true);
        controlWidget = new QWidget();
        controlWidget->setObjectName(QString::fromUtf8("controlWidget"));
        gridLayout_4 = new QGridLayout(controlWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        controlLayout = new QGroupBox(controlWidget);
        controlLayout->setObjectName(QString::fromUtf8("controlLayout"));
        controlLayout->setEnabled(true);
        gridLayout_6 = new QGridLayout(controlLayout);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        stopButton = new QPushButton(controlLayout);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        gridLayout_6->addWidget(stopButton, 1, 1, 1, 1);

        launchButton = new QPushButton(controlLayout);
        launchButton->setObjectName(QString::fromUtf8("launchButton"));

        gridLayout_6->addWidget(launchButton, 0, 1, 1, 1);

        resumeButton = new QPushButton(controlLayout);
        resumeButton->setObjectName(QString::fromUtf8("resumeButton"));

        gridLayout_6->addWidget(resumeButton, 2, 1, 1, 1);


        gridLayout_4->addWidget(controlLayout, 0, 0, 1, 1);

        controlDock->setWidget(controlWidget);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), controlDock);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        PiecesCount->setTitle(QApplication::translate("MainWindow", "Pieces", 0, QApplication::UnicodeUTF8));
        AcceptedNumber->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        AcceptedLabel->setText(QApplication::translate("MainWindow", "accepted", 0, QApplication::UnicodeUTF8));
        RejectedNumber->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        RejectedLabel->setText(QApplication::translate("MainWindow", "rejected", 0, QApplication::UnicodeUTF8));
        RejectedBar->setFormat(QApplication::translate("MainWindow", "%v/%m%", 0, QApplication::UnicodeUTF8));
        ConnectionLabel->setText(QString());
        ConnectionButton->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        AddressLine->setText(QApplication::translate("MainWindow", "127.0.0.1:42424", 0, QApplication::UnicodeUTF8));
        configurationLayout->setTitle(QApplication::translate("MainWindow", "Confguration", 0, QApplication::UnicodeUTF8));
        operatoCodeLabel->setText(QApplication::translate("MainWindow", "Operator Code", 0, QApplication::UnicodeUTF8));
        thresholdLabel->setText(QApplication::translate("MainWindow", "Threshold", 0, QApplication::UnicodeUTF8));
        bundleReferenceLabel->setText(QApplication::translate("MainWindow", "Bundle Reference", 0, QApplication::UnicodeUTF8));
        numberOfBoxLabel->setText(QApplication::translate("MainWindow", "Number of box", 0, QApplication::UnicodeUTF8));
        piecesBoxLavbel->setText(QApplication::translate("MainWindow", "Pieces / box", 0, QApplication::UnicodeUTF8));
        sendConfigButton->setText(QApplication::translate("MainWindow", "Ok", 0, QApplication::UnicodeUTF8));
        controlLayout->setTitle(QApplication::translate("MainWindow", "Control", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        launchButton->setText(QApplication::translate("MainWindow", "Launch", 0, QApplication::UnicodeUTF8));
        resumeButton->setText(QApplication::translate("MainWindow", "Resume", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
