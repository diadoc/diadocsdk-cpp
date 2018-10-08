// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Auth/AuthenticateByTrustedServiceKeyInfo.proto

#ifndef PROTOBUF_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto__INCLUDED
#define PROTOBUF_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace Diadoc {
namespace Api {
namespace Proto {
namespace Auth {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto();
void protobuf_AssignDesc_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto();
void protobuf_ShutdownFile_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto();

class AuthenticateByTrustedServiceKeyInfo;

// ===================================================================

class AuthenticateByTrustedServiceKeyInfo : public ::google::protobuf::Message {
 public:
  AuthenticateByTrustedServiceKeyInfo();
  virtual ~AuthenticateByTrustedServiceKeyInfo();

  AuthenticateByTrustedServiceKeyInfo(const AuthenticateByTrustedServiceKeyInfo& from);

  inline AuthenticateByTrustedServiceKeyInfo& operator=(const AuthenticateByTrustedServiceKeyInfo& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const AuthenticateByTrustedServiceKeyInfo& default_instance();

  void Swap(AuthenticateByTrustedServiceKeyInfo* other);

  // implements Message ----------------------------------------------

  AuthenticateByTrustedServiceKeyInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AuthenticateByTrustedServiceKeyInfo& from);
  void MergeFrom(const AuthenticateByTrustedServiceKeyInfo& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string Key = 1;
  inline bool has_key() const;
  inline void clear_key();
  static const int kKeyFieldNumber = 1;
  inline const ::std::string& key() const;
  inline void set_key(const ::std::string& value);
  inline void set_key(const char* value);
  inline void set_key(const char* value, size_t size);
  inline ::std::string* mutable_key();
  inline ::std::string* release_key();
  inline void set_allocated_key(::std::string* key);

  // required string Id = 2;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 2;
  inline const ::std::string& id() const;
  inline void set_id(const ::std::string& value);
  inline void set_id(const char* value);
  inline void set_id(const char* value, size_t size);
  inline ::std::string* mutable_id();
  inline ::std::string* release_id();
  inline void set_allocated_id(::std::string* id);

  // @@protoc_insertion_point(class_scope:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo)
 private:
  inline void set_has_key();
  inline void clear_has_key();
  inline void set_has_id();
  inline void clear_has_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* key_;
  ::std::string* id_;
  friend void  protobuf_AddDesc_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto();
  friend void protobuf_AssignDesc_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto();
  friend void protobuf_ShutdownFile_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto();

  void InitAsDefaultInstance();
  static AuthenticateByTrustedServiceKeyInfo* default_instance_;
};
// ===================================================================


// ===================================================================

// AuthenticateByTrustedServiceKeyInfo

// required string Key = 1;
inline bool AuthenticateByTrustedServiceKeyInfo::has_key() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AuthenticateByTrustedServiceKeyInfo::set_has_key() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AuthenticateByTrustedServiceKeyInfo::clear_has_key() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AuthenticateByTrustedServiceKeyInfo::clear_key() {
  if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    key_->clear();
  }
  clear_has_key();
}
inline const ::std::string& AuthenticateByTrustedServiceKeyInfo::key() const {
  // @@protoc_insertion_point(field_get:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo.Key)
  return *key_;
}
inline void AuthenticateByTrustedServiceKeyInfo::set_key(const ::std::string& value) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    key_ = new ::std::string;
  }
  key_->assign(value);
  // @@protoc_insertion_point(field_set:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo.Key)
}
inline void AuthenticateByTrustedServiceKeyInfo::set_key(const char* value) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    key_ = new ::std::string;
  }
  key_->assign(value);
  // @@protoc_insertion_point(field_set_char:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo.Key)
}
inline void AuthenticateByTrustedServiceKeyInfo::set_key(const char* value, size_t size) {
  set_has_key();
  if (key_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    key_ = new ::std::string;
  }
  key_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo.Key)
}
inline ::std::string* AuthenticateByTrustedServiceKeyInfo::mutable_key() {
  set_has_key();
  if (key_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    key_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo.Key)
  return key_;
}
inline ::std::string* AuthenticateByTrustedServiceKeyInfo::release_key() {
  clear_has_key();
  if (key_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = key_;
    key_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AuthenticateByTrustedServiceKeyInfo::set_allocated_key(::std::string* key) {
  if (key_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete key_;
  }
  if (key) {
    set_has_key();
    key_ = key;
  } else {
    clear_has_key();
    key_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo.Key)
}

// required string Id = 2;
inline bool AuthenticateByTrustedServiceKeyInfo::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AuthenticateByTrustedServiceKeyInfo::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AuthenticateByTrustedServiceKeyInfo::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AuthenticateByTrustedServiceKeyInfo::clear_id() {
  if (id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    id_->clear();
  }
  clear_has_id();
}
inline const ::std::string& AuthenticateByTrustedServiceKeyInfo::id() const {
  // @@protoc_insertion_point(field_get:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo.Id)
  return *id_;
}
inline void AuthenticateByTrustedServiceKeyInfo::set_id(const ::std::string& value) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    id_ = new ::std::string;
  }
  id_->assign(value);
  // @@protoc_insertion_point(field_set:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo.Id)
}
inline void AuthenticateByTrustedServiceKeyInfo::set_id(const char* value) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    id_ = new ::std::string;
  }
  id_->assign(value);
  // @@protoc_insertion_point(field_set_char:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo.Id)
}
inline void AuthenticateByTrustedServiceKeyInfo::set_id(const char* value, size_t size) {
  set_has_id();
  if (id_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    id_ = new ::std::string;
  }
  id_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo.Id)
}
inline ::std::string* AuthenticateByTrustedServiceKeyInfo::mutable_id() {
  set_has_id();
  if (id_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    id_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo.Id)
  return id_;
}
inline ::std::string* AuthenticateByTrustedServiceKeyInfo::release_id() {
  clear_has_id();
  if (id_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = id_;
    id_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AuthenticateByTrustedServiceKeyInfo::set_allocated_id(::std::string* id) {
  if (id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete id_;
  }
  if (id) {
    set_has_id();
    id_ = id;
  } else {
    clear_has_id();
    id_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo.Id)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Auth
}  // namespace Proto
}  // namespace Api
}  // namespace Diadoc

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Auth_2fAuthenticateByTrustedServiceKeyInfo_2eproto__INCLUDED
