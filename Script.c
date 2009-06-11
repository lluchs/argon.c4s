/*-- Argons Ehre --*/

#strict 2

static const KillsPerRelaunchGain = 3;

static	iRelaunchesCount, aRelaunches, aKills,
	fNoRelaunchPlayer;

global func & Relaunches(int iPlr) { return aRelaunches[iPlr]; }
global func & Kills(int iPlr) { return aKills[iPlr]; }

/* Rundeninitialisierung */

protected func Initialize()
{
 // Standard Anzahl der Relaunches: 5
 iRelaunchesCount = 5;
 
 // Array initialisieren
 aRelaunches = CreateArray();
 aKills = CreateArray();

 // Das Spark-Objekt initialisieren
 CreateObject(_SPK, LandscapeWidth()/2 ,-5, -1)->SetAction("Wait");

 // Effekte
 SetGamma(RGB(4,4,7), RGB(146,147,163), RGB(252,254,255) );
 SetSkyParallax(0, 20, 20, 0,0,0,0);
 for(var i; i < 5; ++i) CreateParticle("Fog", Random(LandscapeWidth()), Random(LandscapeHeight()), 0,0, RandomX(1000,1500));

 // Regeln
 if(!ObjectCount(MCMC))
 	CreateObject(MCMC, 0, 0, NO_OWNER);
 // Scriptzähler starten
 ScriptGo(1);
}

/* Zauberenergie */

protected func Script10()
{
 var pObj;

 // Allen Königen neue Zauberenergie geben
 for(pObj in FindObjects(Find_ID(KING)))
   DoMagicEnergy(1, pObj);

 // Vllt noch ein Blitz?
 var r = Random(2);
 if (Random(GetPlayerCount()/2+1))
  if (!Random(2))
   LaunchLightning(Random(LandscapeWidth()), 0, -20, 40, 5, 15, 0);
  else
   LaunchLightning(LandscapeWidth()*(!r), Random(LandscapeHeight()), -20+40*r, 15, -20, 40, 0);

 // Den Scriptzähler zurücksetzen
 goto(0);
}

/* Spieler */

protected func InitializePlayer(int iPlr)
{
 var idDef, i, pKing = GetCrew(iPlr);
 
 // Dem Spieler alle geladenen Zauber (außer dem Zauber "Aufwertung", dieser wird als Menübild benutzt) verfügbar machen
 while (idDef = GetDefinition(i++, C4D_Magic))
  SetPlrMagic(iPlr, idDef);

 // Den Spieler platzieren
 PlacePlayer(iPlr, Random(LandscapeWidth()-20)+10, Random(LandscapeHeight()-100)+50);

 // Dem König volle Zauberenergie geben
 pKing->~MagicEnergy();

 // Dem König die Startobjekte in die Hand geben
 CreateContents(ARWP, pKing);
 CreateContents(BOW1, pKing);

 // Die Anzahl der Relaunches für den Spieler bestimmen
 Relaunches(iPlr) = iRelaunchesCount;
 SetWealth(iPlr, Relaunches(iPlr));

 // Scoreboard initialisieren
 var iPlrID = GetPlayerID(iPlr);

 SetScoreboardData(SBRD_Caption,	SBRD_Caption,	"Relaunches",			SBRD_Caption);
 SetScoreboardData(iPlrID,		SBRD_Caption,	GetTaggedPlayerName(iPlr),	iPlrID);
 var iColID = ScoreboardCol(RLNC);
 SetScoreboardData(SBRD_Caption,	iColID,		"{{_RLO}}",			iColID);

 iColID = ScoreboardCol(KLLS);
 SetScoreboardData(SBRD_Caption,	iColID,		"{{SWOR}}",			iColID);

 // Scoreboard aktualisieren
 UpdateScoreboard(iPlr, false);

 // Die Anzahl der Relaunches wird durch den Host bestimmt
 if (!iPlr)
 {
  // König anhalten
  SetComDir(COMD_Stop, pKing);

  // Menü öffnen
  CreateMenu(_RLO, pKing, pKing, 0, "Relaunches", 0, 1, 1);
  AddMenuItem("+1", "SetRelaunches(+1)", LMM5, pKing);
  AddMenuItem("-1", "SetRelaunches(-1)", LMM1, pKing);

  // Die Anzahl der Relaunches über dem König ausgeben
  Message("@Relaunches:|%d", 0, iRelaunchesCount);
 }
}

global func SetRelaunches(int iChange)
{
 // Nicht weniger als 0 Relaunches
 if (iRelaunchesCount + iChange < 0) return;

 // Die Anzahl der Relaunches verändern
 iRelaunchesCount += iChange;

 // Die Anzahl der Relaunches für die Spieler verändern
 var i = GetPlayerCount();
 while (i--)
 {
  Relaunches(GetPlayerByIndex(i)) += iChange;
  SetWealth(GetPlayerByIndex(i), Relaunches(GetPlayerByIndex(i)));
  UpdateScoreboard(GetPlayerByIndex(i), false);
 }

 // Die Anzahl der Relaunches über dem König ausgeben
 Message("@Relaunches:|%d", 0, iRelaunchesCount);
}

protected func RemovePlayer(iPlr)
{
 // Scoreboard aktualisieren
 var iPlrID = GetPlayerID(iPlr), iColID = ScoreboardCol(RLNC);
 SetScoreboardData(iPlrID,		iColID,		"-",				Relaunches(iPlr));
 SortScoreboard(iColID, true);
}

private func PlacePlayer(int iPlr, int iX, int iY)
{
 var pKing = GetCrew(iPlr);

 // Den König ggf. aus dem Relaunchobjekt holen
 Exit(pKing);

 // Den König zufällig platzieren
 SetPosition(iX, iY, pKing);

 // Eine magische Brücke unter dem König erschaffen
 CreateObject(FBRG, pKing->GetX(), pKing->GetY()+16, iPlr); //SetAction("Field", pKing);
}

protected func OnClonkDeath(object pClonk, int iKilledBy) {
 var iPlr = GetOwner(pClonk);
 // Der Spieler, der den Clonk getötet hat, bekommt einen Kill
 if (iKilledBy != iPlr && GetPlayerName(iKilledBy)) GiveKill(iKilledBy, iPlr);

 // Kein Relaunch für eliminierte Spieler
 if (!GetPlayerName(iPlr) || !Relaunches(iPlr)) {
 	SetPlrView(iPlr, pClonk);
 	return EliminatePlayer(iPlr);
 }

 // Dem Spieler einen neuen König erschaffen
 var pKing = CreateObject(KING, 0, 0, iPlr);
 GrabObjectInfo(pClonk, pKing);
 MakeCrewMember(pKing, iPlr);
 SetCursor(iPlr, pKing, true);
 DoEnergy(100 - GetEnergy(pKing), pKing);

 // Dem König volle Zauberenergie geben
 pKing->~MagicEnergy();

 // Dem König die Startobjekte in die Hand geben
 CreateContents(ARWP, pKing);
 CreateContents(BOW1, pKing);

 // Den Clonk in ein Relaunchobjekt stecken.
 var pRelaunchObj = CreateObject(_RLO, Random(LandscapeWidth()-20)+10, Random(LandscapeHeight()-100)+50, iPlr);
 Enter(pRelaunchObj, pKing);
 pRelaunchObj->Relaunch(iPlr);

 // Dem Spieler ein Relaunch abziehen
 Relaunches(iPlr)--;
 SetWealth(iPlr, Relaunches(iPlr));

 // Scoreboard für das Opfer aktualisieren
 UpdateScoreboard(iPlr, true);

 // Verkünden
 if (iKilledBy != iPlr && GetPlayerName(iKilledBy))
 {
  if (!Relaunches(iPlr))
   Log("$MsgNoRelaunchesLeft$", GetPlayerName(iPlr), GetPlayerName(iKilledBy));
  else
   Log("$MsgXRelaunchesLeft$", GetPlayerName(iPlr), GetPlayerName(iKilledBy), Relaunches(iPlr), iRelaunchesCount);
 }
 else
 {
  if (!Relaunches(iPlr))
   Log("$MsgNoRelaunchesLeftNoKiller$", GetPlayerName(iPlr));
  else
   Log("$MsgXRelaunchesLeftNoKiller$", GetPlayerName(iPlr), Relaunches(iPlr), iRelaunchesCount);
 }
 Sound("Trumpet");
}

private func GiveKill(int iKiller, int iVictim)
{
 // Der Spieler bekommt einen Kill
 Kills(iKiller)++;

 // Genug Kills für einen Bonus-Relaunch? / keine Relaunches?
 if (!(Kills(iKiller) % KillsPerRelaunchGain) || !Relaunches(iKiller))
 {
  Relaunches(iKiller)++;
  SetWealth(iKiller, Relaunches(iKiller));
 }

 // Scoreboard für den Mörder aktualisieren
 UpdateScoreboard(iKiller, false);

 // Bonusmaterial für den Mörder
 var pCursor = GetCursor(iKiller);
 if (pCursor)
 {
  var idFirstContents = pCursor->Contents()->GetID();

  // 6 Pfeile
  if (!Random(4))
  {
   CreateContents(ARRW, pCursor, 6);
  }
  // 2 Kristalle
  else if (!Random(3))
  {
   CreateContents(CRYS, pCursor, 2); 
  }
  // 1 Brot + 1 Wasserfass
  else if (!Random(2))
  {
   CreateContents(BRED, pCursor);
   CreateContents(WBRL, pCursor);
  }
  // 1 Zufallszauber
  else
  {
   CreateContents(RMMG, pCursor);
  }

  if (pCursor->Contents()->GetID() != idFirstContents) ShiftContents(pCursor, 0, idFirstContents);
 }
}

global func UpdateScoreboard(int iPlr, bool fShow)
{
 var iPlrID = GetPlayerID(iPlr);

 var iColID = ScoreboardCol(RLNC);
 SetScoreboardData(iPlrID,		iColID,		Format("%d", Relaunches(iPlr)),	Relaunches(iPlr));
 SortScoreboard(iColID, true);

 iColID = ScoreboardCol(KLLS);
 SetScoreboardData(iPlrID,		iColID,		Format("%d", Kills(iPlr)),	Kills(iPlr));

 if (fShow)
 {
  DoScoreboardShow(1, iPlr);
  Schedule(Format("DoScoreboardShow(-1, %d)", iPlr), 38*3);
 }
}
