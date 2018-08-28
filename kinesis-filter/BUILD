package(default_visibility = ["//visibility:public"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
    "envoy_cc_library",
    "envoy_cc_test",
    "envoy_proto_library",
)

envoy_cc_binary(
    name = "envoy",
    repository = "@envoy",
    deps = [
        ":kinesis_filter_config",
        "@envoy//source/exe:envoy_main_entry_lib",
    ],
)

envoy_proto_library(
    name = "kinesis_filter_config_proto",
    srcs = ["kinesis_filter_config.proto"]
)

envoy_cc_library(
    name = "kinesis_filter_lib",
    srcs = ["kinesis_filter.cc"],
    hdrs = ["kinesis_filter.h"],
    repository = "@envoy",
    deps = [
        "//:kinesis_filter_config_proto",
        "@envoy//source/exe:envoy_common_lib",
    ],
)

envoy_cc_library(
    name = "kinesis_filter_config",
    srcs = ["kinesis_filter_config.cc"],
    repository = "@envoy",
    deps = [
        "//:kinesis_filter_config_proto",
        ":kinesis_filter_lib",
        "@envoy//include/envoy/server:filter_config_interface",
    ],
)
