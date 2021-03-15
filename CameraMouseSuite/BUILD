load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//:qt.bzl", "qt_cc_library", "qt_resource", "qt_ui_library")

qt_resource(
    name = "resources",
    files = glob([
        "resources/icons.qrc",
        "images/*",
    ]),
)

qt_ui_library(
    name = "forms",
    ui = "forms/mainWindow.ui",
    deps = ["@qt//:qt_widgets"],
)

cc_library(
    name = "mediapipe_lib",
    copts = ["/std:c++17"],
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
)

qt_cc_library(
    name = "library",
    srcs = glob(["sources/*.cpp"]),
    hdrs = glob(["headers/*.h"]),
    copts = [
        "/std:c++17",
        "/opencv_world3410",
    ],
    includes = [
        "headers/",
        "resources/",
    ],
    linkopts = [
        "user32.lib",
        "Winmm.lib",
    ],
    deps = [
        ":forms",
        ":mediapipe_lib",
        "@qt//:qt_core",
        "@qt//:qt_multimedia",
        "@qt//:qt_multimediawidgets",
        "@qt//:qt_network",
        "@qt//:qt_widgets",
    ],
)

cc_binary(
    name = "main",
    srcs = glob(["sources/main.cpp"]),
    copts = [
        "/std:c++17",
        "/opencv_world3410",
    ],
    includes = glob(["headers/*.h"]),
    deps = [
        ":forms",
        ":library",
        ":mediapipe_lib",
        ":resources",
        "@qt//:qt_core",
        "@qt//:qt_multimedia",
        "@qt//:qt_widgets",
    ],
)
