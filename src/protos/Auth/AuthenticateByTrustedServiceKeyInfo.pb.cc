// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Auth/AuthenticateByTrustedServiceKeyInfo.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Auth/AuthenticateByTrustedServiceKeyInfo.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace Diadoc {
namespace Api {
namespace Proto {
namespace Auth {

namespace {

const ::google::protobuf::Descriptor* AuthenticateByTrustedServiceKeyInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AuthenticateByTrustedServiceKeyInfo_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto() {
  protobuf_AddDesc_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Auth/AuthenticateByTrustedServiceKeyInfo.proto");
  GOOGLE_CHECK(file != NULL);
  AuthenticateByTrustedServiceKeyInfo_descriptor_ = file->message_type(0);
  static const int AuthenticateByTrustedServiceKeyInfo_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AuthenticateByTrustedServiceKeyInfo, key_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AuthenticateByTrustedServiceKeyInfo, id_),
  };
  AuthenticateByTrustedServiceKeyInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AuthenticateByTrustedServiceKeyInfo_descriptor_,
      AuthenticateByTrustedServiceKeyInfo::default_instance_,
      AuthenticateByTrustedServiceKeyInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AuthenticateByTrustedServiceKeyInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AuthenticateByTrustedServiceKeyInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AuthenticateByTrustedServiceKeyInfo));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AuthenticateByTrustedServiceKeyInfo_descriptor_, &AuthenticateByTrustedServiceKeyInfo::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto() {
  delete AuthenticateByTrustedServiceKeyInfo::default_instance_;
  delete AuthenticateByTrustedServiceKeyInfo_reflection_;
}

void protobuf_AddDesc_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n.Auth/AuthenticateByTrustedServiceKeyIn"
    "fo.proto\022\025Diadoc.Api.Proto.Auth\">\n#Authe"
    "nticateByTrustedServiceKeyInfo\022\013\n\003Key\030\001 "
    "\002(\t\022\n\n\002Id\030\002 \002(\t", 135);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Auth/AuthenticateByTrustedServiceKeyInfo.proto", &protobuf_RegisterTypes);
  AuthenticateByTrustedServiceKeyInfo::default_instance_ = new AuthenticateByTrustedServiceKeyInfo();
  AuthenticateByTrustedServiceKeyInfo::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto {
  StaticDescriptorInitializer_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto() {
    protobuf_AddDesc_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto();
  }
} static_descriptor_initializer_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int AuthenticateByTrustedServiceKeyInfo::kKeyFieldNumber;
const int AuthenticateByTrustedServiceKeyInfo::kIdFieldNumber;
#endif  // !_MSC_VER

AuthenticateByTrustedServiceKeyInfo::AuthenticateByTrustedServiceKeyInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo)
}

void AuthenticateByTrustedServiceKeyInfo::InitAsDefaultInstance() {
}

AuthenticateByTrustedServiceKeyInfo::AuthenticateByTrustedServiceKeyInfo(const AuthenticateByTrustedServiceKeyInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo)
}

void AuthenticateByTrustedServiceKeyInfo::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  key_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  id_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AuthenticateByTrustedServiceKeyInfo::~AuthenticateByTrustedServiceKeyInfo() {
  // @@protoc_insertion_point(destructor:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo)
  SharedDtor();
}

void AuthenticateByTrustedServiceKeyInfo::SharedDtor() {
  if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete key_;
  }
  if (id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete id_;
  }
  if (this != default_instance_) {
  }
}

void AuthenticateByTrustedServiceKeyInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AuthenticateByTrustedServiceKeyInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AuthenticateByTrustedServiceKeyInfo_descriptor_;
}

const AuthenticateByTrustedServiceKeyInfo& AuthenticateByTrustedServiceKeyInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto();
  return *default_instance_;
}

AuthenticateByTrustedServiceKeyInfo* AuthenticateByTrustedServiceKeyInfo::default_instance_ = NULL;

AuthenticateByTrustedServiceKeyInfo* AuthenticateByTrustedServiceKeyInfo::New() const {
  return new AuthenticateByTrustedServiceKeyInfo;
}

void AuthenticateByTrustedServiceKeyInfo::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    if (has_key()) {
      if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        key_->clear();
      }
    }
    if (has_id()) {
      if (id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        id_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AuthenticateByTrustedServiceKeyInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string Key = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_key()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->key().data(), this->key().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "key");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_Id;
        break;
      }

      // required string Id = 2;
      case 2: {
        if (tag == 18) {
         parse_Id:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_id()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->id().data(), this->id().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "id");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo)
  return false;
#undef DO_
}

void AuthenticateByTrustedServiceKeyInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo)
  // required string Key = 1;
  if (has_key()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->key().data(), this->key().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "key");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->key(), output);
  }

  // required string Id = 2;
  if (has_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->id().data(), this->id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "id");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->id(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo)
}

::google::protobuf::uint8* AuthenticateByTrustedServiceKeyInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo)
  // required string Key = 1;
  if (has_key()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->key().data(), this->key().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "key");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->key(), target);
  }

  // required string Id = 2;
  if (has_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->id().data(), this->id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "id");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->id(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo)
  return target;
}

int AuthenticateByTrustedServiceKeyInfo::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string Key = 1;
    if (has_key()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->key());
    }

    // required string Id = 2;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->id());
    }

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

void AuthenticateByTrustedServiceKeyInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AuthenticateByTrustedServiceKeyInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AuthenticateByTrustedServiceKeyInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AuthenticateByTrustedServiceKeyInfo::MergeFrom(const AuthenticateByTrustedServiceKeyInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_key()) {
      set_key(from.key());
    }
    if (from.has_id()) {
      set_id(from.id());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AuthenticateByTrustedServiceKeyInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AuthenticateByTrustedServiceKeyInfo::CopyFrom(const AuthenticateByTrustedServiceKeyInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AuthenticateByTrustedServiceKeyInfo::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void AuthenticateByTrustedServiceKeyInfo::Swap(AuthenticateByTrustedServiceKeyInfo* other) {
  if (other != this) {
    std::swap(key_, other->key_);
    std::swap(id_, other->id_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AuthenticateByTrustedServiceKeyInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AuthenticateByTrustedServiceKeyInfo_descriptor_;
  metadata.reflection = AuthenticateByTrustedServiceKeyInfo_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Auth
}  // namespace Proto
}  // namespace Api
}  // namespace Diadoc

// @@protoc_insertion_point(global_scope)
