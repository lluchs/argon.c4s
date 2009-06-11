/*-- Waffengang --*/

#strict 2

public func Activate(caster, real_caster)
{
 Sound("Magic*");

 // Zaubernden Clonk ermitteln
 var clonk = caster;
 if (real_caster) clonk = real_caster;
 if (!clonk) return(RemoveObject());

 // Dem Clonk eine zufällig ausgewählte Waffe geben
 var id = RandomWeapon();
 if (FindContents(id, clonk)) id = RandomWeapon();
 return(CreateContents(id, clonk));
}

private func RandomWeapon()
{
 var r = Random(13);
 if (!r)   return SWOR; // Schwert
 if (!--r) return SPER; // Speer
 if (!--r) return BOW1; // Bogen
 if (!--r) return ARWP; // Pfeilpaket
 if (!--r) return FARP; // Brandpfeilpaket
 if (!--r) return XARP; // Sprengpfeilpaket
 if (!--r) return TFLN; // T-Flint
 if (!--r) return STFN; // Super-T-Flint
 if (!--r) return FLNT; // Feuerstein
 if (!--r) return SFLN; // Superflint
 if (!--r) return EFLN; // Teraflint
 if (!--r) return FBMP; // Brandbombe
 if (!--r) return ZAPN; // Zapnest
}

public func GetSpellClass(object pMage) { return FIRE; }
public func GetSpellCombo(pMage) { return "2"; } // (1: Backward; 2: Down; 3: Forward; 4: Throw; 5: Jump; 6: Dig)
