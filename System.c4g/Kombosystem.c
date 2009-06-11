/*-- König -> Kombosystem (Achtung: für eigene Szenarien bitte Version von C2C nehmen) --*/

#strict 2

static const KING_ComboExtraDataName = "KING_PrefCombo";

#appendto KING

protected func ControlSpecial2(object pCaller) {
	if(!_inherited(pCaller, ...))
		return;
	if(!IsComboSystemEnabled())
		return 1;
	// Kombo nach Spieler-Default
	var iCombo = GetKingCombo(GetOwner(pCaller));
	if(!iCombo)
		return 1;
	CloseMenu();
	return CreateSpellMenu(this, this, 0, iCombo == 2);
}

global func GetKingCombo(int iPlr) {
  var iCombo = GetPlrExtraData(iPlr, KING_ComboExtraDataName);
  if(!iCombo)
  	iCombo = GetPlrExtraData(iPlr, MCLK_ComboExtraDataName);
  else
  	if(iCombo == -1)
  		iCombo++;
  return iCombo;
}

public func OnComboMenuEnter(id idSpell) {
	return DoMagic(idSpell);
}

public func OnComboMenuAbort() {
	return;
}

private func ExecMagic(id idSpell) {
	var fReturn = _inherited(idSpell, ...);
	if(fReturn && GetPlrExtraData(GetOwner(), MCLK_ComboExtraDataName))
		PlayerMessage(GetController(), idSpell -> GetName(), this);
	return fReturn;
}

public func CheckMagicRequirements(id idSpell)
{
  // Nicht genug Zauberenergie
  var iNumCast=MCLK_UnlimitedCast, iNumCast2=MCLK_UnlimitedCast;
  if(!(iNumCast = CheckMana(idSpell)))
  {
    return;
  }

  // Nicht genug alchemische Komponenten
  if(ObjectCount(ALCO)) if(!(iNumCast2=CheckAlchem(idSpell,this)))
  {
    return;
  }
  
  // Zaubern OK
  return Min(iNumCast, iNumCast2);
}

public func ContextCombo(pByObject)
{
  [$CtxCombo$|Image=MCMC|Condition=IsComboSystemEnabled]
  // Kombosystem ändern
  var iCombo = GetKingCombo(GetOwner(pByObject));
  iCombo = (iCombo+1) % 3;
  // Meldung und Sound
  if(iCombo)
  {
    var sMsg; if (iCombo == 2) sMsg = "$ChangedToCombo2$"; else sMsg = "$ChangedToCombo$";
    PlayerMessage(GetOwner(),sMsg, this);
    Sound("SpellSysCombo*", 0, 0, 0, GetOwner()+1);
    CreateParticle("NoGravSpark", 0,0,  0,-6, 5*10, RGBa(255,255,0, 0), this);
    CreateParticle("NoGravSpark", 0,0, -5,-3, 5*10, RGBa(255,255,0, 0), this);
    CreateParticle("NoGravSpark", 0,0, -5, 3, 5*10, RGBa(255,255,0, 0), this);
    CreateParticle("NoGravSpark", 0,0,  5,-3, 5*10, RGBa(255,255,0, 0), this);
    CreateParticle("NoGravSpark", 0,0,  5, 3, 5*10, RGBa(255,255,0, 0), this);
    CreateParticle("NoGravSpark", 0,0,  0, 6, 5*10, RGBa(255,255,0, 0), this);
  }
  else
  {
    PlayerMessage(GetOwner(),"$ChangedToMenu$", this);
    Sound("SpellSysMenu*", 0, 0, 0, GetOwner()+1);
    CreateParticle("NoGravSpark", 0,0,  0,-6, 5*10, RGBa(255,0,0, 0), this);
    CreateParticle("NoGravSpark", 0,0, -5,-3, 5*10, RGBa(255,0,0, 0), this);
    CreateParticle("NoGravSpark", 0,0, -5, 3, 5*10, RGBa(255,0,0, 0), this);
    CreateParticle("NoGravSpark", 0,0,  5,-3, 5*10, RGBa(255,0,0, 0), this);
    CreateParticle("NoGravSpark", 0,0,  5, 3, 5*10, RGBa(255,0,0, 0), this);
    CreateParticle("NoGravSpark", 0,0,  0, 6, 5*10, RGBa(255,0,0, 0), this);
  }
 
  // Dies als Default für zukünftige Clonks (und zwar unabhängig vom MCLK)
  if(!iCombo)
  	iCombo = -1;
  SetPlrExtraData(GetController(), KING_ComboExtraDataName, iCombo);
  return 1;
}

public func ContextComboHelp(object pByObject)
{
  [$CtxComboHelp$|Image=CXIN|Condition=ComboOn]
  // Hilfe anzeigen
  MessageWindow("$MsgComboHelp$", GetOwner(pByObject), CXIN, "$CtxComboHelp$");
  return 1;
}

protected func ComboOn() { return GetKingCombo(GetOwner()); }
