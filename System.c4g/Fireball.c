/*-- Feuerball --*/

#strict 2

#appendto FIRB

protected func Initialize() {
	inherited(...);
	var iEffectNumber = GetEffect("FireballFlight", this);
	if(!iEffectNumber)
		return;
	EffectVar(5, this, iEffectNumber) = (10 + Random(10)) * 6;
	EffectVar(1, this, iEffectNumber) = 50;
	return 1;
}

public func SetSizeBoost(int iTo) { // damit der Flintkombo was bringt
	iTo += 3 * 6;
	return inherited(iTo, ...);
}
