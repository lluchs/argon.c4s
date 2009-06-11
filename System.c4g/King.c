#strict 2
#appendto KING

local aSpells;

/* Schnellzauber Funktion */

public func ControlSpecial2(object pCaller) {
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
  return 1;
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
