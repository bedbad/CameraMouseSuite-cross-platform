/*                         Camera Mouse Suite
 *  Copyright (C) 2015, Andrew Kurauchi
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtCore/QObject>
#ifdef Q_OS_LINUX
#include <opencv2/imgproc.hpp>
#endif

#include "CameraMouseController.h"
#include "StandardTrackingModule.h"
#include "ImageProcessing.h"

#include <QtCore/QThread>
#include <QtCore/QMetaType>

namespace CMS {

CameraMouseController::CameraMouseController(Settings &settings, StandardTrackingModule *trackingModule, MouseControlModule *controlModule) :
    settings(settings), trackingModule(trackingModule), controlModule(controlModule)
{
    trackingThread = new QThread();
    trackingModule->moveToThread(trackingThread);

    //Signaling:
    //Part 1. Communication
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<Point>("Point");

    connect(this, &CameraMouseController::processFrame, trackingModule, &StandardTrackingModule::process, Qt::QueuedConnection);
    connect(this, &CameraMouseController::updateTrackPoint, trackingModule, &StandardTrackingModule::setTrackPoint, Qt::QueuedConnection);
    connect(trackingModule, &StandardTrackingModule::positionUpdated, this, &CameraMouseController::frameFinished, Qt::QueuedConnection);
    connect(trackingModule, &StandardTrackingModule::finished, trackingThread, &QThread::quit);
    connect(trackingModule, &StandardTrackingModule::finished, trackingThread, &QObject::deleteLater);

    trackingThread->start();
    trackingThread->setPriority(QThread::Priority::LowestPriority);/*
    connect(&featureCheckTimer, &QTimer::timeout, trackingModule, &StandardTrackingModule::onTimeout);*/
    qDebug() << "Main Thread ID:" << QThread::currentThreadId();
}

void CameraMouseController::sendFrame(cv::Mat& frame){
    prevFrame = frame;
    emit processFrame(frame.clone());
}
void CameraMouseController::drawOnFrame(cv::Mat &frame, Point point){
    float ratio = 0.03;
    int width = (int) (frame.size().width * ratio);
    int height = (int) (frame.size().height * ratio);
    cv::Rect rectangle(point.X() - width / 2, point.Y() - height / 2, width, height);
    ImageProcessing::drawGreenRectangle(frame, rectangle);
}

CameraMouseController::~CameraMouseController(){
    delete trackingThread;
    delete controlModule;
}

//void CameraMouseController::processFrame(cv::Mat &frame)
//{
//    prevFrame = frame;

//    if (trackingModule->isInitialized())
//    {
//        Point featurePosition = trackingModule->track(frame);
//        if (!featurePosition.empty())
//        {
////            if (settings.isAutoDetectNoseEnabled() && featureCheckTimer.elapsed() > 1000)
////            {
////                Point autoFeaturePosition = Point();
////                        //initializationModule.initializeFeature(frame);
////                if (!autoFeaturePosition.empty())
////                {
////                    double distThreshSq = settings.getResetFeatureDistThreshSq();
////                    Point disp = autoFeaturePosition - featurePosition;
////                    if (disp * disp > distThreshSq)
////                    {
////                        trackingModule->setTrackPoint(frame, autoFeaturePosition);
////                        controlModule->setScreenReference(controlModule->getPrevPos());
////                        controlModule->restart();
////                        featurePosition = autoFeaturePosition;
////                    }
////                    featureCheckTimer.restart();
////                }
////            }
//            trackingModule->drawOnFrame(frame, featurePosition);
//            controlModule->update(featurePosition);
//        }
//    }
////    else if (settings.isAutoDetectNoseEnabled())
////    {
////        Point initialFeaturePosition = initializationModule.initializeFeature(frame);
////        if (!initialFeaturePosition.empty())
////        {
////            trackingModule->setTrackPoint(frame, initialFeaturePosition);
////            controlModule->setScreenReference(settings.getScreenResolution()/2);
////            controlModule->restart();
////        }
////    }
//}

void CameraMouseController::frameFinished(cv::Mat mat, Point featurePosition){
    if(trackingModule->isInitialized()){
        controlModule->update(featurePosition);
        emit frameProcessed(featurePosition);
    }
}

void CameraMouseController::processClick(Point position){
        emit updateTrackPoint(prevFrame, position);
        controlModule->restart();
}

bool CameraMouseController::isAutoDetectWorking(){
    return initializationModule.allFilesLoaded();
}

} // namespace CMS

