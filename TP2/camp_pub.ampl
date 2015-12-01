set MEDIA;

param budget >= 0; #en euros
param travailleurs >= 0; #en personnes
param cout{MEDIA} >= 0; #en euros;
param impact{MEDIA} >= 0; #en personnes
param travailleurs_semaines{MEDIA} >= 0; #en personnes / semaines
param mini{MEDIA} >= 0; #en unites de medias
var qte{MEDIA} >= 0;

maximize nb_pers:
	sum {m in MEDIA}
	qte[m] * impact[m];

subject to minitv{m in MEDIA}:
	qte[m] >= mini[m];

subject to budget_limite:
	sum{m in MEDIA}
	qte[m] * cout[m] <= budget;

subject to nb_travailleurs:
	sum{m in MEDIA}
	qte[m] * travailleurs_semaines[m] <= travailleurs;
	
data camp_pub.dat;