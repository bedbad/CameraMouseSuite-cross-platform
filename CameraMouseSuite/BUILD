load("//:qt.bzl", "qt_ui_library", "qt_cc_library", "qt_resource")

qt_resource(
    name = "resources",
    files = glob(["resources/icons.qrc", "images/*",]),
)

qt_ui_library(
    name = "forms",
    ui = "forms/mainWindow.ui",
    deps = ["@qt//:qt_widgets"],
)

cc_library(
    name = "mediapipe_lib",
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/formats:image_frame",
        "@mediapipe//mediapipe/framework/formats:image_frame_opencv",
        "@mediapipe//mediapipe/framework/port:commandlineflags",
        "@mediapipe//mediapipe/framework/port:file_helpers",
        "@mediapipe//mediapipe/framework/port:opencv_highgui",
        "@mediapipe//mediapipe/framework/port:opencv_imgproc",
        "@mediapipe//mediapipe/framework/port:opencv_video",
        "@mediapipe//mediapipe/framework/port:parse_text_proto",
        "@mediapipe//mediapipe/framework/port:status",
        "@mediapipe//mediapipe/graphs/face_mesh:desktop_live_calculators",
    ],
    copts = ["/std:c++17"],
)

qt_cc_library(
        name = "library",
        srcs = glob(["sources/*.cpp"]),
        hdrs = glob(["headers/*.h"]),
        deps = [
        "@qt//:qt_core",
        "@qt//:qt_multimedia",
        ":mediapipe_lib",
        "@qt//:qt_widgets",
        ":forms",
        ],
        includes = ["headers/", "resources/"],
        copts = ["/std:c++17"],
        linkopts = ['user32.lib'],
)

cc_binary(
    name = "main",
    srcs = glob(["sources/main.cpp"]),
    includes = glob(["headers/*.h"]),
    deps = [
        "@qt//:qt_core", 
        "@qt//:qt_multimedia",
        "@qt//:qt_widgets",
        ":forms",
        ":library",
        ":resources",
        ":mediapipe_lib",
    ],
    copts = ["/std:c++17"],
    linkopts = ['user32.lib'],
)
