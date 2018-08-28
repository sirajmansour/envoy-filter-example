#include <string>

#include "kinesis_filter.h"

#include "common/config/json_utility.h"
#include "envoy/registry/registry.h"

#include "kinesis-filter/kinesis_filter_config.pb.h"
#include "kinesis-filter/kinesis_filter_config.pb.validate.h"

namespace Envoy {
namespace Server {
namespace Configuration {

class KinesisFilterConfig : public NamedHttpFilterConfigFactory {
public:
  Http::FilterFactoryCb createFilterFactory(const Json::Object& json_config, const std::string&,
                                            FactoryContext& context) override {

    kinesis::Config proto_config;
    translateConfig(json_config, proto_config);

    return createFilter(proto_config, context);
  }

  Http::FilterFactoryCb createFilterFactoryFromProto(const Protobuf::Message& proto_config,
                                                     const std::string&,
                                                     FactoryContext& context) override {

    return createFilter(
        Envoy::MessageUtil::downcastAndValidate<const kinesis::Config&>(proto_config), context);
  }

  /**
   *  Return the Protobuf Message that represents your config incase you have config proto
   */
  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return ProtobufTypes::MessagePtr{new kinesis::Config()};
  }

  std::string name() override { return "kinesis"; }

private:
  Http::FilterFactoryCb createFilter(const kinesis::Config& proto_config, FactoryContext&) {
    Http::KinesisFilterConfigSharedPtr config =
        std::make_shared<Http::KinesisFilterConfig>(Http::KinesisFilterConfig(proto_config));

    return [config](Http::FilterChainFactoryCallbacks& callbacks) -> void {
      auto filter = new Http::KinesisFilter(config);
      callbacks.addStreamDecoderFilter(Http::StreamDecoderFilterSharedPtr{filter});
    };
  }

  void translateConfig(const Json::Object& json_config, kinesis::Config& proto_config) {

    // normally we want to validate the json_config againts a defined json-schema here.
    JSON_UTIL_SET_STRING(json_config, proto_config, region);
    JSON_UTIL_SET_STRING(json_config, proto_config, access_key_id);
    JSON_UTIL_SET_STRING(json_config, proto_config, access_key_secret);
  }
};

/**
 * Static registration for this filter configuration. @see RegisterFactory.
 */
static Registry::RegisterFactory<KinesisFilterConfig, NamedHttpFilterConfigFactory> register_;

} // namespace Configuration
} // namespace Server
} // namespace Envoy
