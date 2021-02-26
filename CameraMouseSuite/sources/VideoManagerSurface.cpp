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

// This code is partially based on http://stackoverflow.com/questions/26229633/use-of-qabstractvideosurface

#include <QtGui/QMouseEvent>
#include "VideoManagerSurface.h"
#include "asmOpenCV.h"
#include "Point.h"
#include "TemplateTrackingModule.h"
#include <chrono>

#include <QtCore/QDebug>
#include "facemesh.h"


namespace CMS {

using namespace std::chrono;

VideoManagerSurface::VideoManagerSurface(Settings &settings, CameraMouseController *controller, QLabel *imageLabel, QObject *parent) :
    QAbstractVideoSurface(parent),
    settings(settings),
    controller(controller)
{
    this->draw_switch = false;
    this->imageLabel = imageLabel;
    supportedFormats = QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_RGB24
                                                         << QVideoFrame::Format_RGB32
                                                         << QVideoFrame::Format_ARGB32
                                                         << QVideoFrame::Format_CameraRaw;

    connect(controller, &CameraMouseController::frameProcessed, this , &VideoManagerSurface::frameToGui);
    connect(imageLabel, SIGNAL(mousePressed(QMouseEvent*)), this, SLOT(mousePressEvent(QMouseEvent*)));

    faceMesh = new FaceMesh();
    connect(faceMesh, SIGNAL(emitPixel(const QImage&)), this, SLOT(showMesh(const QImage)));
    faceMesh->start();

}

VideoManagerSurface::~VideoManagerSurface()
{
    // TODO Move to MainWindow if we decide to keep the pointer there
    delete(controller);
}

QList<QVideoFrame::PixelFormat> VideoManagerSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle)
    {
        return supportedFormats;
    }
    else
    {
        return QList<QVideoFrame::PixelFormat>();
    }
}

inline
size_t get_current_time_milliseconds(){
    return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}

void VideoManagerSurface::frameToGui(Point featurePosition){
    draw_switch = true;
    this->featurePosition = featurePosition;
}

bool VideoManagerSurface::present(const QVideoFrame &frame)
{
        QVideoFrame frameCopy(frame);
        stampFrame();
        if(!frameCopy.map(QAbstractVideoBuffer::ReadOnly))
        {
           setError(ResourceError);
           return false;
        }
        format = frame.pixelFormat();

         // This is a shallow operation. it just refer the frame buffer
        QImage image(
                frameCopy.bits(),
                frameCopy.width(),
                frameCopy.height(),
                frameCopy.bytesPerLine(),
                QVideoFrame::imageFormatFromPixelFormat(frameCopy.pixelFormat()));

        // The kind of mirroring needed depends on the OS
        #ifdef Q_OS_LINUX
            image = image.mirrored(true, false);
        #elif defined Q_OS_WIN
            image = image.mirrored(true, true);
        #elif defined Q_OS_MAC
            image = image.mirrored(true, false);
        #endif
        cv::Mat mat = ASM::QImageToCvMat(image);

        controller->sendFrame(mat);
        faceMesh->setFrame(mat);

        /*if(draw_switch){
            controller->drawOnFrame(mat, featurePosition);
            draw_switch = false;

             image = QImage(mat.data,
                           mat.cols,
                           mat.rows,
                           mat.step,
                           QVideoFrame::imageFormatFromPixelFormat(format));

             drawText(image, "REAL FPS:"+std::to_string(eval_fps()));
        }

        if (frameSize.isEmpty())
        {
            settings.setFrameSize(Point(image.size()));
            frameSize = image.size();
            scaledFrameSize = image.size();
            frameOffset = Point(imageLabel->size().width() - image.width(), imageLabel->size().height() - image.height())/2;
        }*/

        // QPixmap::fromImage create a new buffer for the pixmap
        //imageLabel->setPixmap(QPixmap::fromImage(image));
        //imageLabel->update();
        // Release the data
        frameCopy.unmap();



        return true;
}


void VideoManagerSurface::mousePressEvent(QMouseEvent *event)
{
    if (frameSize.isEmpty())
        return;
//    double offX = frameOffset.X();
//    double offY = frameOffset.Y();
//    double x = (double) (event->x() - offX);
//    double y = (double) (event->y() - offY);
    controller->processClick(Point(event->x(), event->y()));
}

void VideoManagerSurface :: showMesh(const QImage &img)
{
    QImage image(img);
    if(draw_switch){
            cv::Mat mat = ASM::QImageToCvMat(img);
            controller->drawOnFrame(mat, featurePosition);
            draw_switch = false;

             image = QImage(mat.data,
                           mat.cols,
                           mat.rows,
                           mat.step,
                           QVideoFrame::imageFormatFromPixelFormat(format));

             drawText(image, "REAL FPS:"+std::to_string(eval_fps()));
        }

        if (frameSize.isEmpty())
        {
            settings.setFrameSize(Point(image.size()));
            frameSize = image.size();
            scaledFrameSize = image.size();
            frameOffset = Point(imageLabel->size().width() - image.width(), imageLabel->size().height() - image.height())/2;
        }

    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->update();
}

} // namespace CMS