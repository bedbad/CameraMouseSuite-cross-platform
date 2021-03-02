#include "facemesh.h"
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include "mediapipe/calculators/util/detections_to_render_data_calculator.pb.h"
#include "mediapipe/framework/formats/detection.pb.h"
#include "asmOpenCV.h"

DEFINE_string(calculator_graph_config_file, "../mediapipe/mediapipe/graphs/face_mesh/face_mesh_desktop_live.pbtxt", "");



FaceMesh :: FaceMesh(QObject *parent)
        : QThread(parent)
{
}

void FaceMesh :: setFrame(cv::Mat& img) 
{
        //cv::cvtColor(camera_frame_raw, camera_frame, cv::COLOR_BGR2RGB);
        // Wrap Mat into an ImageFrame.
        auto input_frame = absl::make_unique<mediapipe::ImageFrame>(mediapipe::ImageFormat::SRGB, img.cols, img.rows, mediapipe::ImageFrame::kDefaultAlignmentBoundary);
        cv::Mat input_frame_mat = mediapipe::formats::MatView(input_frame.get());
        img.copyTo(input_frame_mat);

        // Send image packet into the graph.
        size_t frame_timestamp_us = (double)cv::getTickCount() / (double)cv::getTickFrequency() * 1e6;
        graph.AddPacketToInputStream(kInputStream, mediapipe::Adopt(input_frame.release()).At(mediapipe::Timestamp(frame_timestamp_us)));
}

void FaceMesh :: receivePixel(const QImage& img)
{
        QImage image = img.copy();
        if(image.isNull())
                return;
        imagePipe.append(image);
}

void FaceMesh :: run()
{
        //This function Run MPP Graph
        RunMPPGraph();
}

mediapipe::Status FaceMesh :: RunMPPGraph()
{
        std::string calculator_graph_config_contents;
        MP_RETURN_IF_ERROR(mediapipe::file::GetContents(FLAGS_calculator_graph_config_file, &calculator_graph_config_contents));
        std::cout << "Get calculator graph config contents: " << calculator_graph_config_contents;
        mediapipe::CalculatorGraphConfig config = mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(calculator_graph_config_contents);

        std::cout << "Initialize the calculator graph.";
        mediapipe::CalculatorGraph graph;
        MP_RETURN_IF_ERROR(graph.Initialize(config));

        std::cout << "Initialize the camera or load the video.";

        std::cout << "Start running the calculator graph.";
        ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller poller, graph.AddOutputStreamPoller(kOutputStream));
        MP_RETURN_IF_ERROR(graph.StartRun({}));

        std::cout << "Start grabbing and processing frames.";
        bool grab_frames = true;
        while (grab_frames) 
        {
                // Capture opencv camera or video frame.

                if(imagePipe.isEmpty())
                        continue;
                QImage x = QImage(imagePipe.takeFirst());
                if(x.isNull()) continue;
                cv::Mat camera_frame_raw = ASM::QImageToCvMat(x);
                cv::imshow("Input", camera_frame_raw);

                cv::Mat camera_frame;
                cv::cvtColor(camera_frame_raw, camera_frame, cv::COLOR_BGR2RGB);
                cv::flip(camera_frame, camera_frame, /*flipcode=HORIZONTAL*/ 1);

                // Wrap Mat into an ImageFrame.
                auto input_frame = absl::make_unique<mediapipe::ImageFrame>( mediapipe::ImageFormat::SRGB, camera_frame.cols, camera_frame.rows, mediapipe::ImageFrame::kDefaultAlignmentBoundary);
                cv::Mat input_frame_mat = mediapipe::formats::MatView(input_frame.get());
                camera_frame.copyTo(input_frame_mat);

                // Send image packet into the graph.
                size_t frame_timestamp_us = (double)cv::getTickCount() / (double)cv::getTickFrequency() * 1e6;
                MP_RETURN_IF_ERROR(graph.AddPacketToInputStream( kInputStream, mediapipe::Adopt(input_frame.release()).At(mediapipe::Timestamp(frame_timestamp_us))));

                // Get the graph result packet, or stop if that fails.
                mediapipe::Packet packet;
                if (!poller.Next(&packet)) break;
                auto& output_frame = packet.Get<mediapipe::ImageFrame>();

                // Convert back to opencv for display or saving.
                cv::Mat output_frame_mat = mediapipe::formats::MatView(&output_frame);
                cv::cvtColor(output_frame_mat, output_frame_mat, cv::COLOR_RGB2BGR);
    
                cv::imshow("Output", output_frame_mat);
        }

        LOG(INFO) << "Shutting down.";
        MP_RETURN_IF_ERROR(graph.CloseInputStream(kInputStream));
        return graph.WaitUntilDone();
}

FaceMesh :: ~FaceMesh()
{
    
}