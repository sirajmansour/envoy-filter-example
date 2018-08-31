#pragma once

#include <string>

#include "envoy/server/filter_config.h"

#include "kinesis-filter/kinesis_filter_config.pb.h"
#include <aws/core/Aws.h>
#include <aws/kinesis/KinesisClient.h>

namespace Envoy {
namespace Http {

class KinesisFilterConfig {
public:
  KinesisFilterConfig(const kinesis::Config& config);

  const std::string& awsRegion() const { return aws_region_; }
  const std::string& awsAccessKeyId() const { return aws_access_key_id_; }
  const std::string& awsAccessKeySecret() const { return aws_access_key_secret_; }

private:
  const std::string aws_region_;
  const std::string aws_access_key_id_;
  const std::string aws_access_key_secret_;
};

typedef std::shared_ptr<KinesisFilterConfig> KinesisFilterConfigSharedPtr;

class KinesisFilter : public StreamDecoderFilter {
public:
  KinesisFilter(KinesisFilterConfigSharedPtr);
  ~KinesisFilter();

  // Http::StreamFilterBase
  void onDestroy() override;

  // Http::StreamDecoderFilter
  FilterHeadersStatus decodeHeaders(HeaderMap&, bool) override;
  FilterDataStatus decodeData(Buffer::Instance&, bool) override;
  FilterTrailersStatus decodeTrailers(HeaderMap&) override;
  void setDecoderFilterCallbacks(StreamDecoderFilterCallbacks&) override;

private:
  const KinesisFilterConfigSharedPtr config_;
  StreamDecoderFilterCallbacks* decoder_callbacks_;
  const std::shared_ptr<Aws::Kinesis::KinesisClient> kinesis_client_;
};

} // namespace Http
} // namespace Envoy
