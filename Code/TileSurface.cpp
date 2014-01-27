#include "TileSurface.h"


TileSurface::TileSurface(int a_iTileId, Tmpl8::Surface* a_pTileSurface)
{
	m_iTileId = a_iTileId;
	m_pTileSurface = a_pTileSurface;
}


TileSurface::~TileSurface(void)
{
}


bool TileSurface::CompareSurfaces(Tmpl8::Surface* a_pOther)
{
	short pixelsOff = 0;
	for(int i = 0; i < a_pOther->GetWidth() * a_pOther->GetHeight(); i+=4)
	{
		Tmpl8::Pixel* otherPixel = a_pOther->GetBuffer() + i;
		Tmpl8::Pixel* ownPixel = m_pTileSurface->GetBuffer() + i;
		
		if(*ownPixel == *otherPixel)
		{
			continue;
		}
		else
		{
			return true;
		}
	}
	return false;
}