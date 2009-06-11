/*-- Ausgrauung für das Kombosystem --*/

#strict 2

#appendto MGSM

local fOverlayGraphic;

protected func RecheckSymbol() { // Ausgrauung im Kombosystem
	_inherited(...);
	if(fOverlayGraphic || !(pMagician -> GetCooldown(idThisSpell)))
		return 1;
	SetGraphics(0, this, idThisSpell, 2, GFXOV_MODE_IngamePicture);
	SetClrModulation(RGB(100, 100, 100), this, 2);
	//SetObjectBlitMode(GFX_BLIT_Additive, this, 2);
	SetClrModulation(1, this, GFX_Overlay);
	SetObjectBlitMode(GFX_BLIT_Mod2, this, GFX_Overlay);
	return 1;
}

private func SetGraphics(string szGfxName, object pObj, id idSrcDef, int iOverlay) {
	if(iOverlay == 2) {
		if(!idSrcDef)
			fOverlayGraphic = 0;
		else
			fOverlayGraphic = 1;
	}
	return inherited(szGfxName, pObj, idSrcDef, iOverlay, ...);
}

