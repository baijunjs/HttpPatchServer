#ifndef  __VRV_INCLUDE_H__
#define  __VRV_INCLUDE_H__

#ifdef VRV_PCHELP_SLP
#define USE_VRV_SDK_UNIT_DEINFIE
#endif

#ifdef  VRV_SDK_UNIT
#ifndef USE_VRV_SDK_UNIT_DEINFIE
#define USE_VRV_SDK_UNIT_DEINFIE
#endif
#pragma comment(lib,"VrvSdkUnit.lib")
#endif

#ifdef USE_VRV_SDK_UNIT_DEINFIE
//SDK��Ҫ���������ͷ�ļ��Ͷ���
#include "VrvSdkExplort.h"
using namespace VRVSDK;
#endif



#endif