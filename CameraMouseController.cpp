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

#include <QObject>
#ifdef Q_OS_LINUX
#include <opencv2/imgproc.hpp>
#endif

#include "CameraMouseController.h"
#include "ImageProcessing.h"

namespace CMS {

CameraMouseController::CameraMouseController(Settings &settings, ITrackingModule *trackingModule, MouseControlModule *controlModule) :
    settings(settings), trackingModule(trackingModule), controlModule(controlModule)
{
    trackingModule->moveToThread(&trackingThread);
    connect(&trackingThread, &QThread::finished, trackingModule, &QObject::deleteLater, Qt::QueuedConnection);
    connect(this, SIGNAL(processFrame(cv::Mat)), trackingModule, SLOT(track(cv::Mat)), Qt::QueuedConnection);
    connect(this, SIGNAL(updateTrackPoint(cv::Mat, Point)), trackingModule, SLOT(setTrackPoint(cv::Mat, Point)), Qt::QueuedConnection);
    connect(trackingModule, SIGNAL(positionUpdated(cv::Mat, Point)), this, SLOT(frameFinished(cv::Mat, Point)), Qt::QueuedConnection);
    trackingThread.start();
    
    featureCheckTimer.start();
}

void CameraMouseController::drawOnFrame(cv::Mat &frame, Point point){
    float ratio = 0.03;
    int width = (int) (frame.size().width * ratio);
    int height = (int) (frame.size().height * ratio);
    cv::Rect rectangle(point.X() - width / 2, point.Y() - height / 2, width, height);
    ImageProcessing::drawGreenRectangle(frame, rectangle);
}

CameraMouseController::~CameraMouseController(){
    trackingThread.wait();
    trackingThread.quit();
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
    controlModule->update(featurePosition);
    emit frameProcessed(featurePosition);
}

void CameraMouseController::processClick(Point position){
    if (!prevFrame.empty())
    {
        emit updateTrackPoint(prevFrame, position);
        controlModule->restart();
    }
}

bool CameraMouseController::isAutoDetectWorking(){
    return initializationModule.allFilesLoaded();
}

} // namespace CMS

