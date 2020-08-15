
/*
*	author: zyb
*   \brief CaptureEvent Interface
*/

#include "Common.h"
#include <mmreg.h>

class ICaptureEvent
{
public:
	virtual ~ICaptureEvent(){};

	virtual void OnCaptureStart(DWORD dwInterval) = 0;
	virtual void OnCaptureStop() = 0;
	
	virtual void OnAdjustCaptureFormat(WAVEFORMATEX *pFormat) = 0;
	virtual void OnCaptureData(LPBYTE pData, int iDataLen) = 0;
};