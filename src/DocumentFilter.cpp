#include "StdAfx.h"
#include "DocumentFilter.h"

DocumentFilter::DocumentFilter(const std::wstring& boxId, const std::wstring& filterCategory)
	: BoxId(boxId)
	, FilterCategory(filterCategory)
	, TimestampFrom(NULL)
	, TimestampTo(NULL)
	, ExcludeSubdepartments(false)
{}

DocumentFilter::~DocumentFilter(void)
{
}
