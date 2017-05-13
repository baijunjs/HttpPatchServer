
#ifndef CRC_H_
#define CRC_H_

void InitCRC (DWORD *lpCRC);
DWORD CRC32 (DWORD dwCRC, 
			 LPBYTE lpAddr, 
			 DWORD dwSize,
			 DWORD *lpCRC);

DWORD GetFileCrc(const char * pszFilePath);

#endif