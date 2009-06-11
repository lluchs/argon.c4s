#strict 2

/* Meteoritenhagel: 20 Sek. Abklingzeit */
#appendto MMTR
public func CooldownTime() { return 700; }

/* Gravitation: 10 Sek. Abklingzeit */
//#appendto MGDW
//#appendto MGUP
//public func CooldownTime() { return(350); }

/* Feuerfaust: 5 Sek. Abklingzeit */
#appendto FRFS
public func CooldownTime() { return 175; }

/* Feuerball: 7 Sek. Abklingzeit */
#appendto MFRB
public func CooldownTime() { return 245; }

/* Der Feuerball benotigt keine Abklingzeit, wenn der Zauber abgebrochen worden ist. */
public func AbortAiming(object pCaller) {
	pCaller -> RemoveCooldown(GetID());
	return _inherited(pCaller, ...);
}
 
#appendto WC7U

/* Waffengang: 5 Sek. Abklingzeit */

public func CooldownTime() { return 175; }
