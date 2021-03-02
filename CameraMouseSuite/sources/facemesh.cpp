#include "facemesh.h"
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include "mediapipe/calculators/util/detections_to_render_data_calculator.pb.h"
#include "mediapipe/framework/formats/detection.pb.h"

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

void FaceMesh :: run()
{
        //This function Run MPP Graph
        RunMPPGraph();
}

void FaceMesh :: recv()
{
        qDebug() << "Timer done ";
        isReady = true;
}

mediapipe::Status FaceMesh :: RunMPPGraph()
{
        std::string calculator_graph_config_contents;
        MP_RETURN_IF_ERROR(mediapipe::file::GetContents(FLAGS_calculator_graph_config_file, &calculator_graph_config_contents));
        mediapipe::CalculatorGraphConfig config = mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(calculator_graph_config_contents);
        MP_RETURN_IF_ERROR(graph.Initialize(config));

        
        std::cout << "Start running the calculator graph. \n";
        ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller poller, graph.AddOutputStreamPoller(kOutputStream));
        MP_RETURN_IF_ERROR(graph.StartRun({}));

        while (!isInterruptionRequested()) 
        {
                // Get the graph result packet, or stop if that fails.
                mediapipe::Packet packet;
                if (!poller.Next(&packet)) break;
                auto& output_frame = packet.Get<mediapipe::ImageFrame>();

                // Convert back to opencv for display or saving.
                cv::Mat output_frame_mat = mediapipe::formats::MatView(&output_frame);
                cv::cvtColor(output_frame_mat, output_frame_mat, cv::COLOR_RGB2BGR);

                cv::imshow("Mediapipe Output", output_frame_mat);
                
                QImage img;
                if (output_frame_mat.channels()== 3)
                {
                        img = QImage((const unsigned char*)(output_frame_mat.data), output_frame_mat.cols,output_frame_mat.rows,QImage::Format_RGB888);
                }else{
                        img = QImage((const unsigned char*)(output_frame_mat.data), output_frame_mat.cols,output_frame_mat.rows,QImage::Format_Indexed8);
                }

                emit emitPixel(img);
        }

        LOG(INFO) << "Shutting down.";
        MP_RETURN_IF_ERROR(graph.CloseInputStream(kInputStream));
        return graph.WaitUntilDone();
}

FaceMesh :: ~FaceMesh()
{
    
}