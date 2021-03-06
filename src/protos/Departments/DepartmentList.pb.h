// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Departments/DepartmentList.proto

#ifndef PROTOBUF_Departments_2fDepartmentList_2eproto__INCLUDED
#define PROTOBUF_Departments_2fDepartmentList_2eproto__INCLUDED

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
#include "Departments/Department.pb.h"
// @@protoc_insertion_point(includes)

namespace Diadoc {
namespace Api {
namespace Proto {
namespace Departments {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_Departments_2fDepartmentList_2eproto();
void protobuf_AssignDesc_Departments_2fDepartmentList_2eproto();
void protobuf_ShutdownFile_Departments_2fDepartmentList_2eproto();

class DepartmentList;

// ===================================================================

class DepartmentList : public ::google::protobuf::Message {
 public:
  DepartmentList();
  virtual ~DepartmentList();

  DepartmentList(const DepartmentList& from);

  inline DepartmentList& operator=(const DepartmentList& from) {
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
  static const DepartmentList& default_instance();

  void Swap(DepartmentList* other);

  // implements Message ----------------------------------------------

  DepartmentList* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DepartmentList& from);
  void MergeFrom(const DepartmentList& from);
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

  // repeated .Diadoc.Api.Proto.Departments.Department Departments = 1;
  inline int departments_size() const;
  inline void clear_departments();
  static const int kDepartmentsFieldNumber = 1;
  inline const ::Diadoc::Api::Proto::Departments::Department& departments(int index) const;
  inline ::Diadoc::Api::Proto::Departments::Department* mutable_departments(int index);
  inline ::Diadoc::Api::Proto::Departments::Department* add_departments();
  inline const ::google::protobuf::RepeatedPtrField< ::Diadoc::Api::Proto::Departments::Department >&
      departments() const;
  inline ::google::protobuf::RepeatedPtrField< ::Diadoc::Api::Proto::Departments::Department >*
      mutable_departments();

  // required int32 TotalCount = 2;
  inline bool has_totalcount() const;
  inline void clear_totalcount();
  static const int kTotalCountFieldNumber = 2;
  inline ::google::protobuf::int32 totalcount() const;
  inline void set_totalcount(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Diadoc.Api.Proto.Departments.DepartmentList)
 private:
  inline void set_has_totalcount();
  inline void clear_has_totalcount();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::Diadoc::Api::Proto::Departments::Department > departments_;
  ::google::protobuf::int32 totalcount_;
  friend void  protobuf_AddDesc_Departments_2fDepartmentList_2eproto();
  friend void protobuf_AssignDesc_Departments_2fDepartmentList_2eproto();
  friend void protobuf_ShutdownFile_Departments_2fDepartmentList_2eproto();

  void InitAsDefaultInstance();
  static DepartmentList* default_instance_;
};
// ===================================================================


// ===================================================================

// DepartmentList

// repeated .Diadoc.Api.Proto.Departments.Department Departments = 1;
inline int DepartmentList::departments_size() const {
  return departments_.size();
}
inline void DepartmentList::clear_departments() {
  departments_.Clear();
}
inline const ::Diadoc::Api::Proto::Departments::Department& DepartmentList::departments(int index) const {
  // @@protoc_insertion_point(field_get:Diadoc.Api.Proto.Departments.DepartmentList.Departments)
  return departments_.Get(index);
}
inline ::Diadoc::Api::Proto::Departments::Department* DepartmentList::mutable_departments(int index) {
  // @@protoc_insertion_point(field_mutable:Diadoc.Api.Proto.Departments.DepartmentList.Departments)
  return departments_.Mutable(index);
}
inline ::Diadoc::Api::Proto::Departments::Department* DepartmentList::add_departments() {
  // @@protoc_insertion_point(field_add:Diadoc.Api.Proto.Departments.DepartmentList.Departments)
  return departments_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Diadoc::Api::Proto::Departments::Department >&
DepartmentList::departments() const {
  // @@protoc_insertion_point(field_list:Diadoc.Api.Proto.Departments.DepartmentList.Departments)
  return departments_;
}
inline ::google::protobuf::RepeatedPtrField< ::Diadoc::Api::Proto::Departments::Department >*
DepartmentList::mutable_departments() {
  // @@protoc_insertion_point(field_mutable_list:Diadoc.Api.Proto.Departments.DepartmentList.Departments)
  return &departments_;
}

// required int32 TotalCount = 2;
inline bool DepartmentList::has_totalcount() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void DepartmentList::set_has_totalcount() {
  _has_bits_[0] |= 0x00000002u;
}
inline void DepartmentList::clear_has_totalcount() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void DepartmentList::clear_totalcount() {
  totalcount_ = 0;
  clear_has_totalcount();
}
inline ::google::protobuf::int32 DepartmentList::totalcount() const {
  // @@protoc_insertion_point(field_get:Diadoc.Api.Proto.Departments.DepartmentList.TotalCount)
  return totalcount_;
}
inline void DepartmentList::set_totalcount(::google::protobuf::int32 value) {
  set_has_totalcount();
  totalcount_ = value;
  // @@protoc_insertion_point(field_set:Diadoc.Api.Proto.Departments.DepartmentList.TotalCount)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Departments
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

#endif  // PROTOBUF_Departments_2fDepartmentList_2eproto__INCLUDED
