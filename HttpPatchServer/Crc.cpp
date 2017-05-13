
#include "stdafx.h"
#include "Crc.h"

DWORD CRCTab [1024];
void InitCRC (DWORD *lpCRC)
{
	if (!lpCRC) lpCRC = CRCTab;
	int I,J;
	DWORD C;
	for (I=0; I<1024; I++)
	{
		for (C=I, J=0; J<8; J++)
		{
			C = (C & 1) ? (C>>1)^0xEDB88320L : (C>>1);
		}

		lpCRC[I] = C;
	}
}

DWORD CRC32 (DWORD dwCRC, 
			 LPBYTE lpAddr, 
			 DWORD dwSize,
			 DWORD *lpCRC)
{
	if (!lpAddr) return dwCRC;
	if (!lpCRC) lpCRC = CRCTab;
	for (DWORD I=0; I<dwSize; I++)
	{
		dwCRC = lpCRC[(BYTE)dwCRC ^ lpAddr[I] ] ^ (dwCRC >> 8);
	}
	return (dwCRC);
} 

DWORD GetFileCrc(const char * pszFilePath)
{
	DWORD dwCrc = 0;
	
	InitCRC(CRCTab);
	
	DWORD dwMaximumSizeHigh, dwMaximumSizeLow;
	HANDLE hFile = CreateFileA(pszFilePath,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE) return 0;
	dwMaximumSizeLow = GetFileSize(hFile, &dwMaximumSizeHigh);
	HANDLE hMapView = CreateFileMappingA(hFile,
		NULL,
		PAGE_READONLY,
		dwMaximumSizeHigh,
		dwMaximumSizeLow,
		NULL);
	if (hMapView == NULL)
	{
		CloseHandle(hFile);
		return 0;
	}

	LPVOID pz = MapViewOfFile(hMapView,
		FILE_MAP_READ,
		0,
		0,
		0);
	if (pz == NULL)
	{
		CloseHandle(hFile);
		CloseHandle(hMapView);
		return 0;
	}


	dwCrc = CRC32(0,(LPBYTE)pz,dwMaximumSizeLow,CRCTab);
	
	UnmapViewOfFile(pz);
	CloseHandle(hMapView);
	CloseHandle(hFile);

#ifdef _DEBUG
	FILE* _fp = NULL;
	fopen_s(&_fp, pszFilePath, "rb");
	if (_fp)
	{
		fseek(_fp, 0, SEEK_END);
		long len = ftell(_fp);
		fseek(_fp, 0, SEEK_SET);
		char* buf = (char*)malloc(len);
		memset(buf, 0, len);
		size_t i = fread(buf, 1, len, _fp);
		DWORD dw = CRC32(0, (LPBYTE)buf, len, CRCTab);
		free(buf);
		fclose(_fp);
	}
#endif
	return dwCrc;
}
