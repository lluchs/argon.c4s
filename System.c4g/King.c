#strict 2
#appendto KING

local aSpells;

public func ChangeMiddle() {
	//Log("ChangeMiddle: %d", FrameCounter());
	if(Contents())
		Contents() -> ~Activate(this);
}

public func ChangeLeft() {
//	Log("ChangeLeft");
	if(GetKingCombo(GetOwner()))
		return;
  // Clonk soll anhalten
  SetComDir(COMD_Stop);
  // Menü öffnen
  OpenEmptySpellMenu(MCMQ, this, this, this, "");
  for(var i=0; i < MaxQuickspells(); ++i)
  {
    var idData = GetPlrExtraData(GetOwner(),Format("%s%d",MCLK_QSPrefix,i));
    if(IsQSID(idData))
      AddMenuItem(Format("$MnuSlotNumber$: %s", i+1, "%s"), "QuickspellEditMenu",idData,0,0,i);
    else
      AddMenuItem(Format("$MnuSlotNumber$: $MnuEmpty$",i+1), "QuickspellEditMenu",MCMX,0,0,i);
  }
  // mittleren Spruch auswählen
  SelectMenuItem(MaxQuickspells()/2);
}

public func ChangeRight() {
//	Log("ChangeRight");
	if(GetAction() == "Dig")
		SetAction("Walk");
	 // Nicht bereit
  if (!ReadyToMagic()) { DoCastError(Format("$MsgNotReadyToMagic$", GetName())); return; }
  
  // Bereits Zaubermenü geöffnet
  if(GetMenu() == MCMS) {
  	CloseMenu();
  	return DoMagic(aSpells[GetMenuSelection()]);
  }
  // Clonk soll anhalten
  SetComDir(COMD_Stop);
  // Menü öffnen
  //OpenSpellMenu(this, this, "$MnuCast$: %s", "DoMagic", GetOwner(), this, "$MnuNoSpells$", idLastSpell);
  var iExtra;
  if(FindDefinition(ALCO) && ObjectCount(ALCO)) { if(FindDefinition(NMGE) && ObjectCount(NMGE)) iExtra=1; else iExtra=5; }
  else                  { if(FindDefinition(NMGE) && ObjectCount(NMGE)) iExtra=0; else iExtra=3; }
  CreateMenu(MCMS, 0, 0, iExtra, "$MnuNoSpells$", GetMagicEnergy());
  aSpells = CreateArray(12); // 12 Zauber atm, Menge aber eigentlich egal
  for(var idSpell, i; idSpell = GetPlrMagic(GetOwner(), 0, i); i++) {
  	aSpells[i] = idSpell;
    AddMenuItem("$MnuCast$: %s", "DoMagic", idSpell);
  }
  SelectMenuItem(iLastSpell);
}

/* Schnellzauber Funktion */

public func ControlSpecial2(object pCaller) {
	if(GetAction() == "Dig")
		SetAction("Walk");
  // Menüsystem: Schnellzauber
  
  // Keine Schnellzauber belegt
  if (!Quickspells()) { DoCastError("$MsgNoQuickSpells$"); return 1; }
  // Nicht bereit
  if (!ReadyToMagic()) { DoCastError(Format("$MsgNotReadyToMagic$", GetName())); return; }
  // Menü öffnen
  OpenEmptySpellMenu(MCMS, this, this, this, "");
  for(var i=0; i < MaxQuickspells(); ++i)
  {
    var idData = GetPlrExtraData(GetOwner(),Format("%s%d",MCLK_QSPrefix,i));
    if(IsQSID(idData))
      AddMenuItem("$MnuSlotQuickspell$: %s", "DoMagic", idData);
    else
      AddMenuItem("$MnuSlotQuickspell$: $MnuEmpty$", "Nothing", MCMX);
  }
  // in die Mitte
  SelectMenuItem(MaxQuickspells()/2);
  return 1;
}

protected func Nothing() { /* Nichts */ }

protected func QuickspellEditMenu(id idSpell, int iSelection) {
  // Clonk soll anhalten
  SetComDir(COMD_Stop);
  // Menü öffnen
  OpenEmptySpellMenu(MCMQ, this, this, this, "$MnuNoSpells$");
  var idMagic, i = 0;
  // "Schnellzauber löschen"
  if ((idSpell != MCM1) && (idSpell != MCM2) && (idSpell != MCM3) && (idSpell != MCM4) && (idSpell != MCM5))
    AddMenuItem(Format("$MnuSlotNumber$: $MnuDelQuickspell$", iSelection+1),"QuickspellDel",MCMX,0,0,iSelection);
  // Alles außer schon ausgewählte anzeigen
  while (idMagic = GetPlrMagic(GetOwner(), 0, i++))
    if(!IsQuickspell(idMagic))
      AddMenuItem(Format("$MnuSlotNumber$: %s", iSelection+1, "%s"), "QuickspellAdd", idMagic,0,0,iSelection);
}

protected func QuickspellAdd(id idSpell, int iSelection) {
  AddQuickspell(idSpell, iSelection);
  ChangeLeft();
}

protected func QuickspellDel(id idSpell, int iSelection) {
  DelQuickspell(idSpell, iSelection);
  ChangeLeft();
}

/* Schnellzauber */

protected func AddQuickspell(id idSpell, int iPos)	// fügt einen Zauber zum Schnellzugriff hinzu
{ SetPlrExtraData(GetOwner(),Format("%s%d",MCLK_QSPrefix,iPos),idSpell); }

protected func DelQuickspell(id idSpell, int iPos)	// löscht einen Zauber aus dem Schnellzugriff
{ SetPlrExtraData(GetOwner(),Format("%s%d",MCLK_QSPrefix,iPos),false); }

private func MaxQuickspells() { return 5; }		// Maximale Anzahl der Zauber im Schnellzugriff

private func Quickspells() {
  for(var i=0; i<MaxQuickspells(); ++i)
    if(IsQSID(GetPlrExtraData(GetOwner(),Format("%s%d",MCLK_QSPrefix,i)) ))
      return(true);
}

private func IsQuickspell(id idSpell)			// der angegebene Zauber ist immo im Schnellzugriff
{
  var idData;
  for(var i=0; IsQSID(idData = GetPlrExtraData(GetOwner(),Format("%s%d",MCLK_QSPrefix,i)) ) && i<MaxQuickspells(); ++i)
    if(idData == idSpell) return(1);
  return(0);
}

private func IsQSID(id idItem) {				// Ist eine geladene ID und als Schnellzauber zulässig
  if(GetType(idItem) != C4V_C4ID) return(false);
  if(!FindDefinition(idItem)) return(false);
  if(!GetPlrMagic(GetOwner(),idItem)) return(false);
  return(true);
}  

private func DoCastError(string sErr)
{
  PlayerMessage(GetController(), sErr,this());
  Sound("Error", 0, this(), 100, GetController()+1);
  return(true);
}

/* Der König hat max. 100 Manapunkte, nicht nur 50 */

public func MagicEnergy() {
	SetPhysical("Magic", 100000, PHYS_Temporary);
	DoMagicEnergy(100, this, true);
	return 1;
}

/* Aus dem Relaunchobjekt oder aus dem Feuerball kann nicht heraus gezaubert werden */

public func ReadyToMagic()
{
 if(Contained() && Contained() -> GetID() == _RLO)
 	return;
 return _inherited(...);
}

/* Im Laufen, Bogenzielen und Reiten können Kristalle umgewandelt werden */

public func IsConvertReady() {
	return GetAction() == "Walk" || GetAction() == "AimBow" || WildcardMatch(GetAction(), "Ride*");
}

/* Nach dem Schließen des Relaunchmenüs geht die Relaunchmessage weg */

protected func MenuQueryCancel() {
	if(GetMenu() == _RLO)
		Message("Relaunches:|%d", 0, iRelaunchesCount);
}
