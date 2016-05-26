// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Docflow/ResolutionDocflow.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace Diadoc {
namespace Api {
namespace Proto {
namespace Docflow {

namespace {

const ::google::protobuf::Descriptor* ResolutionDocflow_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ResolutionDocflow_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Docflow_2fResolutionDocflow_2eproto() {
  protobuf_AddDesc_Docflow_2fResolutionDocflow_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Docflow/ResolutionDocflow.proto");
  GOOGLE_CHECK(file != NULL);
  ResolutionDocflow_descriptor_ = file->message_type(0);
  static const int ResolutionDocflow_offsets_[1] = {
  };
  ResolutionDocflow_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ResolutionDocflow_descriptor_,
      ResolutionDocflow::default_instance_,
      ResolutionDocflow_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ResolutionDocflow, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ResolutionDocflow, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ResolutionDocflow));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Docflow_2fResolutionDocflow_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ResolutionDocflow_descriptor_, &ResolutionDocflow::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Docflow_2fResolutionDocflow_2eproto() {
  delete ResolutionDocflow::default_instance_;
  delete ResolutionDocflow_reflection_;
}

void protobuf_AddDesc_Docflow_2fResolutionDocflow_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::Diadoc::Api::Proto::protobuf_AddDesc_Timestamp_2eproto();
  ::Diadoc::Api::Proto::protobuf_AddDesc_ResolutionTarget_2eproto();
  ::Diadoc::Api::Proto::Docflow::protobuf_AddDesc_Docflow_2fAttachment_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\037Docflow/ResolutionDocflow.proto\022\030Diado"
    "c.Api.Proto.Docflow\032\017Timestamp.proto\032\026Re"
    "solutionTarget.proto\032\030Docflow/Attachment"
    ".proto\"\023\n\021ResolutionDocflow", 147);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Docflow/ResolutionDocflow.proto", &protobuf_RegisterTypes);
  ResolutionDocflow::default_instance_ = new ResolutionDocflow();
  ResolutionDocflow::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Docflow_2fResolutionDocflow_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Docflow_2fResolutionDocflow_2eproto {
  StaticDescriptorInitializer_Docflow_2fResolutionDocflow_2eproto() {
    protobuf_AddDesc_Docflow_2fResolutionDocflow_2eproto();
  }
} static_descriptor_initializer_Docflow_2fResolutionDocflow_2eproto_;


// ===================================================================

#ifndef _MSC_VER
#endif  // !_MSC_VER

ResolutionDocflow::ResolutionDocflow()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void ResolutionDocflow::InitAsDefaultInstance() {
}

ResolutionDocflow::ResolutionDocflow(const ResolutionDocflow& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void ResolutionDocflow::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ResolutionDocflow::~ResolutionDocflow() {
  SharedDtor();
}

void ResolutionDocflow::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ResolutionDocflow::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ResolutionDocflow::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ResolutionDocflow_descriptor_;
}

const ResolutionDocflow& ResolutionDocflow::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Docflow_2fResolutionDocflow_2eproto();  return *default_instance_;
}

ResolutionDocflow* ResolutionDocflow::default_instance_ = NULL;

ResolutionDocflow* ResolutionDocflow::New() const {
  return new ResolutionDocflow;
}

void ResolutionDocflow::Clear() {
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ResolutionDocflow::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      return true;
    }
    DO_(::google::protobuf::internal::WireFormat::SkipField(
          input, tag, mutable_unknown_fields()));
  }
  return true;
#undef DO_
}

void ResolutionDocflow::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* ResolutionDocflow::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int ResolutionDocflow::ByteSize() const {
  int total_size = 0;
  
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ResolutionDocflow::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ResolutionDocflow* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ResolutionDocflow*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ResolutionDocflow::MergeFrom(const ResolutionDocflow& from) {
  GOOGLE_CHECK_NE(&from, this);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ResolutionDocflow::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ResolutionDocflow::CopyFrom(const ResolutionDocflow& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ResolutionDocflow::IsInitialized() const {
  
  return true;
}

void ResolutionDocflow::Swap(ResolutionDocflow* other) {
  if (other != this) {
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ResolutionDocflow::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ResolutionDocflow_descriptor_;
  metadata.reflection = ResolutionDocflow_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Docflow
}  // namespace Proto
}  // namespace Api
}  // namespace Diadoc

// @@protoc_insertion_point(global_scope)