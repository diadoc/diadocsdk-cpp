#pragma once

struct DocumentFilter
{
	DocumentFilter(const std::wstring& boxId, const std::wstring& filterCategory);
	~DocumentFilter();

	std::wstring BoxId;
	std::wstring FilterCategory;
	std::wstring CounteragentBoxId;
	const __int64* TimestampFrom;
	const __int64* TimestampTo;
	std::wstring FromDocumentDate;
	std::wstring ToDocumentDate;
	std::wstring DepartmentId;
	bool ExcludeSubdepartments;
	std::wstring SortDirection;
	std::string AfterIndexKey;
};
