#include "SysUtil.h"
#include <memory.h>
#include <malloc.h>
void* SysUtil::SysAllocNZ(unsigned int uSize)
{
	void* pData = malloc(uSize);

	if (pData == NULL)
	{
		//ErrSetErrorCode(ERR_MEMORY);
	}

	return pData;
}

void* SysUtil::SysAlloc(unsigned int uSize)
{
	void* pData =SysUtil::SysAllocNZ(uSize);

	if (pData != nullptr)
		memset(pData, 0, uSize);

	return pData;
}

void SysUtil::SysFree(void* pData)
{
	free(pData);
}

void* SysUtil::SysRealloc(void* pData, unsigned int uSize)
{
	void* pNewData = realloc(pData, uSize);

	if (pNewData == NULL)
	{
		//ErrSetErrorCode(ERR_MEMORY);
	}
	return pNewData;
}