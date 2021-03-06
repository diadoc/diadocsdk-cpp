// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Documents/DocumentsMoveOperation.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Documents/DocumentsMoveOperation.pb.h"

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
namespace Documents {

namespace {

const ::google::protobuf::Descriptor* DocumentsMoveOperation_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  DocumentsMoveOperation_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_Documents_2fDocumentsMoveOperation_2eproto() {
  protobuf_AddDesc_Documents_2fDocumentsMoveOperation_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Documents/DocumentsMoveOperation.proto");
  GOOGLE_CHECK(file != NULL);
  DocumentsMoveOperation_descriptor_ = file->message_type(0);
  static const int DocumentsMoveOperation_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DocumentsMoveOperation, boxid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DocumentsMoveOperation, todepartmentid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DocumentsMoveOperation, documentids_),
  };
  DocumentsMoveOperation_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      DocumentsMoveOperation_descriptor_,
      DocumentsMoveOperation::default_instance_,
      DocumentsMoveOperation_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DocumentsMoveOperation, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DocumentsMoveOperation, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(DocumentsMoveOperation));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Documents_2fDocumentsMoveOperation_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    DocumentsMoveOperation_descriptor_, &DocumentsMoveOperation::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Documents_2fDocumentsMoveOperation_2eproto() {
  delete DocumentsMoveOperation::default_instance_;
  delete DocumentsMoveOperation_reflection_;
}

void protobuf_AddDesc_Documents_2fDocumentsMoveOperation_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::Diadoc::Api::Proto::protobuf_AddDesc_DocumentId_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n&Documents/DocumentsMoveOperation.proto"
    "\022\032Diadoc.Api.Proto.Documents\032\020DocumentId"
    ".proto\"r\n\026DocumentsMoveOperation\022\r\n\005BoxI"
    "d\030\001 \002(\t\022\026\n\016ToDepartmentId\030\002 \001(\t\0221\n\013Docum"
    "entIds\030\003 \003(\0132\034.Diadoc.Api.Proto.Document"
    "Id", 202);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Documents/DocumentsMoveOperation.proto", &protobuf_RegisterTypes);
  DocumentsMoveOperation::default_instance_ = new DocumentsMoveOperation();
  DocumentsMoveOperation::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Documents_2fDocumentsMoveOperation_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Documents_2fDocumentsMoveOperation_2eproto {
  StaticDescriptorInitializer_Documents_2fDocumentsMoveOperation_2eproto() {
    protobuf_AddDesc_Documents_2fDocumentsMoveOperation_2eproto();
  }
} static_descriptor_initializer_Documents_2fDocumentsMoveOperation_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int DocumentsMoveOperation::kBoxIdFieldNumber;
const int DocumentsMoveOperation::kToDepartmentIdFieldNumber;
const int DocumentsMoveOperation::kDocumentIdsFieldNumber;
#endif  // !_MSC_VER

DocumentsMoveOperation::DocumentsMoveOperation()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Diadoc.Api.Proto.Documents.DocumentsMoveOperation)
}

void DocumentsMoveOperation::InitAsDefaultInstance() {
}

DocumentsMoveOperation::DocumentsMoveOperation(const DocumentsMoveOperation& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Diadoc.Api.Proto.Documents.DocumentsMoveOperation)
}

void DocumentsMoveOperation::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  boxid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  todepartmentid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

DocumentsMoveOperation::~DocumentsMoveOperation() {
  // @@protoc_insertion_point(destructor:Diadoc.Api.Proto.Documents.DocumentsMoveOperation)
  SharedDtor();
}

void DocumentsMoveOperation::SharedDtor() {
  if (boxid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete boxid_;
  }
  if (todepartmentid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete todepartmentid_;
  }
  if (this != default_instance_) {
  }
}

void DocumentsMoveOperation::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* DocumentsMoveOperation::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return DocumentsMoveOperation_descriptor_;
}

const DocumentsMoveOperation& DocumentsMoveOperation::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Documents_2fDocumentsMoveOperation_2eproto();
  return *default_instance_;
}

DocumentsMoveOperation* DocumentsMoveOperation::default_instance_ = NULL;

DocumentsMoveOperation* DocumentsMoveOperation::New() const {
  return new DocumentsMoveOperation;
}

void DocumentsMoveOperation::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    if (has_boxid()) {
      if (boxid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        boxid_->clear();
      }
    }
    if (has_todepartmentid()) {
      if (todepartmentid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        todepartmentid_->clear();
      }
    }
  }
  documentids_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool DocumentsMoveOperation::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Diadoc.Api.Proto.Documents.DocumentsMoveOperation)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string BoxId = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_boxid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->boxid().data(), this->boxid().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "boxid");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_ToDepartmentId;
        break;
      }

      // optional string ToDepartmentId = 2;
      case 2: {
        if (tag == 18) {
         parse_ToDepartmentId:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_todepartmentid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->todepartmentid().data(), this->todepartmentid().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "todepartmentid");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_DocumentIds;
        break;
      }

      // repeated .Diadoc.Api.Proto.DocumentId DocumentIds = 3;
      case 3: {
        if (tag == 26) {
         parse_DocumentIds:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_documentids()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_DocumentIds;
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
  // @@protoc_insertion_point(parse_success:Diadoc.Api.Proto.Documents.DocumentsMoveOperation)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Diadoc.Api.Proto.Documents.DocumentsMoveOperation)
  return false;
#undef DO_
}

void DocumentsMoveOperation::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Diadoc.Api.Proto.Documents.DocumentsMoveOperation)
  // required string BoxId = 1;
  if (has_boxid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->boxid().data(), this->boxid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "boxid");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->boxid(), output);
  }

  // optional string ToDepartmentId = 2;
  if (has_todepartmentid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->todepartmentid().data(), this->todepartmentid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "todepartmentid");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->todepartmentid(), output);
  }

  // repeated .Diadoc.Api.Proto.DocumentId DocumentIds = 3;
  for (int i = 0; i < this->documentids_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->documentids(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Diadoc.Api.Proto.Documents.DocumentsMoveOperation)
}

::google::protobuf::uint8* DocumentsMoveOperation::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Diadoc.Api.Proto.Documents.DocumentsMoveOperation)
  // required string BoxId = 1;
  if (has_boxid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->boxid().data(), this->boxid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "boxid");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->boxid(), target);
  }

  // optional string ToDepartmentId = 2;
  if (has_todepartmentid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->todepartmentid().data(), this->todepartmentid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "todepartmentid");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->todepartmentid(), target);
  }

  // repeated .Diadoc.Api.Proto.DocumentId DocumentIds = 3;
  for (int i = 0; i < this->documentids_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->documentids(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Diadoc.Api.Proto.Documents.DocumentsMoveOperation)
  return target;
}

int DocumentsMoveOperation::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string BoxId = 1;
    if (has_boxid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->boxid());
    }

    // optional string ToDepartmentId = 2;
    if (has_todepartmentid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->todepartmentid());
    }

  }
  // repeated .Diadoc.Api.Proto.DocumentId DocumentIds = 3;
  total_size += 1 * this->documentids_size();
  for (int i = 0; i < this->documentids_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->documentids(i));
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

void DocumentsMoveOperation::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const DocumentsMoveOperation* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const DocumentsMoveOperation*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void DocumentsMoveOperation::MergeFrom(const DocumentsMoveOperation& from) {
  GOOGLE_CHECK_NE(&from, this);
  documentids_.MergeFrom(from.documentids_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_boxid()) {
      set_boxid(from.boxid());
    }
    if (from.has_todepartmentid()) {
      set_todepartmentid(from.todepartmentid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void DocumentsMoveOperation::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void DocumentsMoveOperation::CopyFrom(const DocumentsMoveOperation& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DocumentsMoveOperation::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->documentids())) return false;
  return true;
}

void DocumentsMoveOperation::Swap(DocumentsMoveOperation* other) {
  if (other != this) {
    std::swap(boxid_, other->boxid_);
    std::swap(todepartmentid_, other->todepartmentid_);
    documentids_.Swap(&other->documentids_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata DocumentsMoveOperation::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = DocumentsMoveOperation_descriptor_;
  metadata.reflection = DocumentsMoveOperation_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Documents
}  // namespace Proto
}  // namespace Api
}  // namespace Diadoc

// @@protoc_insertion_point(global_scope)
