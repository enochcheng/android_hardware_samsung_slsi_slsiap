#include <OMX_Component.h>

#define		NX_MAX_COMPONENTS			64
#define		NX_MAX_ROLES				16
#define		NX_MAX_CONCURRENT_COMPS		1

typedef struct NX_COMPONENT_INFO{
	OMX_STRING		strName;
	OMX_STRING		strSoName;
	OMX_U32			nRoles;
	OMX_HANDLETYPE	hModule;
	OMX_STRING		pRoles[NX_MAX_ROLES];
	OMX_HANDLETYPE	handle[NX_MAX_CONCURRENT_COMPS];
	OMX_S32			nRefCount;
	OMX_ERRORTYPE	(*ComponentInit)( OMX_IN OMX_HANDLETYPE hComponent );
}NX_COMPONENT_INFO;

typedef struct NX_COMPONENT_REG_INFO{
	OMX_STRING		CompName;
	OMX_STRING		CompRole;
	OMX_STRING		CompSoName;
	OMX_ERRORTYPE	(*ComponentInit)( OMX_IN OMX_HANDLETYPE hComponent );
}NX_COMPONENT_REG_INFO;
