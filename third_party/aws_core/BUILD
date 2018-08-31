licenses(["notice"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
    "envoy_package",
)

envoy_package()

# cc_import(
#   name = "aws_core_redist",
#   shared_library = "v141/aws-cpp-sdk-core.dll",
# )

cc_import(
  name = "aws_core_lib",
  hdrs = glob(["v141/include/**/*.h"]),
  static_library = "v141/aws-cpp-sdk-core.lib",
  shared_library = "v141/aws-cpp-sdk-core.dll",
)

# cc_library(
#     name = "aws_core_lib",
#     includes = [
#         "v141/include/",
#     ],
#     deps = [
#         ":aws_core"
#     ],
#     alwayslink = 1
# )