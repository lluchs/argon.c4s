#strict

protected func Incineration()
{
 Incinerate(GetActionTarget());
 Extinguish();
}

protected func AttachTargetLost()
{
 RemoveObject();
 return(0);
}

protected func Entrance()
{
 RemoveObject();
 return(0);
}