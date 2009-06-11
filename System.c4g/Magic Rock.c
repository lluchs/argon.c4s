#strict 2

#appendto MRCK

public func Exit(object pObj, int iX, int iY, int iR, int iXDir, int iYDir) {
	if((pObj -> Contained()) == this) {
		iXDir = GetXDir() / 10;
		iYDir = GetYDir() / 10;
	}
	return inherited(pObj, iX, iY, iR, iXDir, iYDir, ...);
}

public func Punch(object pObj, int iPunch) {
	if((pObj -> Contained()) == this)
		iPunch /= 2; // halber Schaden
	return inherited(pObj, iPunch, ...);
}
