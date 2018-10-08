// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Auth/AuthenticateByLoginInfo.proto

#ifndef PROTOBUF_Auth_2fAuthenticateByLoginInfo_2eproto__INCLUDED
#define PROTOBUF_Auth_2fAuthenticateByLoginInfo_2eproto__INCLUDED

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
#include "Auth/AuthenticateByTrustedServiceKeyInfo.pb.h"
// @@protoc_insertion_point(includes)

namespace Diadoc {
namespace Api {
namespace Proto {
namespace Auth {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Auth_2fAuthenticateByLoginInfo_2eproto();
void protobuf_AssignDesc_Auth_2fAuthenticateByLoginInfo_2eproto();
void protobuf_ShutdownFile_Auth_2fAuthenticateByLoginInfo_2eproto();

class AuthenticateByLoginInfo;

// ===================================================================

class AuthenticateByLoginInfo : public ::google::protobuf::Message {
 public:
  AuthenticateByLoginInfo();
  virtual ~AuthenticateByLoginInfo();

  AuthenticateByLoginInfo(const AuthenticateByLoginInfo& from);

  inline AuthenticateByLoginInfo& operator=(const AuthenticateByLoginInfo& from) {
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
  static const AuthenticateByLoginInfo& default_instance();

  void Swap(AuthenticateByLoginInfo* other);

  // implements Message ----------------------------------------------

  AuthenticateByLoginInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AuthenticateByLoginInfo& from);
  void MergeFrom(const AuthenticateByLoginInfo& from);
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

  // required string Login = 1;
  inline bool has_login() const;
  inline void clear_login();
  static const int kLoginFieldNumber = 1;
  inline const ::std::string& login() const;
  inline void set_login(const ::std::string& value);
  inline void set_login(const char* value);
  inline void set_login(const char* value, size_t size);
  inline ::std::string* mutable_login();
  inline ::std::string* release_login();
  inline void set_allocated_login(::std::string* login);

  // required string Password = 2;
  inline bool has_password() const;
  inline void clear_password();
  static const int kPasswordFieldNumber = 2;
  inline const ::std::string& password() const;
  inline void set_password(const ::std::string& value);
  inline void set_password(const char* value);
  inline void set_password(const char* value, size_t size);
  inline ::std::string* mutable_password();
  inline ::std::string* release_password();
  inline void set_allocated_password(::std::string* password);

  // optional .Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo TrustedServiceKeyInfo = 3;
  inline bool has_trustedservicekeyinfo() const;
  inline void clear_trustedservicekeyinfo();
  static const int kTrustedServiceKeyInfoFieldNumber = 3;
  inline const ::Diadoc::Api::Proto::Auth::AuthenticateByTrustedServiceKeyInfo& trustedservicekeyinfo() const;
  inline ::Diadoc::Api::Proto::Auth::AuthenticateByTrustedServiceKeyInfo* mutable_trustedservicekeyinfo();
  inline ::Diadoc::Api::Proto::Auth::AuthenticateByTrustedServiceKeyInfo* release_trustedservicekeyinfo();
  inline void set_allocated_trustedservicekeyinfo(::Diadoc::Api::Proto::Auth::AuthenticateByTrustedServiceKeyInfo* trustedservicekeyinfo);

  // @@protoc_insertion_point(class_scope:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo)
 private:
  inline void set_has_login();
  inline void clear_has_login();
  inline void set_has_password();
  inline void clear_has_password();
  inline void set_has_trustedservicekeyinfo();
  inline void clear_has_trustedservicekeyinfo();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* login_;
  ::std::string* password_;
  ::Diadoc::Api::Proto::Auth::AuthenticateByTrustedServiceKeyInfo* trustedservicekeyinfo_;
  friend void  protobuf_AddDesc_Auth_2fAuthenticateByLoginInfo_2eproto();
  friend void protobuf_AssignDesc_Auth_2fAuthenticateByLoginInfo_2eproto();
  friend void protobuf_ShutdownFile_Auth_2fAuthenticateByLoginInfo_2eproto();

  void InitAsDefaultInstance();
  static AuthenticateByLoginInfo* default_instance_;
};
// ===================================================================


// ===================================================================

// AuthenticateByLoginInfo

// required string Login = 1;
inline bool AuthenticateByLoginInfo::has_login() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AuthenticateByLoginInfo::set_has_login() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AuthenticateByLoginInfo::clear_has_login() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AuthenticateByLoginInfo::clear_login() {
  if (login_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    login_->clear();
  }
  clear_has_login();
}
inline const ::std::string& AuthenticateByLoginInfo::login() const {
  // @@protoc_insertion_point(field_get:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo.Login)
  return *login_;
}
inline void AuthenticateByLoginInfo::set_login(const ::std::string& value) {
  set_has_login();
  if (login_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    login_ = new ::std::string;
  }
  login_->assign(value);
  // @@protoc_insertion_point(field_set:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo.Login)
}
inline void AuthenticateByLoginInfo::set_login(const char* value) {
  set_has_login();
  if (login_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    login_ = new ::std::string;
  }
  login_->assign(value);
  // @@protoc_insertion_point(field_set_char:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo.Login)
}
inline void AuthenticateByLoginInfo::set_login(const char* value, size_t size) {
  set_has_login();
  if (login_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    login_ = new ::std::string;
  }
  login_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo.Login)
}
inline ::std::string* AuthenticateByLoginInfo::mutable_login() {
  set_has_login();
  if (login_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    login_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo.Login)
  return login_;
}
inline ::std::string* AuthenticateByLoginInfo::release_login() {
  clear_has_login();
  if (login_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = login_;
    login_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AuthenticateByLoginInfo::set_allocated_login(::std::string* login) {
  if (login_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete login_;
  }
  if (login) {
    set_has_login();
    login_ = login;
  } else {
    clear_has_login();
    login_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo.Login)
}

// required string Password = 2;
inline bool AuthenticateByLoginInfo::has_password() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AuthenticateByLoginInfo::set_has_password() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AuthenticateByLoginInfo::clear_has_password() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AuthenticateByLoginInfo::clear_password() {
  if (password_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    password_->clear();
  }
  clear_has_password();
}
inline const ::std::string& AuthenticateByLoginInfo::password() const {
  // @@protoc_insertion_point(field_get:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo.Password)
  return *password_;
}
inline void AuthenticateByLoginInfo::set_password(const ::std::string& value) {
  set_has_password();
  if (password_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    password_ = new ::std::string;
  }
  password_->assign(value);
  // @@protoc_insertion_point(field_set:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo.Password)
}
inline void AuthenticateByLoginInfo::set_password(const char* value) {
  set_has_password();
  if (password_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    password_ = new ::std::string;
  }
  password_->assign(value);
  // @@protoc_insertion_point(field_set_char:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo.Password)
}
inline void AuthenticateByLoginInfo::set_password(const char* value, size_t size) {
  set_has_password();
  if (password_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    password_ = new ::std::string;
  }
  password_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo.Password)
}
inline ::std::string* AuthenticateByLoginInfo::mutable_password() {
  set_has_password();
  if (password_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    password_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo.Password)
  return password_;
}
inline ::std::string* AuthenticateByLoginInfo::release_password() {
  clear_has_password();
  if (password_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = password_;
    password_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AuthenticateByLoginInfo::set_allocated_password(::std::string* password) {
  if (password_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete password_;
  }
  if (password) {
    set_has_password();
    password_ = password;
  } else {
    clear_has_password();
    password_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo.Password)
}

// optional .Diadoc.Api.Proto.Auth.AuthenticateByTrustedServiceKeyInfo TrustedServiceKeyInfo = 3;
inline bool AuthenticateByLoginInfo::has_trustedservicekeyinfo() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void AuthenticateByLoginInfo::set_has_trustedservicekeyinfo() {
  _has_bits_[0] |= 0x00000004u;
}
inline void AuthenticateByLoginInfo::clear_has_trustedservicekeyinfo() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void AuthenticateByLoginInfo::clear_trustedservicekeyinfo() {
  if (trustedservicekeyinfo_ != NULL) trustedservicekeyinfo_->::Diadoc::Api::Proto::Auth::AuthenticateByTrustedServiceKeyInfo::Clear();
  clear_has_trustedservicekeyinfo();
}
inline const ::Diadoc::Api::Proto::Auth::AuthenticateByTrustedServiceKeyInfo& AuthenticateByLoginInfo::trustedservicekeyinfo() const {
  // @@protoc_insertion_point(field_get:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo.TrustedServiceKeyInfo)
  return trustedservicekeyinfo_ != NULL ? *trustedservicekeyinfo_ : *default_instance_->trustedservicekeyinfo_;
}
inline ::Diadoc::Api::Proto::Auth::AuthenticateByTrustedServiceKeyInfo* AuthenticateByLoginInfo::mutable_trustedservicekeyinfo() {
  set_has_trustedservicekeyinfo();
  if (trustedservicekeyinfo_ == NULL) trustedservicekeyinfo_ = new ::Diadoc::Api::Proto::Auth::AuthenticateByTrustedServiceKeyInfo;
  // @@protoc_insertion_point(field_mutable:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo.TrustedServiceKeyInfo)
  return trustedservicekeyinfo_;
}
inline ::Diadoc::Api::Proto::Auth::AuthenticateByTrustedServiceKeyInfo* AuthenticateByLoginInfo::release_trustedservicekeyinfo() {
  clear_has_trustedservicekeyinfo();
  ::Diadoc::Api::Proto::Auth::AuthenticateByTrustedServiceKeyInfo* temp = trustedservicekeyinfo_;
  trustedservicekeyinfo_ = NULL;
  return temp;
}
inline void AuthenticateByLoginInfo::set_allocated_trustedservicekeyinfo(::Diadoc::Api::Proto::Auth::AuthenticateByTrustedServiceKeyInfo* trustedservicekeyinfo) {
  delete trustedservicekeyinfo_;
  trustedservicekeyinfo_ = trustedservicekeyinfo;
  if (trustedservicekeyinfo) {
    set_has_trustedservicekeyinfo();
  } else {
    clear_has_trustedservicekeyinfo();
  }
  // @@protoc_insertion_point(field_set_allocated:Diadoc.Api.Proto.Auth.AuthenticateByLoginInfo.TrustedServiceKeyInfo)
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

#endif  // PROTOBUF_Auth_2fAuthenticateByLoginInfo_2eproto__INCLUDED