/*-- Kombosystem für Könige ändern --*/

#strict 2

protected func Activate(int iByPlayer) {
	var pByObject = GetCursor(iByPlayer);
	if(!(pByObject -> ~ContextCombo(pByObject)))
		MessageWindow(GetDesc(), iByPlayer);
	return 1;
}
