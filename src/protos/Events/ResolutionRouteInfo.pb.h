// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Events/ResolutionRouteInfo.proto

#ifndef PROTOBUF_Events_2fResolutionRouteInfo_2eproto__INCLUDED
#define PROTOBUF_Events_2fResolutionRouteInfo_2eproto__INCLUDED

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
namespace Events {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Events_2fResolutionRouteInfo_2eproto();
void protobuf_AssignDesc_Events_2fResolutionRouteInfo_2eproto();
void protobuf_ShutdownFile_Events_2fResolutionRouteInfo_2eproto();

class ResolutionRouteAssignmentInfo;
class ResolutionRouteRemovalInfo;

// ===================================================================

class ResolutionRouteAssignmentInfo : public ::google::protobuf::Message {
 public:
  ResolutionRouteAssignmentInfo();
  virtual ~ResolutionRouteAssignmentInfo();

  ResolutionRouteAssignmentInfo(const ResolutionRouteAssignmentInfo& from);

  inline ResolutionRouteAssignmentInfo& operator=(const ResolutionRouteAssignmentInfo& from) {
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
  static const ResolutionRouteAssignmentInfo& default_instance();

  void Swap(ResolutionRouteAssignmentInfo* other);

  // implements Message ----------------------------------------------

  ResolutionRouteAssignmentInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ResolutionRouteAssignmentInfo& from);
  void MergeFrom(const ResolutionRouteAssignmentInfo& from);
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

  // required string RouteId = 1;
  inline bool has_routeid() const;
  inline void clear_routeid();
  static const int kRouteIdFieldNumber = 1;
  inline const ::std::string& routeid() const;
  inline void set_routeid(const ::std::string& value);
  inline void set_routeid(const char* value);
  inline void set_routeid(const char* value, size_t size);
  inline ::std::string* mutable_routeid();
  inline ::std::string* release_routeid();
  inline void set_allocated_routeid(::std::string* routeid);

  // required string Author = 2;
  inline bool has_author() const;
  inline void clear_author();
  static const int kAuthorFieldNumber = 2;
  inline const ::std::string& author() const;
  inline void set_author(const ::std::string& value);
  inline void set_author(const char* value);
  inline void set_author(const char* value, size_t size);
  inline ::std::string* mutable_author();
  inline ::std::string* release_author();
  inline void set_allocated_author(::std::string* author);

  // @@protoc_insertion_point(class_scope:Diadoc.Api.Proto.Events.ResolutionRouteAssignmentInfo)
 private:
  inline void set_has_routeid();
  inline void clear_has_routeid();
  inline void set_has_author();
  inline void clear_has_author();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* routeid_;
  ::std::string* author_;
  friend void  protobuf_AddDesc_Events_2fResolutionRouteInfo_2eproto();
  friend void protobuf_AssignDesc_Events_2fResolutionRouteInfo_2eproto();
  friend void protobuf_ShutdownFile_Events_2fResolutionRouteInfo_2eproto();

  void InitAsDefaultInstance();
  static ResolutionRouteAssignmentInfo* default_instance_;
};
// -------------------------------------------------------------------

class ResolutionRouteRemovalInfo : public ::google::protobuf::Message {
 public:
  ResolutionRouteRemovalInfo();
  virtual ~ResolutionRouteRemovalInfo();

  ResolutionRouteRemovalInfo(const ResolutionRouteRemovalInfo& from);

  inline ResolutionRouteRemovalInfo& operator=(const ResolutionRouteRemovalInfo& from) {
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
  static const ResolutionRouteRemovalInfo& default_instance();

  void Swap(ResolutionRouteRemovalInfo* other);

  // implements Message ----------------------------------------------

  ResolutionRouteRemovalInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ResolutionRouteRemovalInfo& from);
  void MergeFrom(const ResolutionRouteRemovalInfo& from);
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

  // required string RouteId = 1;
  inline bool has_routeid() const;
  inline void clear_routeid();
  static const int kRouteIdFieldNumber = 1;
  inline const ::std::string& routeid() const;
  inline void set_routeid(const ::std::string& value);
  inline void set_routeid(const char* value);
  inline void set_routeid(const char* value, size_t size);
  inline ::std::string* mutable_routeid();
  inline ::std::string* release_routeid();
  inline void set_allocated_routeid(::std::string* routeid);

  // required string Author = 2;
  inline bool has_author() const;
  inline void clear_author();
  static const int kAuthorFieldNumber = 2;
  inline const ::std::string& author() const;
  inline void set_author(const ::std::string& value);
  inline void set_author(const char* value);
  inline void set_author(const char* value, size_t size);
  inline ::std::string* mutable_author();
  inline ::std::string* release_author();
  inline void set_allocated_author(::std::string* author);

  // @@protoc_insertion_point(class_scope:Diadoc.Api.Proto.Events.ResolutionRouteRemovalInfo)
 private:
  inline void set_has_routeid();
  inline void clear_has_routeid();
  inline void set_has_author();
  inline void clear_has_author();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* routeid_;
  ::std::string* author_;
  friend void  protobuf_AddDesc_Events_2fResolutionRouteInfo_2eproto();
  friend void protobuf_AssignDesc_Events_2fResolutionRouteInfo_2eproto();
  friend void protobuf_ShutdownFile_Events_2fResolutionRouteInfo_2eproto();

  void InitAsDefaultInstance();
  static ResolutionRouteRemovalInfo* default_instance_;
};
// ===================================================================


// ===================================================================

// ResolutionRouteAssignmentInfo

// required string RouteId = 1;
inline bool ResolutionRouteAssignmentInfo::has_routeid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ResolutionRouteAssignmentInfo::set_has_routeid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ResolutionRouteAssignmentInfo::clear_has_routeid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ResolutionRouteAssignmentInfo::clear_routeid() {
  if (routeid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    routeid_->clear();
  }
  clear_has_routeid();
}
inline const ::std::string& ResolutionRouteAssignmentInfo::routeid() const {
  // @@protoc_insertion_point(field_get:Diadoc.Api.Proto.Events.ResolutionRouteAssignmentInfo.RouteId)
  return *routeid_;
}
inline void ResolutionRouteAssignmentInfo::set_routeid(const ::std::string& value) {
  set_has_routeid();
  if (routeid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    routeid_ = new ::std::string;
  }
  routeid_->assign(value);
  // @@protoc_insertion_point(field_set:Diadoc.Api.Proto.Events.ResolutionRouteAssignmentInfo.RouteId)
}
inline void ResolutionRouteAssignmentInfo::set_routeid(const char* value) {
  set_has_routeid();
  if (routeid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    routeid_ = new ::std::string;
  }
  routeid_->assign(value);
  // @@protoc_insertion_point(field_set_char:Diadoc.Api.Proto.Events.ResolutionRouteAssignmentInfo.RouteId)
}
inline void ResolutionRouteAssignmentInfo::set_routeid(const char* value, size_t size) {
  set_has_routeid();
  if (routeid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    routeid_ = new ::std::string;
  }
  routeid_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Diadoc.Api.Proto.Events.ResolutionRouteAssignmentInfo.RouteId)
}
inline ::std::string* ResolutionRouteAssignmentInfo::mutable_routeid() {
  set_has_routeid();
  if (routeid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    routeid_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:Diadoc.Api.Proto.Events.ResolutionRouteAssignmentInfo.RouteId)
  return routeid_;
}
inline ::std::string* ResolutionRouteAssignmentInfo::release_routeid() {
  clear_has_routeid();
  if (routeid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = routeid_;
    routeid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void ResolutionRouteAssignmentInfo::set_allocated_routeid(::std::string* routeid) {
  if (routeid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete routeid_;
  }
  if (routeid) {
    set_has_routeid();
    routeid_ = routeid;
  } else {
    clear_has_routeid();
    routeid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:Diadoc.Api.Proto.Events.ResolutionRouteAssignmentInfo.RouteId)
}

// required string Author = 2;
inline bool ResolutionRouteAssignmentInfo::has_author() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ResolutionRouteAssignmentInfo::set_has_author() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ResolutionRouteAssignmentInfo::clear_has_author() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ResolutionRouteAssignmentInfo::clear_author() {
  if (author_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    author_->clear();
  }
  clear_has_author();
}
inline const ::std::string& ResolutionRouteAssignmentInfo::author() const {
  // @@protoc_insertion_point(field_get:Diadoc.Api.Proto.Events.ResolutionRouteAssignmentInfo.Author)
  return *author_;
}
inline void ResolutionRouteAssignmentInfo::set_author(const ::std::string& value) {
  set_has_author();
  if (author_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    author_ = new ::std::string;
  }
  author_->assign(value);
  // @@protoc_insertion_point(field_set:Diadoc.Api.Proto.Events.ResolutionRouteAssignmentInfo.Author)
}
inline void ResolutionRouteAssignmentInfo::set_author(const char* value) {
  set_has_author();
  if (author_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    author_ = new ::std::string;
  }
  author_->assign(value);
  // @@protoc_insertion_point(field_set_char:Diadoc.Api.Proto.Events.ResolutionRouteAssignmentInfo.Author)
}
inline void ResolutionRouteAssignmentInfo::set_author(const char* value, size_t size) {
  set_has_author();
  if (author_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    author_ = new ::std::string;
  }
  author_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Diadoc.Api.Proto.Events.ResolutionRouteAssignmentInfo.Author)
}
inline ::std::string* ResolutionRouteAssignmentInfo::mutable_author() {
  set_has_author();
  if (author_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    author_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:Diadoc.Api.Proto.Events.ResolutionRouteAssignmentInfo.Author)
  return author_;
}
inline ::std::string* ResolutionRouteAssignmentInfo::release_author() {
  clear_has_author();
  if (author_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = author_;
    author_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void ResolutionRouteAssignmentInfo::set_allocated_author(::std::string* author) {
  if (author_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete author_;
  }
  if (author) {
    set_has_author();
    author_ = author;
  } else {
    clear_has_author();
    author_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:Diadoc.Api.Proto.Events.ResolutionRouteAssignmentInfo.Author)
}

// -------------------------------------------------------------------

// ResolutionRouteRemovalInfo

// required string RouteId = 1;
inline bool ResolutionRouteRemovalInfo::has_routeid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ResolutionRouteRemovalInfo::set_has_routeid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ResolutionRouteRemovalInfo::clear_has_routeid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ResolutionRouteRemovalInfo::clear_routeid() {
  if (routeid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    routeid_->clear();
  }
  clear_has_routeid();
}
inline const ::std::string& ResolutionRouteRemovalInfo::routeid() const {
  // @@protoc_insertion_point(field_get:Diadoc.Api.Proto.Events.ResolutionRouteRemovalInfo.RouteId)
  return *routeid_;
}
inline void ResolutionRouteRemovalInfo::set_routeid(const ::std::string& value) {
  set_has_routeid();
  if (routeid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    routeid_ = new ::std::string;
  }
  routeid_->assign(value);
  // @@protoc_insertion_point(field_set:Diadoc.Api.Proto.Events.ResolutionRouteRemovalInfo.RouteId)
}
inline void ResolutionRouteRemovalInfo::set_routeid(const char* value) {
  set_has_routeid();
  if (routeid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    routeid_ = new ::std::string;
  }
  routeid_->assign(value);
  // @@protoc_insertion_point(field_set_char:Diadoc.Api.Proto.Events.ResolutionRouteRemovalInfo.RouteId)
}
inline void ResolutionRouteRemovalInfo::set_routeid(const char* value, size_t size) {
  set_has_routeid();
  if (routeid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    routeid_ = new ::std::string;
  }
  routeid_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Diadoc.Api.Proto.Events.ResolutionRouteRemovalInfo.RouteId)
}
inline ::std::string* ResolutionRouteRemovalInfo::mutable_routeid() {
  set_has_routeid();
  if (routeid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    routeid_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:Diadoc.Api.Proto.Events.ResolutionRouteRemovalInfo.RouteId)
  return routeid_;
}
inline ::std::string* ResolutionRouteRemovalInfo::release_routeid() {
  clear_has_routeid();
  if (routeid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = routeid_;
    routeid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void ResolutionRouteRemovalInfo::set_allocated_routeid(::std::string* routeid) {
  if (routeid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete routeid_;
  }
  if (routeid) {
    set_has_routeid();
    routeid_ = routeid;
  } else {
    clear_has_routeid();
    routeid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:Diadoc.Api.Proto.Events.ResolutionRouteRemovalInfo.RouteId)
}

// required string Author = 2;
inline bool ResolutionRouteRemovalInfo::has_author() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ResolutionRouteRemovalInfo::set_has_author() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ResolutionRouteRemovalInfo::clear_has_author() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ResolutionRouteRemovalInfo::clear_author() {
  if (author_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    author_->clear();
  }
  clear_has_author();
}
inline const ::std::string& ResolutionRouteRemovalInfo::author() const {
  // @@protoc_insertion_point(field_get:Diadoc.Api.Proto.Events.ResolutionRouteRemovalInfo.Author)
  return *author_;
}
inline void ResolutionRouteRemovalInfo::set_author(const ::std::string& value) {
  set_has_author();
  if (author_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    author_ = new ::std::string;
  }
  author_->assign(value);
  // @@protoc_insertion_point(field_set:Diadoc.Api.Proto.Events.ResolutionRouteRemovalInfo.Author)
}
inline void ResolutionRouteRemovalInfo::set_author(const char* value) {
  set_has_author();
  if (author_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    author_ = new ::std::string;
  }
  author_->assign(value);
  // @@protoc_insertion_point(field_set_char:Diadoc.Api.Proto.Events.ResolutionRouteRemovalInfo.Author)
}
inline void ResolutionRouteRemovalInfo::set_author(const char* value, size_t size) {
  set_has_author();
  if (author_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    author_ = new ::std::string;
  }
  author_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:Diadoc.Api.Proto.Events.ResolutionRouteRemovalInfo.Author)
}
inline ::std::string* ResolutionRouteRemovalInfo::mutable_author() {
  set_has_author();
  if (author_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    author_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:Diadoc.Api.Proto.Events.ResolutionRouteRemovalInfo.Author)
  return author_;
}
inline ::std::string* ResolutionRouteRemovalInfo::release_author() {
  clear_has_author();
  if (author_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = author_;
    author_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void ResolutionRouteRemovalInfo::set_allocated_author(::std::string* author) {
  if (author_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete author_;
  }
  if (author) {
    set_has_author();
    author_ = author;
  } else {
    clear_has_author();
    author_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:Diadoc.Api.Proto.Events.ResolutionRouteRemovalInfo.Author)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Events
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

#endif  // PROTOBUF_Events_2fResolutionRouteInfo_2eproto__INCLUDED