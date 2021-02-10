 load("//:qt.bzl", "qt_ui_library", "qt_cc_library", "qt_resource")

qt_resource(
    name = "resources",
    files = glob([
        "resources/icons.qrc",
	"images/*"
    ]),
)

qt_ui_library(
        name = "forms",
        ui = "forms/mainWindows.ui",
	deps = ["@qt//:qt_widgets"],
)

qt_cc_library(
        name = "library",
        srcs = glob(["sources/*.cpp"]),
        hdrs = glob(["headers/*.h"]),
        deps = [
        "@qt//:qt_core",
        "@qt//:qt_widgets",
        ":forms"],
        includes = ["headers/", "resources/"],
)

cc_binary(
    name = "main",
    srcs = glob(["sources/main.cpp"]),
    includes = glob(["headers/*.h"]),
    deps = [
        "@qt//:qt_core",
        "@qt//:qt_widgets",
        ":forms",
        ":library",
        ":resources",
    ],
)
