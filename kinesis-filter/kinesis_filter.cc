#include <string>

#include "kinesis_filter.h"
#include "envoy/server/filter_config.h"
#include <aws/core/Aws.h>
#include <aws/kinesis/KinesisClient.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/external/tinyxml2/tinyxml2.h>

namespace Envoy {
namespace Http {

KinesisFilterConfig::KinesisFilterConfig(const kinesis::Config& proto_config)
    : aws_region_(proto_config.region()), aws_access_key_id_(proto_config.access_key_id()),
      aws_access_key_secret_(proto_config.access_key_secret()) {}

KinesisFilter::KinesisFilter(KinesisFilterConfigSharedPtr config) : config_(config) {
  kinesis_client_ = Aws::MakeShared<Aws::Kinesis::KinesisClient>(Aws::External::tinyxml2::ALLOCATION_TAG,Aws::Auth::AWSCredentials::AWSCredentials((config.get())->awsAccessKeyId(),(config.get())->awsAccessKeySecret()))
}

KinesisFilter::~KinesisFilter() {}

void KinesisFilter::onDestroy() {}

FilterHeadersStatus KinesisFilter::decodeHeaders(HeaderMap&, bool) {
  return FilterHeadersStatus::Continue;
}

FilterDataStatus KinesisFilter::decodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus KinesisFilter::decodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void KinesisFilter::setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

} // namespace Http
} // namespace Envoy
