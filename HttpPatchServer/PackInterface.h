#pragma once
class CPackInterface
{
public:
	static bool init();
	static IPackIndex *getPackIndexObject();
	static void FreePackIndexObject(IPackIndex*);
	static ILoadIndex *getLoadIndexObject();
	static void FreeLoadIndexObject(ILoadIndex *);
private:
	static PFNCreatePackObject pfn_createpackobject;
	static PFNCreateLoadObject pfn_createloadobject;
};
