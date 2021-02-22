/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ClickableLabel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QSlider *dwellSlider;
    QDoubleSpinBox *dwellSpinBox;
    QLabel *label;
    QLabel *label_8;
    QCheckBox *enableClickingCheckBox;
    QCheckBox *autoDetectNoseCheckBox;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    CMS::ClickableLabel *frameLabel;
    QMenuBar *menuBar;
    QMenu *menuDevices;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(833, 537);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(200, 16777215));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);

        dwellSlider = new QSlider(groupBox_2);
        dwellSlider->setObjectName(QString::fromUtf8("dwellSlider"));
        dwellSlider->setMaximum(5000);
        dwellSlider->setOrientation(Qt::Horizontal);
        dwellSlider->setTickPosition(QSlider::NoTicks);

        gridLayout->addWidget(dwellSlider, 2, 0, 1, 5);

        dwellSpinBox = new QDoubleSpinBox(groupBox_2);
        dwellSpinBox->setObjectName(QString::fromUtf8("dwellSpinBox"));
        dwellSpinBox->setMaximumSize(QSize(60, 16777215));
        dwellSpinBox->setMaximum(5.000000000000000);
        dwellSpinBox->setSingleStep(0.100000000000000);

        gridLayout->addWidget(dwellSpinBox, 1, 2, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 3, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 1, 0, 1, 1);

        enableClickingCheckBox = new QCheckBox(groupBox_2);
        enableClickingCheckBox->setObjectName(QString::fromUtf8("enableClickingCheckBox"));

        gridLayout->addWidget(enableClickingCheckBox, 0, 0, 1, 3);


        verticalLayout->addWidget(groupBox_2);

        autoDetectNoseCheckBox = new QCheckBox(groupBox);
        autoDetectNoseCheckBox->setObjectName(QString::fromUtf8("autoDetectNoseCheckBox"));
        autoDetectNoseCheckBox->setChecked(true);

        verticalLayout->addWidget(autoDetectNoseCheckBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(groupBox);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        frameLabel = new CMS::ClickableLabel(centralWidget);
        frameLabel->setObjectName(QString::fromUtf8("frameLabel"));
        frameLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(frameLabel);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 833, 21));
        menuDevices = new QMenu(menuBar);
        menuDevices->setObjectName(QString::fromUtf8("menuDevices"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuDevices->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Settings", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Clicking", nullptr));
        label->setText(QApplication::translate("MainWindow", "s", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Dwell time", nullptr));
        enableClickingCheckBox->setText(QApplication::translate("MainWindow", "Enable clicking", nullptr));
        autoDetectNoseCheckBox->setText(QApplication::translate("MainWindow", "Auto Detect Nose", nullptr));
        frameLabel->setText(QApplication::translate("MainWindow", "No image", nullptr));
        menuDevices->setTitle(QApplication::translate("MainWindow", "Devices", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
