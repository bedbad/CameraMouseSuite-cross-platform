#### Windows Build

 bazel build --cxxopt="//std:c++17" --cxxopt="//DM_PI=3.145" main --define MEDIAPIPE_DISABLE_GPU=1 --action_env PYTHON_BIN_PATH=$(which python)  --experimental_repo_remote_exec --verbose_failures
