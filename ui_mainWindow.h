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
#include <QtGui/QIcon>
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
#include <QtWidgets/QPushButton>
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
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QCheckBox *reverseHorizontalCheckBox;
    QSlider *verticalGainSlider;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label_7;
    QSlider *horizontalGainSlider;
    QPushButton *lockGainButton;
    QCheckBox *smoothingCheckBox;
    QSlider *smoothingSlider;
    QLabel *label_9;
    QLabel *label_10;
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
        MainWindow->resize(833, 488);
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

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        reverseHorizontalCheckBox = new QCheckBox(groupBox_3);
        reverseHorizontalCheckBox->setObjectName(QString::fromUtf8("reverseHorizontalCheckBox"));

        gridLayout_3->addWidget(reverseHorizontalCheckBox, 0, 0, 1, 2);

        verticalGainSlider = new QSlider(groupBox_3);
        verticalGainSlider->setObjectName(QString::fromUtf8("verticalGainSlider"));
        verticalGainSlider->setMinimum(3);
        verticalGainSlider->setMaximum(18);
        verticalGainSlider->setSingleStep(3);
        verticalGainSlider->setValue(6);
        verticalGainSlider->setOrientation(Qt::Horizontal);
        verticalGainSlider->setInvertedAppearance(false);
        verticalGainSlider->setInvertedControls(false);
        verticalGainSlider->setTickPosition(QSlider::TicksAbove);
        verticalGainSlider->setTickInterval(3);

        gridLayout_3->addWidget(verticalGainSlider, 6, 0, 1, 2);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 5, 0, 1, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 4, 0, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_5, 5, 1, 1, 1);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 1, 0, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 2, 0, 1, 1);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_7, 2, 1, 1, 1);

        horizontalGainSlider = new QSlider(groupBox_3);
        horizontalGainSlider->setObjectName(QString::fromUtf8("horizontalGainSlider"));
        horizontalGainSlider->setMinimum(3);
        horizontalGainSlider->setMaximum(18);
        horizontalGainSlider->setSingleStep(3);
        horizontalGainSlider->setValue(6);
        horizontalGainSlider->setOrientation(Qt::Horizontal);
        horizontalGainSlider->setTickPosition(QSlider::TicksAbove);
        horizontalGainSlider->setTickInterval(3);

        gridLayout_3->addWidget(horizontalGainSlider, 3, 0, 1, 2);

        lockGainButton = new QPushButton(groupBox_3);
        lockGainButton->setObjectName(QString::fromUtf8("lockGainButton"));
        lockGainButton->setMaximumSize(QSize(18, 18));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/images/lock-unlocked.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/icons/images/lock-locked.png"), QSize(), QIcon::Normal, QIcon::On);
        lockGainButton->setIcon(icon);
        lockGainButton->setCheckable(true);
        lockGainButton->setChecked(false);

        gridLayout_3->addWidget(lockGainButton, 4, 2, 1, 1);

        smoothingCheckBox = new QCheckBox(groupBox_3);
        smoothingCheckBox->setObjectName(QString::fromUtf8("smoothingCheckBox"));

        gridLayout_3->addWidget(smoothingCheckBox, 7, 0, 1, 1);

        smoothingSlider = new QSlider(groupBox_3);
        smoothingSlider->setObjectName(QString::fromUtf8("smoothingSlider"));
        smoothingSlider->setMinimum(5);
        smoothingSlider->setMaximum(95);
        smoothingSlider->setSingleStep(5);
        smoothingSlider->setValue(65);
        smoothingSlider->setOrientation(Qt::Horizontal);
        smoothingSlider->setInvertedAppearance(true);
        smoothingSlider->setTickPosition(QSlider::TicksAbove);

        gridLayout_3->addWidget(smoothingSlider, 9, 0, 1, 2);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 8, 0, 1, 1);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_10, 8, 1, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        autoDetectNoseCheckBox = new QCheckBox(groupBox);
        autoDetectNoseCheckBox->setObjectName(QString::fromUtf8("autoDetectNoseCheckBox"));

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
        menuBar->setGeometry(QRect(0, 0, 833, 18));
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
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Mouse Movement", nullptr));
        reverseHorizontalCheckBox->setText(QApplication::translate("MainWindow", "Reverse Horizontal", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Low", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Vertical Gain", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "High", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Horizontal Gain", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Low", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "High", nullptr));
        lockGainButton->setText(QString());
        smoothingCheckBox->setText(QApplication::translate("MainWindow", "Smoothing", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Low", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "High", nullptr));
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
