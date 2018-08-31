licenses(["notice"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
    "envoy_package",
)

envoy_package()

cc_import(
  name = "aws_core_redist",
  shared_library = "v141/aws-cpp-sdk-core.dll",
)

cc_import(
  name = "aws_core_static",
  static_library = "v141/aws-cpp-sdk-core.lib",
)

envoy_cc_library(
    name = "aws_core_lib",
    hdrs = glob(["v141/include/**/*.h"]),
    repository = "@envoy",
    deps = [
        ":aws_core_redist",
        ":aws_core_static"
    ],
)