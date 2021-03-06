#pragma once


#include <string>
#include <vector>

#include <RCF/Idl.hpp>
#include <SF/vector.hpp>
#include <RCF/FileDownload.hpp>
#include "PatchBus.h"


RCF_BEGIN(MyService, "MyService")
RCF_METHOD_R1(bool, RequestPatchInfo, std::vector<vrv::patch::PatchInfo>&)
RCF_METHOD_V1(void, RequestPatchInfo, vrv::patch::PatchInfo&)
RCF_METHOD_V1(void, RequestIndexInfo, std::vector<vrv::patch::IndexInfo>&)
RCF_METHOD_V2(void, DownloadFiles, std::tstring&, RCF::FileDownload&)
RCF_METHOD_V2(void, DownloadIndexFile, std::tstring&, RCF::FileDownload&)
RCF_METHOD_V2(void, DownloadPatchFile, std::tstring&, RCF::FileDownload&)
RCF_METHOD_V1(void, DownloadIndex1xml, RCF::FileDownload&)
RCF_METHOD_R2(int, add, int,int)
RCF_METHOD_R2(BOOL, ReportToServer, std::tstring&, std::tstring &)
RCF_END(MyService)
