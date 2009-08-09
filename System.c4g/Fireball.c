/*-- Feuerball --*/

#strict 2

#appendto FIRB

protected func Initialize() {
	inherited(...);
	var iEffectNumber = GetEffect("FireballFlight", this);
	if(!iEffectNumber)
		return;
	EffectVar(1, this, iEffectNumber) = 60;
	return 1;
}

public func SetSizeBoost(int iTo) {
	if(!iTo)
		iTo = (15 + Random(11)) * 6;
	else
		// damit der Flintkombo was bringt
		iTo += iTo / 2;
	return inherited(iTo, ...);
}
