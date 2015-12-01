set DETAILLANTS;
set REGIONS;
set CATEGORIES;

param region{DETAILLANTS} symbolic in REGIONS;
param huile{DETAILLANTS} >= 0;
param nb_pts_vente{DETAILLANTS} >= 0;
param spiritueux{DETAILLANTS} >= 0;
param categorie{DETAILLANTS} symbolic in CATEGORIES;

var appartient_a_d1 {DETAILLANTS} binary;
var pourcent_spiritueux_d1 >= 0;
var pourcent_pts_ventes_d1 >= 0;
var poucent_huile_d1{REGIONS} >= 0;
var pourcent_detaillant_d1{CATEGORIES} >= 0;

minimize rapport_d1:
	
	
# Spiritueux pour d1
subject to spiritueux_d1 :
	35 <= (sum{d in DETAILLANTS} spiritueux[d] * appartient_a_d1[d]) / (sum{d in DETAILLANTS}spiritueux[d]) * 100 <= 45;

# Spiritueux pour d2
subject to spiritueux_d2 :
	55 <= (sum{d in DETAILLANTS} spiritueux[d] * (1 - appartient_a_d1[d])) / (sum{d in DETAILLANTS}spiritueux[d]) * 100 <= 65;

# Nb point de vente pour d1
subject to nb_point_vente_d1 :
	35 <= (sum{d in DETAILLANTS} nb_pts_vente[d] * appartient_a_d1[d]) / (sum{d in DETAILLANTS}nb_pts_vente[d]) * 100 <= 45;

# Nb point de vente pour d2
subject to nb_point_vente_d2 :
	55 <= (sum{d in DETAILLANTS} nb_pts_vente[d] * (1 - appartient_a_d1[d])) / (sum{d in DETAILLANTS}nb_pts_vente[d]) * 100 <= 65;

# Le marche de l'huile dans chaque region pour d1'
subject to huile_d1{r in REGIONS} :
	35 <= (sum{d in DETAILLANTS : region[d] = r} huile[d] * appartient_a_d1[d]) / (sum{d in DETAILLANTS : region[d] = r}huile[d]) * 100 <= 45;

# Le marche de l'huile dans chaque region pour d1'
subject to huile_d2{r in REGIONS} :
	55 <= (sum{d in DETAILLANTS : region[d] = r} huile[d] * (1 - appartient_a_d1[d])) / (sum{d in DETAILLANTS : region[d] = r}huile[d]) * 100 <= 65;

# Le nombre de detaillant pour chaque categorie pour d1
subject to detaillant_par_categorie_d1{c in CATEGORIES} :
	35 <= (sum{d in DETAILLANTS : categorie[d] = c} appartient_a_d1[d]) / (sum{d in DETAILLANTS : categorie[d] = c} 1) * 100 <= 45;

# Le nombre de detaillant pour chaque categorie pour d2
subject to detaillant_par_categorie_d2{c in CATEGORIES} :
	55 <= (sum{d in DETAILLANTS : categorie[d] = c} (1 - appartient_a_d1[d])) / (sum{d in DETAILLANTS : categorie[d] = c} 1) * 100 <= 65;