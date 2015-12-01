set QUALITES;
set USINES;

param N integer >= 0;
set SEMS := 1..N;

param demande{QUALITES, SEMS} >= 0;
param cout_par_jour{USINES} >= 0;
param tonne_par_jour{QUALITES, USINES} >= 0;
param stock_init{QUALITES} >= 0;

var jour{USINES} >= 0;
var qte_produite{SEMS, QUALITES} >= 0;
var qte_stock{SEMS, QUALITES} >= 0;
var jours_ouvres{SEMS, USINES} >= 0;
var frais_hebdo{SEMS} >= 0;
	
minimize profit :
	sum{u in USINES} cout_par_jour[u] * jour[u];

subject to production_limitee{q in QUALITES, s in SEMS} :
	sum{u in USINES} tonne_par_jour[q, u] * jour[u] >= demande[q, s];

subject to init_stock{q in QUALITES} :
	qte_stock[1,q] = stock_init[q];

subject to final_stock{q in QUALITES} :
	qte_stock[N+1,q] >= stock_init[q];

subject to equilibre{s in SEMS, q in QUALITES} :
	qte[s,q] + qte_produite[s,q] = qte_stock[s+1,q] + qte_produite[s,q] - demande[q,s];

subject to frais_hebdomadaire :
	sum{s in SEMS}
	
data stock_papier.dat;
	