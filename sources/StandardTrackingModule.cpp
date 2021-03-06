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
#include <qdebug.h>
#include <opencv2/video/tracking.hpp>

#include "StandardTrackingModule.h"
#include "asmOpenCV.h"
#include <opencv2/highgui.hpp>

//!!! QT internals !!!
#include <QThread>

namespace CMS {

StandardTrackingModule::StandardTrackingModule() :
    sanityCheck(this),
    initialized(false),
    winSize(10, 10),
    criteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 20, 0.03),
    imageSize(0,0)
{
}

//// *critical*
//size_t getEventQueueSize(QThread* thread)
//{
//    auto threadData = QThreadData::get2(thread);
//    QMutexLocker locker(&threadData->postEventList.mutex);
//    return threadData->postEventList.size();
//}

void StandardTrackingModule::process(cv::Mat frame)
{
    if(!initialized)
        return;

//    sanityCheck.checkFrameNotEmpty(frame);
    cv::Mat grey = ASM::convertToGray(frame);
    if(!prevGrey.empty()){
        qDebug() <<"checking mat"<< prevGrey.size().width << " "<< prevGrey.size().height << " " << "\n";
        std::vector<uchar> featuresFound;
        cv::Mat err;
        std::vector<cv::Point2f> currentTrackPoints;
        cv::TermCriteria criteria = cv::TermCriteria((cv::TermCriteria::COUNT) + (cv::TermCriteria::EPS), 10, 0.03);
        cv::calcOpticalFlowPyrLK(prevGrey, grey, prevTrackPoints, currentTrackPoints,
                                 featuresFound, err, winSize, 3, criteria);

        Point imagePoint;
        sanityCheck.limitTPDelta(currentTrackPoints[0], prevTrackPoints[0]);

        if (featuresFound[0])
        {
            imagePoint = Point(currentTrackPoints[0]);
        }
        prevTrackPoints = currentTrackPoints;
        emit positionUpdated(frame.clone(), imagePoint);
    }

    prevGrey = grey;
}

void StandardTrackingModule::setTrackPoint(cv::Mat frame, Point point)
{
    sanityCheck.checkFrameNotEmpty(frame);

    imageSize = frame.size();
    if (point.X() < 0 || point.X() >= imageSize.width ||
        point.Y() < 0 || point.Y() >= imageSize.height)
    {//TODO debug error
        return;
    }

    initialized = true;

    prevTrackPoints = std::vector<cv::Point2f>();
    prevTrackPoints.push_back(point.asCVPoint());
    cv::Mat prevGrey = ASM::convertToGray(frame);
}

cv::Size StandardTrackingModule::getImageSize()
{
    return imageSize;
}

bool StandardTrackingModule::isInitialized()
{
    return initialized;
}

} // namespace CMS
