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

#ifndef CMS_VIDEOMANAGERSURFACE_H
#define CMS_VIDEOMANAGERSURFACE_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtWidgets/QLabel>
#include <QtMultimedia/QVideoFrame>
#include <QtMultimedia/QAbstractVideoSurface>
#include <opencv/cv.h>
#include "TrackingModule.h"
#include "MouseControlModule.h"
#include "Keyboard.h"
#include "CameraMouseController.h"
#include "Point.h"
#include "Settings.h"

#include <chrono>
#include <algorithm>
#include <QtGui/QPen>
#include <QtGui/QPainter>

constexpr double c_billion = 1000000000.0;
constexpr uint8_t fps_smooth_count = 30;

namespace CMS {

// TODO I think this class has too many resposibilities

class VideoManagerSurface : public QAbstractVideoSurface
{
    Q_OBJECT

public:
    VideoManagerSurface(Settings &settings, CameraMouseController *controller, QLabel *imageLabel, QObject *parent = 0);
    ~VideoManagerSurface();

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;
    bool present(const QVideoFrame &frame);
    void frameToProcess(cv::Mat);
    double eval_fps(){
        if (frame_timestamps.size() < 5) return 0.0;
        std::vector<double> fpsque{};
        std::transform(std::begin(frame_timestamps), std::end(frame_timestamps)-1,
                       std::begin(frame_timestamps)+1, std::back_inserter(fpsque),
                       [](auto ts1, auto ts2)->double{
            return 1/(std::chrono::duration_cast<std::chrono::nanoseconds>(ts2 - ts1).count()/c_billion);
            });
        return std::accumulate(begin(fpsque), end(fpsque), 0.0)/fpsque.size();
    }

    void drawText(QImage& current_frame, std::string text){
        QPainter p(&current_frame);
        p.setPen(QPen(Qt::red));
        p.setFont(QFont("Times", 12, QFont::Bold));
        p.drawText(current_frame.rect(), Qt::AlignTop, text.c_str());
    }

    std::deque<std::chrono::duration<double>> frame_timestamps;
    
protected slots:
    void mousePressEvent(QMouseEvent *event);
    void frameToGui(Point featurePosition);
    void stampFrame(){
        frame_timestamps.push_back(std::chrono::high_resolution_clock::now().time_since_epoch());
        if(frame_timestamps.size() > fps_smooth_count)
            frame_timestamps.pop_front();
    }
private:
    bool draw_switch;
    Point featurePosition;
    Settings &settings;
    CameraMouseController *controller;
    QLabel *imageLabel;
    QList<QVideoFrame::PixelFormat> supportedFormats;
    QSize frameSize;
    QSize scaledFrameSize;
    Point frameOffset;
    QVideoFrame::PixelFormat format;
};

} // namespace CMS

#endif // CMS_VIDEOMANAGERSURFACE_H
