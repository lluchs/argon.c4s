/*-- Abklingzeit --*/

#strict 2

/* Funktionen zum Arbeiten mit Abklingzeiten */

global func CreateCooldown(id idSpell) {
	var iTime = idSpell -> ~CooldownTime();
	if(iTime && FindObject2(Find_ID(_CLD)))
		return AddEffect("IntCooldown", this, 300, iTime, 0, 0, idSpell);
	return;
}

global func GetCooldown(id idSpell) {
	var i, iNr;
	while(iNr = GetEffect("IntCooldown", this, i++))
		if (EffectVar(0, this, iNr) == idSpell)
			return iNr;
	return;
}

global func RemoveCooldown(id idSpell) {
	var iNr;
	while(iNr = GetCooldown(idSpell))
		RemoveEffect(0, this, iNr);
	return 1;
}

/* Funktionen für das Abklingzeitsystem */

global func FxIntCooldownStart(object pTarget, int iEffectNumber, int iTemp, id idSpell)	{
	if(!iTemp)
		EffectVar(0, pTarget, iEffectNumber) = idSpell;
	return 1;
}

global func FxIntCooldownStop(object pTarget, int iEffectNumber, int iReason, int iTemp) {
	if(iTemp == 1)
		return;
	// dies hier könnte Probleme mit dem Schnellzaubermenü geben (was mir aber egal ist)
	if(GetMenu(pTarget) == MCMS) {
		CloseMenu(pTarget);
		pTarget -> ~ContextMagic();
	}
	return 1;
}
