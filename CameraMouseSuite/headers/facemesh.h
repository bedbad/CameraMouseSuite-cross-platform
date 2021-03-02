#include <cstdlib>
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/commandlineflags.h"
#include "mediapipe/framework/port/file_helpers.h"
#include "mediapipe/framework/port/opencv_highgui_inc.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"
#include "mediapipe/framework/port/opencv_video_inc.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/framework/port/status.h"

#include <QtCore/QThread>
#include <QtGui/QImage>
#include <QtCore/QList>
#include <algorithm>

constexpr char kInputStream[] = "input_video";
constexpr char kOutputStream[] = "output_video";

class FaceMesh 
        : public QThread
{
    Q_OBJECT
public:
    explicit FaceMesh(QObject *parent = 0);
    void run();
    mediapipe::Status RunMPPGraph();
    ~FaceMesh();

signals:
    void emitPixel(const QImage &image);
};