/*-- Kombosystem f�r K�nige �ndern --*/

#strict 2

protected func Activate(int iByPlayer) {
	var pByObject = GetCursor(iByPlayer);
	if(!(pByObject -> ~ContextCombo(pByObject)))
		MessageWindow(GetDesc(), iByPlayer);
	return 1;
}
