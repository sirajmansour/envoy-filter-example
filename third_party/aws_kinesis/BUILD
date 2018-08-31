licenses(["notice"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
    "envoy_package",
)

envoy_package()

cc_import(
  name = "aws_kinesis_redist",
  shared_library = "v141/aws-cpp-sdk-kinesis.dll",
)

cc_import(
  name = "aws_kinesis_static",
  static_library = "v141/aws-cpp-sdk-kinesis.lib",
)

cc_library(
    name = "aws_kinesis_lib",
    hdrs = glob(["v141/include/**/*.h"]),
    includes = [
        "v141/include/",
    ],
    repository = "@envoy",
    deps = [
        "//third_party/aws_core:aws_core_lib",
        ":aws_kinesis_redist",
        ":aws_kinesis_static"
    ],
)