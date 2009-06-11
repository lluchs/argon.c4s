/* Brennbare Könige */

#strict 2

protected func Activate(int iPlr) {
	MessageWindow(GetDesc(), iPlr);
	return 1;
}

#appendto KING

protected func Initialize() {
	var pFlam = CreateObject(DFLM);
	pFlam -> SetAction("Idle");
	AddEffect("IntKingBurner", pFlam, 1, 30, 0, _KBN, this);
	return _inherited(...);
}
