// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Invoicing/FnsRegistrationMessageInfo.pb.h"

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
namespace Invoicing {

namespace {

const ::google::protobuf::Descriptor* FnsRegistrationMessageInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  FnsRegistrationMessageInfo_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Invoicing_2fFnsRegistrationMessageInfo_2eproto() {
  protobuf_AddDesc_Invoicing_2fFnsRegistrationMessageInfo_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Invoicing/FnsRegistrationMessageInfo.proto");
  GOOGLE_CHECK(file != NULL);
  FnsRegistrationMessageInfo_descriptor_ = file->message_type(0);
  static const int FnsRegistrationMessageInfo_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FnsRegistrationMessageInfo, certificates_),
  };
  FnsRegistrationMessageInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      FnsRegistrationMessageInfo_descriptor_,
      FnsRegistrationMessageInfo::default_instance_,
      FnsRegistrationMessageInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FnsRegistrationMessageInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(FnsRegistrationMessageInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(FnsRegistrationMessageInfo));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Invoicing_2fFnsRegistrationMessageInfo_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    FnsRegistrationMessageInfo_descriptor_, &FnsRegistrationMessageInfo::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Invoicing_2fFnsRegistrationMessageInfo_2eproto() {
  delete FnsRegistrationMessageInfo::default_instance_;
  delete FnsRegistrationMessageInfo_reflection_;
}

void protobuf_AddDesc_Invoicing_2fFnsRegistrationMessageInfo_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n*Invoicing/FnsRegistrationMessageInfo.p"
    "roto\022\032Diadoc.Api.Proto.Invoicing\"2\n\032FnsR"
    "egistrationMessageInfo\022\024\n\014Certificates\030\001"
    " \003(\014", 124);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Invoicing/FnsRegistrationMessageInfo.proto", &protobuf_RegisterTypes);
  FnsRegistrationMessageInfo::default_instance_ = new FnsRegistrationMessageInfo();
  FnsRegistrationMessageInfo::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Invoicing_2fFnsRegistrationMessageInfo_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Invoicing_2fFnsRegistrationMessageInfo_2eproto {
  StaticDescriptorInitializer_Invoicing_2fFnsRegistrationMessageInfo_2eproto() {
    protobuf_AddDesc_Invoicing_2fFnsRegistrationMessageInfo_2eproto();
  }
} static_descriptor_initializer_Invoicing_2fFnsRegistrationMessageInfo_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int FnsRegistrationMessageInfo::kCertificatesFieldNumber;
#endif  // !_MSC_VER

FnsRegistrationMessageInfo::FnsRegistrationMessageInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void FnsRegistrationMessageInfo::InitAsDefaultInstance() {
}

FnsRegistrationMessageInfo::FnsRegistrationMessageInfo(const FnsRegistrationMessageInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void FnsRegistrationMessageInfo::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

FnsRegistrationMessageInfo::~FnsRegistrationMessageInfo() {
  SharedDtor();
}

void FnsRegistrationMessageInfo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void FnsRegistrationMessageInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* FnsRegistrationMessageInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return FnsRegistrationMessageInfo_descriptor_;
}

const FnsRegistrationMessageInfo& FnsRegistrationMessageInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Invoicing_2fFnsRegistrationMessageInfo_2eproto();  return *default_instance_;
}

FnsRegistrationMessageInfo* FnsRegistrationMessageInfo::default_instance_ = NULL;

FnsRegistrationMessageInfo* FnsRegistrationMessageInfo::New() const {
  return new FnsRegistrationMessageInfo;
}

void FnsRegistrationMessageInfo::Clear() {
  certificates_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool FnsRegistrationMessageInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated bytes Certificates = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_Certificates:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->add_certificates()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_Certificates;
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void FnsRegistrationMessageInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated bytes Certificates = 1;
  for (int i = 0; i < this->certificates_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      1, this->certificates(i), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* FnsRegistrationMessageInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated bytes Certificates = 1;
  for (int i = 0; i < this->certificates_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteBytesToArray(1, this->certificates(i), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int FnsRegistrationMessageInfo::ByteSize() const {
  int total_size = 0;
  
  // repeated bytes Certificates = 1;
  total_size += 1 * this->certificates_size();
  for (int i = 0; i < this->certificates_size(); i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::BytesSize(
      this->certificates(i));
  }
  
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

void FnsRegistrationMessageInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const FnsRegistrationMessageInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const FnsRegistrationMessageInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void FnsRegistrationMessageInfo::MergeFrom(const FnsRegistrationMessageInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  certificates_.MergeFrom(from.certificates_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void FnsRegistrationMessageInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void FnsRegistrationMessageInfo::CopyFrom(const FnsRegistrationMessageInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FnsRegistrationMessageInfo::IsInitialized() const {
  
  return true;
}

void FnsRegistrationMessageInfo::Swap(FnsRegistrationMessageInfo* other) {
  if (other != this) {
    certificates_.Swap(&other->certificates_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata FnsRegistrationMessageInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = FnsRegistrationMessageInfo_descriptor_;
  metadata.reflection = FnsRegistrationMessageInfo_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Invoicing
}  // namespace Proto
}  // namespace Api
}  // namespace Diadoc

// @@protoc_insertion_point(global_scope)