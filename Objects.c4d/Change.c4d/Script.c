/*-- Change --*/

#strict 2

local iNumber, pClonk;

public func SetNum(int iNum) {
	iNumber = iNum;
}

public func SetClonk(object pObj) {
	pClonk = pObj;
}

protected func CrewSelection(bool fDeselect, bool fCursorOnly) {
	//Log("%v %v", fDeselect, fCursorOnly);
	if(!fDeselect) {
		if(!fCursorOnly) {
			if(!iNumber) // ..damit nur einmal aufgerufen wird
				pClonk -> ~ChangeMiddle();
		}
		else if(iNumber == 0)
			pClonk -> ~ChangeLeft();
		else if(iNumber == 1)
			pClonk -> ~ChangeRight();
		UnselectCrew(GetOwner());
		SetCursor(GetOwner(), pClonk, true, true);
	}
}
