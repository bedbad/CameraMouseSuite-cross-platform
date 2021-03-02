# CameraMouseSuite-cross-platform
CameraMouseSuite cross platform version. Implemented with Qt and OpenCV.

RUN:
bazel build -c opt --cxxopt="/std:c++17" :main --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH="C://Python38//python.exe" --experimental_repo_remote_exec  --cxxopt="/DM_PI=3.145" --verbose_failures
