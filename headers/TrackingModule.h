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

#ifndef CMS_TRACKINGMODULE_H
#define CMS_TRACKINGMODULE_H

#include <cv.h>

#include <QObject>
#include <QtCore>
#include "Point.h"

namespace CMS {

class ITrackingModule : public QObject
{
    Q_OBJECT
public:
    virtual ~ITrackingModule();
    virtual cv::Size getImageSize() = 0;
    virtual bool isInitialized() = 0;

signals:
    void positionUpdated(cv::Mat, Point point);
public slots:
    virtual void setTrackPoint(cv::Mat frame, Point point) = 0;
    virtual void process(cv::Mat frame) = 0;

};

class TrackingModuleSanityCheck
{
public:
    TrackingModuleSanityCheck(ITrackingModule *trackingModule);
    void checkInitialized();
    void checkFrameNotEmpty(const cv::Mat &frame);
    void checkFrameSize(const cv::Mat &frame);
    void limitTPDelta(cv::Point2f &cur, cv::Point2f &last);

private:
    ITrackingModule *trackingModule;
};

} // namespace CMS

#endif // CMS_TRACKINGMODULE_H

