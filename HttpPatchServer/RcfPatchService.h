#pragma once

#include "RCF\\RCF.hpp"
#include <string>

#include <RCF/Idl.hpp>
#include <SF/vector.hpp>


RCF_BEGIN(IRcfPatch, "IRcfPatch")
RCF_METHOD_V2(void, DownloadFiles, std::string, RCF::FileDownload)
RCF_END(IRcfPatch);
