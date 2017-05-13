#include "stdafx.h"
#include "PackInterface.h"

PFNCreatePackObject CPackInterface::pfn_createpackobject = nullptr;
PFNCreateLoadObject CPackInterface::pfn_createloadobject = nullptr;



bool CPackInterface::init()
{
	HMODULE h = LoadLibraryA("EdpPatch.dll");
	if (h)
	{
		pfn_createpackobject = (PFNCreatePackObject)GetProcAddress(h, "CreatePackObject");
		pfn_createloadobject = (PFNCreateLoadObject)GetProcAddress(h, "CreateLoadObject");
		assert(pfn_createpackobject != nullptr);
		assert(pfn_createloadobject != nullptr);
	}
	else
	{
		vrvlog::SPD_LOG_CRITICAL("EdpPatch.dll load failed ({0}), exit", GetLastError());
		return false;
	}

	return true;
}


IPackIndex * CPackInterface::getPackIndexObject()
{
	IPackIndex *p = nullptr;
	if (pfn_createpackobject)
		p = pfn_createpackobject();
	assert(p);
	return p;
}


void CPackInterface::FreePackIndexObject(IPackIndex* object)
{
	if (object)
		object->Release();
}

ILoadIndex * CPackInterface::getLoadIndexObject()
{
	ILoadIndex *p = nullptr;
	if (pfn_createloadobject)
		p = pfn_createloadobject();
	assert(p);
	return p;
}

void CPackInterface::FreeLoadIndexObject(ILoadIndex *object)
{
	if (object)
		object->Release();
}