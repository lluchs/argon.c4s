/*-- Cooldown --*/

#strict 2

#appendto MCLK
#appendto KING

/* Überladungen für Zauberclonk, Magier und König */

private func AddMenuItem(string szCaption, string szCommand, id idItem, object pMenuObject, int iCount, int iParameter, string szInfoCaption, int iExtra, XPar1) {
	if(GetMenu() == MCMS && szCommand == "DoMagic" && GetCooldown(idItem)) {
		iExtra = 4;
		XPar1 = CreateObject(idItem);
		XPar1 -> SetClrModulation(RGB(100, 100, 100));
	}
	var fReturn = inherited(szCaption, szCommand, idItem, pMenuObject, iCount, iParameter, szInfoCaption, iExtra, XPar1);
	if(XPar1)
		RemoveObject(XPar1);
	return fReturn;
}

protected func DoMagic(id idSpell) {
	if(GetCooldown(idSpell)) {
		Sound("Error", 0, this, 0, GetOwner() + 1);
		return;
	}
	return _inherited(idSpell, ...);
}

private func ExecMagic(id idSpell) {
	var fReturn = _inherited(idSpell, ...);
	if(fReturn)
		CreateCooldown(idSpell);
	return fReturn;
}

