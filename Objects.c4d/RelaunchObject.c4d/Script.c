/*-- Relaunchobjekt --*/

#strict

local iPlayer;

private func RelaunchDelay() { return(2*35); } // Relaunch Delay in Frames

protected func Initialize()
{
 SetVisibility(VIS_None());
}

protected func Relaunch(int iPlr)
{
 // Relaunchspieler festlegen
 iPlayer = iPlr;

 // Dieses Objekt relauncht einen Spieler
 SetAction("Wait");

 // Fertig!
 return(1);
}

private func Execute()
{
 // Falls dieses Objekt keinen Inhalt hat, l�schen!
 if (!Contents() || !GetAlive(Contents())) return(RemoveObject());

 // Falls der Spieler wieder mitspielen darf
 if (GetActTime() >= RelaunchDelay())
 {
  // Clonk wieder mitspielen lassen
  GameCall("PlacePlayer", iPlayer, GetX(), GetY());

  // Dieses Hilfsobjekt l�schen
  return(RemoveObject());
 }

 // Fertig!
 return(1);
}

/* Sonstiges */

protected func ContainedDown() { return(1); }	// Keine Ger�usche
protected func ContainedLeft() { return(1); }	// Damit man die aktivieren / nehmen Men�s nicht �ffnen kann
protected func ContainedRight() { return(1); }	// Damit man die aktivieren / nehmen Men�s nicht �ffnen kann
protected func RejectCollect() { return(1); }	// Damit man nichts in das Objekt ablegen kann
