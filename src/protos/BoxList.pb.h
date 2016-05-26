// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: BoxList.proto

#ifndef PROTOBUF_BoxList_2eproto__INCLUDED
#define PROTOBUF_BoxList_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace Diadoc {
namespace Api {
namespace Proto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_BoxList_2eproto();
void protobuf_AssignDesc_BoxList_2eproto();
void protobuf_ShutdownFile_BoxList_2eproto();

class BoxList;
class BoxInfo;
class OrgInfo;

// ===================================================================

class BoxList : public ::google::protobuf::Message {
 public:
  BoxList();
  virtual ~BoxList();
  
  BoxList(const BoxList& from);
  
  inline BoxList& operator=(const BoxList& from) {
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
  static const BoxList& default_instance();
  
  void Swap(BoxList* other);
  
  // implements Message ----------------------------------------------
  
  BoxList* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BoxList& from);
  void MergeFrom(const BoxList& from);
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
  
  // repeated .Diadoc.Api.Proto.BoxInfo Boxes = 1;
  inline int boxes_size() const;
  inline void clear_boxes();
  static const int kBoxesFieldNumber = 1;
  inline const ::Diadoc::Api::Proto::BoxInfo& boxes(int index) const;
  inline ::Diadoc::Api::Proto::BoxInfo* mutable_boxes(int index);
  inline ::Diadoc::Api::Proto::BoxInfo* add_boxes();
  inline const ::google::protobuf::RepeatedPtrField< ::Diadoc::Api::Proto::BoxInfo >&
      boxes() const;
  inline ::google::protobuf::RepeatedPtrField< ::Diadoc::Api::Proto::BoxInfo >*
      mutable_boxes();
  
  // @@protoc_insertion_point(class_scope:Diadoc.Api.Proto.BoxList)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::Diadoc::Api::Proto::BoxInfo > boxes_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_BoxList_2eproto();
  friend void protobuf_AssignDesc_BoxList_2eproto();
  friend void protobuf_ShutdownFile_BoxList_2eproto();
  
  void InitAsDefaultInstance();
  static BoxList* default_instance_;
};
// -------------------------------------------------------------------

class BoxInfo : public ::google::protobuf::Message {
 public:
  BoxInfo();
  virtual ~BoxInfo();
  
  BoxInfo(const BoxInfo& from);
  
  inline BoxInfo& operator=(const BoxInfo& from) {
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
  static const BoxInfo& default_instance();
  
  void Swap(BoxInfo* other);
  
  // implements Message ----------------------------------------------
  
  BoxInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BoxInfo& from);
  void MergeFrom(const BoxInfo& from);
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
  
  // required string BoxId = 1;
  inline bool has_boxid() const;
  inline void clear_boxid();
  static const int kBoxIdFieldNumber = 1;
  inline const ::std::string& boxid() const;
  inline void set_boxid(const ::std::string& value);
  inline void set_boxid(const char* value);
  inline void set_boxid(const char* value, size_t size);
  inline ::std::string* mutable_boxid();
  inline ::std::string* release_boxid();
  
  // required string BoxName = 2;
  inline bool has_boxname() const;
  inline void clear_boxname();
  static const int kBoxNameFieldNumber = 2;
  inline const ::std::string& boxname() const;
  inline void set_boxname(const ::std::string& value);
  inline void set_boxname(const char* value);
  inline void set_boxname(const char* value, size_t size);
  inline ::std::string* mutable_boxname();
  inline ::std::string* release_boxname();
  
  // required .Diadoc.Api.Proto.OrgInfo Org = 3;
  inline bool has_org() const;
  inline void clear_org();
  static const int kOrgFieldNumber = 3;
  inline const ::Diadoc::Api::Proto::OrgInfo& org() const;
  inline ::Diadoc::Api::Proto::OrgInfo* mutable_org();
  inline ::Diadoc::Api::Proto::OrgInfo* release_org();
  
  // @@protoc_insertion_point(class_scope:Diadoc.Api.Proto.BoxInfo)
 private:
  inline void set_has_boxid();
  inline void clear_has_boxid();
  inline void set_has_boxname();
  inline void clear_has_boxname();
  inline void set_has_org();
  inline void clear_has_org();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* boxid_;
  ::std::string* boxname_;
  ::Diadoc::Api::Proto::OrgInfo* org_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_BoxList_2eproto();
  friend void protobuf_AssignDesc_BoxList_2eproto();
  friend void protobuf_ShutdownFile_BoxList_2eproto();
  
  void InitAsDefaultInstance();
  static BoxInfo* default_instance_;
};
// -------------------------------------------------------------------

class OrgInfo : public ::google::protobuf::Message {
 public:
  OrgInfo();
  virtual ~OrgInfo();
  
  OrgInfo(const OrgInfo& from);
  
  inline OrgInfo& operator=(const OrgInfo& from) {
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
  static const OrgInfo& default_instance();
  
  void Swap(OrgInfo* other);
  
  // implements Message ----------------------------------------------
  
  OrgInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const OrgInfo& from);
  void MergeFrom(const OrgInfo& from);
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
  
  // required string Name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  
  // required string Inn = 2;
  inline bool has_inn() const;
  inline void clear_inn();
  static const int kInnFieldNumber = 2;
  inline const ::std::string& inn() const;
  inline void set_inn(const ::std::string& value);
  inline void set_inn(const char* value);
  inline void set_inn(const char* value, size_t size);
  inline ::std::string* mutable_inn();
  inline ::std::string* release_inn();
  
  // required string Kpp = 3;
  inline bool has_kpp() const;
  inline void clear_kpp();
  static const int kKppFieldNumber = 3;
  inline const ::std::string& kpp() const;
  inline void set_kpp(const ::std::string& value);
  inline void set_kpp(const char* value);
  inline void set_kpp(const char* value, size_t size);
  inline ::std::string* mutable_kpp();
  inline ::std::string* release_kpp();
  
  // @@protoc_insertion_point(class_scope:Diadoc.Api.Proto.OrgInfo)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_inn();
  inline void clear_has_inn();
  inline void set_has_kpp();
  inline void clear_has_kpp();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* name_;
  ::std::string* inn_;
  ::std::string* kpp_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_BoxList_2eproto();
  friend void protobuf_AssignDesc_BoxList_2eproto();
  friend void protobuf_ShutdownFile_BoxList_2eproto();
  
  void InitAsDefaultInstance();
  static OrgInfo* default_instance_;
};
// ===================================================================


// ===================================================================

// BoxList

// repeated .Diadoc.Api.Proto.BoxInfo Boxes = 1;
inline int BoxList::boxes_size() const {
  return boxes_.size();
}
inline void BoxList::clear_boxes() {
  boxes_.Clear();
}
inline const ::Diadoc::Api::Proto::BoxInfo& BoxList::boxes(int index) const {
  return boxes_.Get(index);
}
inline ::Diadoc::Api::Proto::BoxInfo* BoxList::mutable_boxes(int index) {
  return boxes_.Mutable(index);
}
inline ::Diadoc::Api::Proto::BoxInfo* BoxList::add_boxes() {
  return boxes_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Diadoc::Api::Proto::BoxInfo >&
BoxList::boxes() const {
  return boxes_;
}
inline ::google::protobuf::RepeatedPtrField< ::Diadoc::Api::Proto::BoxInfo >*
BoxList::mutable_boxes() {
  return &boxes_;
}

// -------------------------------------------------------------------

// BoxInfo

// required string BoxId = 1;
inline bool BoxInfo::has_boxid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BoxInfo::set_has_boxid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BoxInfo::clear_has_boxid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BoxInfo::clear_boxid() {
  if (boxid_ != &::google::protobuf::internal::kEmptyString) {
    boxid_->clear();
  }
  clear_has_boxid();
}
inline const ::std::string& BoxInfo::boxid() const {
  return *boxid_;
}
inline void BoxInfo::set_boxid(const ::std::string& value) {
  set_has_boxid();
  if (boxid_ == &::google::protobuf::internal::kEmptyString) {
    boxid_ = new ::std::string;
  }
  boxid_->assign(value);
}
inline void BoxInfo::set_boxid(const char* value) {
  set_has_boxid();
  if (boxid_ == &::google::protobuf::internal::kEmptyString) {
    boxid_ = new ::std::string;
  }
  boxid_->assign(value);
}
inline void BoxInfo::set_boxid(const char* value, size_t size) {
  set_has_boxid();
  if (boxid_ == &::google::protobuf::internal::kEmptyString) {
    boxid_ = new ::std::string;
  }
  boxid_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BoxInfo::mutable_boxid() {
  set_has_boxid();
  if (boxid_ == &::google::protobuf::internal::kEmptyString) {
    boxid_ = new ::std::string;
  }
  return boxid_;
}
inline ::std::string* BoxInfo::release_boxid() {
  clear_has_boxid();
  if (boxid_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = boxid_;
    boxid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required string BoxName = 2;
inline bool BoxInfo::has_boxname() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BoxInfo::set_has_boxname() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BoxInfo::clear_has_boxname() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BoxInfo::clear_boxname() {
  if (boxname_ != &::google::protobuf::internal::kEmptyString) {
    boxname_->clear();
  }
  clear_has_boxname();
}
inline const ::std::string& BoxInfo::boxname() const {
  return *boxname_;
}
inline void BoxInfo::set_boxname(const ::std::string& value) {
  set_has_boxname();
  if (boxname_ == &::google::protobuf::internal::kEmptyString) {
    boxname_ = new ::std::string;
  }
  boxname_->assign(value);
}
inline void BoxInfo::set_boxname(const char* value) {
  set_has_boxname();
  if (boxname_ == &::google::protobuf::internal::kEmptyString) {
    boxname_ = new ::std::string;
  }
  boxname_->assign(value);
}
inline void BoxInfo::set_boxname(const char* value, size_t size) {
  set_has_boxname();
  if (boxname_ == &::google::protobuf::internal::kEmptyString) {
    boxname_ = new ::std::string;
  }
  boxname_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BoxInfo::mutable_boxname() {
  set_has_boxname();
  if (boxname_ == &::google::protobuf::internal::kEmptyString) {
    boxname_ = new ::std::string;
  }
  return boxname_;
}
inline ::std::string* BoxInfo::release_boxname() {
  clear_has_boxname();
  if (boxname_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = boxname_;
    boxname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required .Diadoc.Api.Proto.OrgInfo Org = 3;
inline bool BoxInfo::has_org() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void BoxInfo::set_has_org() {
  _has_bits_[0] |= 0x00000004u;
}
inline void BoxInfo::clear_has_org() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void BoxInfo::clear_org() {
  if (org_ != NULL) org_->::Diadoc::Api::Proto::OrgInfo::Clear();
  clear_has_org();
}
inline const ::Diadoc::Api::Proto::OrgInfo& BoxInfo::org() const {
  return org_ != NULL ? *org_ : *default_instance_->org_;
}
inline ::Diadoc::Api::Proto::OrgInfo* BoxInfo::mutable_org() {
  set_has_org();
  if (org_ == NULL) org_ = new ::Diadoc::Api::Proto::OrgInfo;
  return org_;
}
inline ::Diadoc::Api::Proto::OrgInfo* BoxInfo::release_org() {
  clear_has_org();
  ::Diadoc::Api::Proto::OrgInfo* temp = org_;
  org_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// OrgInfo

// required string Name = 1;
inline bool OrgInfo::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void OrgInfo::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void OrgInfo::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void OrgInfo::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& OrgInfo::name() const {
  return *name_;
}
inline void OrgInfo::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void OrgInfo::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void OrgInfo::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* OrgInfo::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* OrgInfo::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required string Inn = 2;
inline bool OrgInfo::has_inn() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void OrgInfo::set_has_inn() {
  _has_bits_[0] |= 0x00000002u;
}
inline void OrgInfo::clear_has_inn() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void OrgInfo::clear_inn() {
  if (inn_ != &::google::protobuf::internal::kEmptyString) {
    inn_->clear();
  }
  clear_has_inn();
}
inline const ::std::string& OrgInfo::inn() const {
  return *inn_;
}
inline void OrgInfo::set_inn(const ::std::string& value) {
  set_has_inn();
  if (inn_ == &::google::protobuf::internal::kEmptyString) {
    inn_ = new ::std::string;
  }
  inn_->assign(value);
}
inline void OrgInfo::set_inn(const char* value) {
  set_has_inn();
  if (inn_ == &::google::protobuf::internal::kEmptyString) {
    inn_ = new ::std::string;
  }
  inn_->assign(value);
}
inline void OrgInfo::set_inn(const char* value, size_t size) {
  set_has_inn();
  if (inn_ == &::google::protobuf::internal::kEmptyString) {
    inn_ = new ::std::string;
  }
  inn_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* OrgInfo::mutable_inn() {
  set_has_inn();
  if (inn_ == &::google::protobuf::internal::kEmptyString) {
    inn_ = new ::std::string;
  }
  return inn_;
}
inline ::std::string* OrgInfo::release_inn() {
  clear_has_inn();
  if (inn_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = inn_;
    inn_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required string Kpp = 3;
inline bool OrgInfo::has_kpp() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void OrgInfo::set_has_kpp() {
  _has_bits_[0] |= 0x00000004u;
}
inline void OrgInfo::clear_has_kpp() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void OrgInfo::clear_kpp() {
  if (kpp_ != &::google::protobuf::internal::kEmptyString) {
    kpp_->clear();
  }
  clear_has_kpp();
}
inline const ::std::string& OrgInfo::kpp() const {
  return *kpp_;
}
inline void OrgInfo::set_kpp(const ::std::string& value) {
  set_has_kpp();
  if (kpp_ == &::google::protobuf::internal::kEmptyString) {
    kpp_ = new ::std::string;
  }
  kpp_->assign(value);
}
inline void OrgInfo::set_kpp(const char* value) {
  set_has_kpp();
  if (kpp_ == &::google::protobuf::internal::kEmptyString) {
    kpp_ = new ::std::string;
  }
  kpp_->assign(value);
}
inline void OrgInfo::set_kpp(const char* value, size_t size) {
  set_has_kpp();
  if (kpp_ == &::google::protobuf::internal::kEmptyString) {
    kpp_ = new ::std::string;
  }
  kpp_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* OrgInfo::mutable_kpp() {
  set_has_kpp();
  if (kpp_ == &::google::protobuf::internal::kEmptyString) {
    kpp_ = new ::std::string;
  }
  return kpp_;
}
inline ::std::string* OrgInfo::release_kpp() {
  clear_has_kpp();
  if (kpp_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = kpp_;
    kpp_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}


// @@protoc_insertion_point(namespace_scope)

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

#endif  // PROTOBUF_BoxList_2eproto__INCLUDED