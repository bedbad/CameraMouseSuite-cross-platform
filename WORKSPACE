workspace(name = "camera_mouse")

load("@camera_mouse//:qt_configure.bzl", "local_qt_path")

new_local_repository(
    name = "qt",
    build_file = "@camera_mouse//:qt.BUILD",
    path = "./",
)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

#
