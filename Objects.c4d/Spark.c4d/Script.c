/* Funken */

#strict

protected func CreateSpark()
{
 CreateObject(GetID(), Random(LandscapeWidth()), 0, -1)->SetXDir(RandomX(-10,10));
 return(1);
}

protected func Initialize() { return(SetAction("Fall")); }
protected func CheckHit() { if (Stuck() || GetContact(0, -1, CNAT_Bottom)) return(Hit()); }
protected func Hit() { return(SetAction("Sparkle")); }
protected func Removal() { return(RemoveObject()); }

protected func CastObject()
{
 CreateObject(RndObjectID(), 0,0, -1);
 Sound("Boing");
 return(1);
}

protected func RndObjectID()
{
 // Seltene Objekte
 var r = Random(6*3);
 if (!r)   return(XARP); // Sprengpfeilpaket
 if (!--r) return(EFLN); // Teraflint
 if (!--r) return(ZAPN); // Zapnest
 if (!--r) return(BLMP); // Luftschiff
 if (!--r) return(CATA); // Katapult
 if (!--r) return(ARCH); // Zielscheibe

 // Normale Objekte
 var r = Random(17);
 if (!r)   return(SWOR); // Schwert
 if (!--r) return(AXE1); // Axt
 if (!--r) return(SPER); // Speer
 if (!--r) return(BOW1); // Bogen
 if (!--r) return(ARWP); // Pfeilpaket
 if (!--r) return(FARP); // Brandpfeilpaket
 if (!--r) return(TFLN); // T-Flint
 if (!--r) return(STFN); // Super-T-Flint
 if (!--r) return(FLNT); // Feuerstein
 if (!--r) return(SFLN); // Superflint
 if (!--r) return(FBMP); // Brandbombe
 if (!--r) return(CRYS); // Kristall
 if (!--r) return(WBRL); // Wasserfass
 if (!--r) return(COKI); // Keks
 if (!--r) return(BRED); // Brot
 if (!--r) return(SNWB); // Schneeball
 if (!--r) return(BALN); // Ballon
}