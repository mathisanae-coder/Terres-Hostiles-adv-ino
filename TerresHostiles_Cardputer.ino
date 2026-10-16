/*
 * TERRES HOSTILES — M5Stack Cardputer Adv (ESP32-S3)
 * Jeu de survie en solitaire (cartes). Sketch unique.
 *
 * Arduino IDE : carte « M5Cardputer » (paquet M5Stack >= 3.x), bibliothèques :
 *   M5Cardputer (>= 1.1.1), M5Unified, M5GFX.  Partition par défaut.
 * Touches : ; haut  . bas  , gauche  / droite  Entrée/Espace valider
 *           Retour arrière ou ` annuler/menu  1-9 choix direct
 * Les données de cartes (section A) sont générées depuis le jeu web (gen_data.js).
 */
/* ===== A. DONNÉES (générées) ===== */
#include <stdint.h>
/* ===== DONNÉES GÉNÉRÉES depuis index.html (gen_data.js) — ne pas modifier à la main ===== */
#define N_ENV 11
#define N_DEF 150
#define N_WX 10
#define SEASON_LEN 8
#define HAND_MAX 8
#define INV_MAX 7
#define SAT_MAX 10
#define EAU_MAX 10
#define ENE_MAX 10
#define AP_BASE 4
#define EXPLORE_DRAWS 2
#define SIGNAL_GOAL 5
enum { T_MATERIAU=1u, T_COUTEAU=2u, T_OUTIL=4u, T_HACHE=8u, T_ARME=16u, T_ARC=32u, T_FEU=64u, T_REPOUSSE=128u, T_CANNE=256u, T_PIEGE=512u, T_RECIPIENT=1024u, T_CHAPEAU=2048u, T_CAPE=4096u, T_BOTTES=8192u, T_CORDE=16384u, T_ORIENTATION=32768u, T_GARDE=65536u, T_EAU=131072u, T_PANSEMENT=262144u, T_ANTIDOTE=524288u, T_ABRI=1048576u, T_SOLIDE=2097152u, T_CITERNE=4194304u, T_JARDIN=8388608u, T_FUMOIR=16777216u, T_SAC=33554432u, T_MIROIR=67108864u, T_LUNETTES=134217728u, T_FOYER=268435456u };
enum { K_MAT=0, K_OBJET=1, K_FOOD=2, K_SOIN=3, K_CONTRE=4, K_HABITAT=5, K_PRED=6, K_PROIE=7, K_MALUS=8, K_CHANCE=9 };
enum { E_DESERT=0, E_OCEAN=1, E_FORET=2, E_GLACIER=3, E_MONTAGNE=4, E_MARAIS=5, E_JUNGLE=6, E_SAVANE=7, E_STEPPE=8, E_CANYON=9, E_FJORD=10 };
enum { CD_SAIGNEMENT=1, CD_INFECTION=2, CD_FRACTURE=4, CD_GASTRO=8 };
enum { W_CLAIR=0, W_CANICULE=1, W_SABLE=2, W_GEL=3, W_BLIZZARD=4, W_VENT=5, W_PLUIE=6, W_ORAGE=7, W_BRUME=8, W_HOULE=9 };
enum { D_BOIS=0, D_PIERRE=1, D_FIBRES=2, D_PEAU=3, D_COUTEAU=4, D_HACHE=5, D_ARC=6, D_LANCE=7, D_BRIQUET=8, D_PIERRE_A_FEU=9, D_TORCHE=10, D_FEU_DE_CAMP=11, D_CANNE_A_PECHE=12, D_FILET=13, D_COLLET=14, D_CASSEROLE=15, D_GOURDE=16, D_CHAPEAU_DE_PAILLE=17, D_MANTEAU_DE_FOURRURE=18, D_CAPE_DE_PLUIE=19, D_BOTTES_MONTANTES=20, D_BOUCLIER_DE_BOIS=21, D_CORDE=22, D_BOUSSOLE=23, D_CHIEN_DE_GARDE=24, D_BAIES_SAUVAGES=25, D_UFS=26, D_RATION_DE_SURVIE=27, D_RACINES=28, D_COQUILLAGES=29, D_POISSON=30, D_GIBIER=31, D_RAGOUT=32, D_VIANDE_SECHEE=33, D_POISSON_SECHE=34, D_POISSON_FUME=35, D_GIBIER_FUME=36, D_FRUITS_SECS=37, D_EAU_DE_SOURCE=38, D_EAU_DE_PLUIE=39, D_EAU_TROUBLE=40, D_NEIGE=41, D_CACTUS=42, D_NOIX_DE_COCO=43, D_EAU_POTABLE=44, D_BANDAGE=45, D_PLANTES_MEDICINALES=46, D_ATTELLE=47, D_SOINS_DE_FORTUNE=48, D_ANTIDOTE=49, D_FUSEE_DE_DETRESSE=50, D_COUVERTURE_DE_SURVIE=51, D_ABRI_DE_FORTUNE=52, D_CABANE=53, D_REFUGE_FORTIFIE=54, D_LOUP=55, D_OURS=56, D_OURS_POLAIRE=57, D_LEOPARD_DES_NEIGES=58, D_SERPENT=59, D_SCORPION=60, D_VAUTOURS=61, D_REQUIN=62, D_MEDUSES=63, D_CROCODILE=64, D_LIEVRE=65, D_CERF=66, D_PHOQUE=67, D_BANC_DE_POISSONS=68, D_LEZARD=69, D_TEMPETE=70, D_BLIZZARD=71, D_GEL_NOCTURNE=72, D_COUP_DE_CHALEUR=73, D_TEMPETE_DE_SABLE=74, D_EBOULEMENT=75, D_VAGUE_SCELERATE=76, D_INFECTION=77, D_PLAIE_OUVERTE=78, D_EAU_SOUILLEE=79, D_MOISISSURE=80, D_PILLEUR_NOCTURNE=81, D_EGAREMENT=82, D_EPAVE=83, D_CACHE_ABANDONNEE=84, D_SOURCE_CACHEE=85, D_GROTTE_SECHE=86, D_ECLAIRCIE=87, D_CARCASSE_FRAICHE=88, D_BOIS_FLOTTE=89, D_FRUITS_MURS=90, D_CITERNE=91, D_JARDIN=92, D_FUMOIR=93, D_CHAMPIGNONS=94, D_NOIX=95, D_MIEL_SAUVAGE=96, D_INSECTES_GRILLES=97, D_RATION_MILITAIRE=98, D_ROSEE=99, D_PELLE=100, D_SAC_A_DOS=101, D_MIROIR_DE_SIGNALISATION=102, D_LUNETTES_DE_NEIGE=103, D_PONCHO=104, D_NASSE=105, D_CARTE_TOPOGRAPHIQUE=106, D_PANIER=107, D_HYENE=108, D_LYNX=109, D_SANGLIER=110, D_BARRACUDA=111, D_PIRANHAS=112, D_CHEVRE_DE_MONTAGNE=113, D_PERDRIX=114, D_CRABES=115, D_RENNE=116, D_GAZELLE=117, D_GRENOUILLES=118, D_THON=119, D_FIEVRE_DES_MARAIS=120, D_AVALANCHE=121, D_CRAMPES=122, D_PIED_TORDU=123, D_MAREE_MONTANTE=124, D_COUP_DE_SOLEIL=125, D_PLUIE_BIENVENUE=126, D_RUCHE_SAUVAGE=127, D_TROUSSE_OUBLIEE=128, D_AURORE_MAGNIFIQUE=129, D_PRAIRIE_MEDICINALE=130, D_OASIS=131, D_ROCHERS_AUX_ALGUES=132, D_JAGUAR=133, D_FOURMIS_LEGIONNAIRES=134, D_LION=135, D_LIONNE_EN_CHASSE=136, D_OURS_BRUN=137, D_PUMA=138, D_ANTILOPE=139, D_MARMOTTE=140, D_TAPIR=141, D_SAUMON=142, D_CRUE_ECLAIR=143, D_MOUSTIQUES=144, D_GASTRO_ENTERITE=145, D_HYPOTHERMIE_DE_MER=146, D_GUELTA=147, D_BERGER_SUR_LA_PISTE=148, D_TROUEE_DANS_LA_CANOPEE=149 };
struct CardDef{const char*nom;const char*txt;uint8_t k,n,dur,perish,power,lvl,need,cost,lootN,burn,passif;uint16_t biomes;uint32_t tags,req,link;int16_t dry,loot,extra,gain0,gain1;int8_t atk,def,sat,eau,pv,ene,moral,r0,r1,r2;uint8_t cure,cond,lose;};
static const CardDef DEFS[N_DEF]={
 {"Bois","Branches droites, bois sec.",K_MAT,6,0,0,0,0,0,0,0,0,0,0x7ff,1u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Pierre","Éclats tranchants, silex, galets.",K_MAT,5,0,0,0,0,0,0,0,0,0,0x7ff,1u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Fibres","Écorce, herbes longues, tendons.",K_MAT,6,0,0,0,0,0,0,0,0,0,0x7ff,1u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Peau","Cuir brut, à travailler avec une lame.",K_MAT,2,0,0,0,0,0,0,0,0,0,0x7ff,1u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Couteau","Taille, dépèce, creuse.",K_OBJET,3,6,0,0,0,0,0,0,0,0,0x7ff,6u,0u,0u,-1,-1,-1,-1,-1,1,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Hache","Abat du bois, fend les ennuis.",K_OBJET,1,5,0,0,0,0,0,0,0,0,0x7ff,12u,0u,0u,-1,-1,-1,-1,-1,2,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Arc","Frappe à distance. Indispensable pour le grand gibier.",K_OBJET,1,5,0,0,0,0,0,0,0,0,0x7ff,48u,0u,0u,-1,-1,-1,-1,-1,2,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Lance","Pointe taillée et durcie au feu.",K_OBJET,1,4,0,0,0,0,0,0,0,0,0x7ff,16u,0u,0u,-1,-1,-1,-1,-1,2,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Briquet","Un feu en une seconde. Cuit, éclaire, désinfecte.",K_OBJET,2,7,0,0,0,0,0,0,0,0,0x7ff,64u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Pierre à feu","Étincelles et amadou. Plus lent, mais ça marche.",K_OBJET,0,5,0,0,0,0,0,0,0,0,0x7ff,64u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Torche","Cuit et fait reculer les bêtes. Se consume chaque soir.",K_OBJET,1,3,0,0,0,0,0,0,1,0,0x7ff,192u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Feu de camp","Cuit, éclaire, tient les bêtes à distance. Meurt en 3 nuits.",K_OBJET,0,3,0,0,0,0,0,0,1,0,0x7ff,192u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Canne à pêche","Patience et fil nylon.",K_OBJET,1,6,0,0,0,0,0,0,0,0,0x7ff,256u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Filet","Prend le poisson comme le petit gibier. Peut être tendu pour la nuit.",K_OBJET,1,4,0,0,0,0,0,0,0,0,0x7ff,768u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Collet","Un nœud coulant, tendu la nuit pour attraper du gibier.",K_OBJET,1,4,0,0,0,0,0,0,0,0,0x7ff,512u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Casserole","Pour bouillir et conserver. Les vivres tiennent un jour de plus.",K_OBJET,2,10,0,0,0,0,0,0,0,0,0x7ff,1024u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Gourde","Garde l'eau fraîche. Récolte la pluie.",K_OBJET,2,8,0,0,0,0,0,0,0,0,0x7ff,1024u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,1,0,0,0,0,0},
 {"Chapeau de paille","De l'ombre portative. S'abîme au soleil.",K_OBJET,2,6,0,0,0,0,0,0,0,0,0x7ff,2048u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,2,0,0,0,0,0},
 {"Manteau de fourrure","Lourd, chaud, et assez épais pour les griffes.",K_OBJET,1,7,0,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,-1,-1,0,1,0,0,0,0,0,0,2,0,0,0,0},
 {"Cape de pluie","Toile cirée contre embruns et averses.",K_OBJET,1,5,0,0,0,0,0,0,0,0,0x7ff,4096u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,2,0,0,0},
 {"Bottes montantes","Les pieds secs gagnent les batailles.",K_OBJET,2,8,0,0,0,0,0,0,0,0,0x7ff,8192u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,1,1,0,0,0},
 {"Bouclier de bois","Planches clouées, bien serrées.",K_OBJET,0,5,0,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,-1,-1,0,2,0,0,0,0,0,0,0,0,0,0,0},
 {"Corde","Sert à lier, grimper, haubaner.",K_OBJET,1,6,0,0,0,0,0,0,0,0,0x7ff,16384u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Boussole","Le nord ne ment pas.",K_OBJET,1,0,0,0,0,0,0,0,0,0,0x7ff,32768u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Chien de garde","Dort peu, aboie fort.",K_OBJET,1,0,0,0,0,0,0,0,0,0,0x7ff,65536u,0u,0u,-1,-1,-1,-1,-1,1,1,0,0,0,0,0,0,0,0,0,0,0},
 {"Baies sauvages","Sucrées, sans façon.",K_FOOD,4,0,3,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,37,-1,-1,-1,-1,0,0,2,0,0,0,0,0,0,0,0,0,0},
 {"Œufs","Trouvés dans un nid abandonné.",K_FOOD,2,0,3,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,-1,-1,0,0,2,0,0,0,0,0,0,0,0,0,0},
 {"Ration de survie","Sous vide, pour les mauvais jours.",K_FOOD,1,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,-1,-1,0,0,3,0,0,0,0,0,0,0,0,0,0},
 {"Racines","Il faut creuser pour les avoir.",K_FOOD,3,0,0,0,0,0,0,0,0,0,0x7ff,0u,4u,0u,-1,-1,-1,-1,-1,0,0,2,0,0,0,0,0,0,0,0,0,0},
 {"Coquillages","À ouvrir avec une lame.",K_FOOD,2,0,2,0,0,0,0,0,0,0,0x7ff,0u,2u,0u,-1,-1,-1,-1,-1,0,0,2,0,0,0,0,0,0,0,0,0,0},
 {"Poisson","Grillé, il tient au corps. Frais, il ne dure pas.",K_FOOD,3,0,2,0,0,0,0,0,0,0,0x7ff,0u,64u,0u,34,-1,-1,-1,-1,0,0,3,0,0,0,0,0,0,0,0,0,0},
 {"Gibier","Gras, dense, réparateur. À cuire ou à sécher vite.",K_FOOD,2,0,2,0,0,0,0,0,0,0,0x7ff,0u,64u,0u,33,-1,-1,-1,-1,0,0,4,0,1,0,0,0,0,0,0,0,0},
 {"Ragoût","Le seul vrai repas chaud. À manger sans attendre.",K_FOOD,2,0,1,0,0,0,0,0,0,0,0x7ff,0u,1088u,0u,-1,-1,-1,-1,-1,0,0,5,1,1,0,0,0,0,0,0,0,0},
 {"Viande séchée","Salée, dure, éternelle.",K_FOOD,0,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,-1,-1,0,0,3,0,0,0,0,0,0,0,0,0,0},
 {"Poisson séché","Fumé au feu de bois.",K_FOOD,0,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,-1,-1,0,0,3,0,0,0,0,0,0,0,0,0,0},
 {"Poisson fumé","Fumé longuement au Fumoir : il cale mieux que le séché et ne pourrit pas.",K_FOOD,0,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,-1,-1,0,0,4,0,0,0,0,0,0,0,0,0,0},
 {"Gibier fumé","Viande fumée au Fumoir : dense, réparatrice, éternelle.",K_FOOD,0,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,-1,-1,0,0,5,0,1,0,0,0,0,0,0,0,0},
 {"Fruits secs","Légers et durables.",K_FOOD,0,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,-1,-1,0,0,2,0,0,0,0,0,0,0,0,0,0},
 {"Eau de source","Claire, froide, un trésor.",K_FOOD,3,0,0,0,0,0,0,0,0,0,0x534,131072u,0u,0u,-1,-1,-1,-1,-1,0,0,0,4,0,0,0,0,0,0,0,0,0},
 {"Eau de pluie","Recueillie dans un récipient.",K_FOOD,2,0,0,0,0,0,0,0,0,0,0x7f6,131072u,1024u,0u,-1,-1,-1,-1,-1,0,0,0,3,0,0,0,0,0,0,0,0,0},
 {"Eau trouble","À faire bouillir. Crue, elle rend malade.",K_FOOD,2,0,0,0,0,0,0,0,0,0,0x3e5,0u,1088u,0u,-1,-1,-1,-1,-1,0,0,0,4,0,0,0,0,0,0,0,0,0},
 {"Neige","À fondre. La manger crue refroidit.",K_FOOD,3,0,0,0,0,0,0,0,0,0,0x518,0u,64u,0u,-1,-1,-1,-1,-1,0,0,0,3,0,0,0,0,0,0,0,0,0},
 {"Cactus","Chair gorgée d'eau sous les épines.",K_FOOD,3,0,0,0,0,0,0,0,0,0,0x281,0u,2u,0u,-1,-1,-1,-1,-1,0,0,1,3,0,0,0,0,0,0,0,0,0},
 {"Noix de coco","Échouée sur la plage.",K_FOOD,2,0,0,0,0,0,0,0,0,0,0x42,0u,2u,0u,-1,-1,-1,-1,-1,0,0,2,3,0,0,0,0,0,0,0,0,0},
 {"Eau potable","En bouteille. Boisson sûre, ou antidote à l'eau souillée.",K_FOOD,1,0,0,0,0,0,0,0,0,0,0x7ff,131072u,0u,0u,-1,-1,-1,-1,-1,0,0,0,4,0,0,0,0,0,0,0,0,0},
 {"Bandage","Propre, serré. Arrête un saignement.",K_SOIN,3,0,0,0,0,0,0,0,0,0,0x7ff,262144u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,1,0,0,0,0,0,1,0,0},
 {"Plantes médicinales","Soigne l'infection. Fait aussi office d'antidote.",K_SOIN,2,0,0,0,0,0,0,0,0,0,0x7ff,524288u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,1,0,0,0,0,0,2,0,0},
 {"Attelle","Immobilise l'os brisé.",K_SOIN,1,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,4,0,0},
 {"Soins de fortune","Lame stérilisée à la flamme : le gros soin.",K_SOIN,1,0,0,0,0,0,0,0,0,0,0x7ff,0u,66u,0u,-1,-1,-1,-1,-1,0,0,0,0,4,0,0,0,0,0,7,0,0},
 {"Antidote","Annule une infection, ou en guérit une.",K_CONTRE,2,0,0,0,0,0,0,0,0,0,0x7ff,524288u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,2,0,0},
 {"Fusée de détresse","Fait fuir n'importe quelle bête.",K_CONTRE,1,0,0,0,0,0,0,0,0,0,0x7ff,128u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Couverture de survie","Tient lieu d'abri pour une nuit.",K_CONTRE,1,0,0,0,0,0,0,0,0,0,0x7ff,1048576u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Abri de fortune","Branches et bâche. +2 PV max, meilleur sommeil.",K_HABITAT,3,0,0,0,1,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Cabane","Murs et toit. Garde-manger : vivres +1 jour. Se fabrique aussi.",K_HABITAT,2,0,0,0,2,1,0,0,0,0,0x7ff,0u,4u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Refuge fortifié","Palissade et foyer permanent (#feu). Coût : 2 cartes.",K_HABITAT,1,0,0,0,3,2,2,0,0,0,0x7ff,0u,16388u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Loup","Chasse en meute, attaque à la nuit.",K_PRED,2,0,0,3,0,0,0,0,0,0,0x51c,0u,0u,65664u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Ours","Affamé avant l'hiver.",K_PRED,2,0,0,4,0,0,0,0,0,0,0x414,0u,0u,128u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Ours polaire","Roi de la banquise, sans pitié.",K_PRED,2,0,0,4,0,0,0,0,0,0,0x8,0u,0u,128u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Léopard des neiges","Un éclair blanc.",K_PRED,1,0,0,3,0,0,0,0,0,0,0x118,0u,0u,65664u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Serpent","Sa morsure se soigne, si on a de quoi.",K_PRED,2,0,0,2,0,0,0,0,0,0,0x2e5,0u,0u,589824u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Scorpion","Sous la pierre où vous vous asseyez.",K_PRED,2,0,0,2,0,0,0,0,0,0,0x2c1,0u,0u,524288u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Vautours","Ils attendent. Ils sont patients.",K_PRED,1,0,0,2,0,0,0,0,0,0,0x391,0u,0u,65664u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Requin","L'aileron tourne autour de vous.",K_PRED,2,0,0,4,0,0,0,0,0,0,0x2,0u,0u,128u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Méduses","Des filaments invisibles.",K_PRED,2,0,0,2,0,0,0,0,0,0,0x402,0u,0u,524288u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Crocodile","Une bûche qui ouvre un œil.",K_PRED,2,0,0,4,0,0,0,0,0,0,0xe0,0u,0u,128u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Lièvre","Rapide, mais prévisible.",K_PROIE,2,0,0,0,0,0,0,1,0,0,0x395,0u,0u,528u,-1,31,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Cerf","Il faut une flèche. Deux repas et une peau.",K_PROIE,2,0,0,0,0,0,0,2,0,0,0x514,0u,0u,32u,-1,31,3,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Phoque","Gras et lent sur la glace.",K_PROIE,2,0,0,0,0,0,0,2,0,0,0x40a,0u,0u,16u,-1,31,3,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Banc de poissons","Le fil frémit.",K_PROIE,3,0,0,0,0,0,0,2,0,0,0x46a,0u,0u,256u,-1,30,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Lézard","Petit, mais on fait avec.",K_PROIE,2,0,0,0,0,0,0,1,0,0,0x281,0u,0u,528u,-1,31,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Tempête","Le ciel s'abat. Un refuge solide ou une cape aide.",K_MALUS,2,0,0,0,0,0,0,0,0,0,0x476,0u,0u,2101248u,-1,-1,-1,-1,-1,0,0,0,0,-2,0,0,0,0,0,0,0,0},
 {"Blizzard","On n'y voit plus. Un abri sauve.",K_MALUS,2,0,0,0,0,0,0,0,0,0,0x118,0u,0u,1048576u,-1,-1,-1,-1,-1,0,0,0,0,-3,-1,0,0,0,0,0,0,0},
 {"Gel nocturne","Le thermomètre plonge.",K_MALUS,2,0,0,0,0,0,0,0,0,0,0x718,0u,0u,1048640u,-1,-1,-1,-1,-1,0,0,0,0,-2,0,0,0,0,0,0,0,0},
 {"Coup de chaleur","Le sol brûle, la tête tourne.",K_MALUS,2,0,0,0,0,0,0,0,0,0,0x281,0u,0u,1179648u,-1,-1,-1,-1,-1,0,0,0,-2,-2,0,0,0,0,0,0,0,0},
 {"Tempête de sable","Le sable s'infiltre partout, vivres comprises.",K_MALUS,2,0,0,0,0,0,0,0,0,0,0x381,0u,0u,1048576u,-1,-1,-1,-1,-1,0,0,0,0,-1,0,0,0,0,0,0,0,2},
 {"Éboulement","La pente se détache. Un os peut casser.",K_MALUS,1,0,0,0,0,0,0,0,0,0,0x610,0u,0u,2113536u,-1,-1,-1,-1,-1,0,0,0,0,-2,0,0,0,0,0,0,4,0},
 {"Vague scélérate","Elle emporte un de vos objets.",K_MALUS,2,0,0,0,0,0,0,0,0,0,0x402,0u,0u,2113536u,-1,-1,-1,-1,-1,0,0,0,0,-1,0,0,0,0,0,0,0,3},
 {"Infection","La plaie noircit, la fièvre monte.",K_MALUS,3,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,524288u,-1,-1,-1,-1,-1,0,0,0,0,-1,0,0,0,0,0,0,2,0},
 {"Plaie ouverte","Une coupure profonde qui ne s'arrête pas.",K_MALUS,2,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,262144u,-1,-1,-1,-1,-1,0,0,0,0,-1,0,0,0,0,0,0,1,0},
 {"Eau souillée","Bouillie ou pure, sinon l'infection suit.",K_MALUS,2,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,131136u,-1,-1,-1,-1,-1,0,0,0,0,-1,0,0,0,0,0,0,2,0},
 {"Moisissure","Les vivres tournent. Un récipient fermé les protège.",K_MALUS,2,0,0,0,0,0,0,0,0,0,0x466,0u,0u,1024u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,2},
 {"Pilleur nocturne","Une main dans votre sac.",K_MALUS,2,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,65600u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 {"Égarement","Vous tournez en rond jusqu'à l'épuisement.",K_MALUS,2,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,32768u,-1,-1,-1,-1,-1,0,0,-2,0,0,-2,0,0,0,0,0,0,0},
 {"Épave","Une coque éventrée, encore pleine de choses utiles.",K_CHANCE,1,0,0,0,0,0,0,0,0,0,0x422,0u,0u,0u,-1,-1,-1,22,15,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Cache abandonnée","Quelqu'un est passé avant vous, et est parti vite.",K_CHANCE,2,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,27,45,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Source cachée","Un filet d'eau derrière un rocher.",K_CHANCE,2,0,0,0,0,0,0,0,0,0,0x3b5,0u,0u,0u,-1,-1,-1,-1,-1,0,0,0,5,0,0,0,0,0,0,0,0,0},
 {"Grotte sèche","Une nuit de vrai sommeil.",K_CHANCE,2,0,0,0,0,0,0,0,0,0,0x719,0u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,1,3,0,0,0,0,0,0,0},
 {"Éclaircie","Un moment de calme qui remet les idées en place.",K_CHANCE,2,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,-1,-1,0,0,1,0,1,1,0,0,0,0,0,0,0},
 {"Carcasse fraîche","Un animal mort tout à l'heure, sans prédateur en vue.",K_CHANCE,2,0,0,0,0,0,0,0,0,0,0x39d,0u,0u,0u,-1,-1,-1,31,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Bois flotté","La marée a déposé de quoi construire.",K_CHANCE,2,0,0,0,0,0,0,0,0,0,0x442,0u,0u,0u,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Fruits mûrs","Un arbre chargé, à l'écart des sentiers.",K_CHANCE,2,0,0,0,0,0,0,0,0,0,0x464,0u,0u,0u,-1,-1,-1,25,25,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Citerne","Récupère rosée et pluie : eau +1 chaque nuit (+2 s'il a plu).",K_OBJET,0,10,0,0,0,0,0,0,0,1,0x7ff,4195328u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Jardin","Plantes cultivées : une récolte une nuit sur deux.",K_OBJET,0,10,0,0,0,0,0,0,0,2,0x7ff,8388608u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Fumoir","Conserve la viande et le poisson : vivres +1 jour.",K_OBJET,0,10,0,0,0,0,0,0,0,0,0x7ff,16777216u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Champignons","Ceux que vous connaissez bien.",K_FOOD,2,0,3,0,0,0,0,0,0,0,0x464,0u,0u,0u,-1,-1,-1,-1,-1,0,0,2,0,0,0,0,0,0,0,0,0,0},
 {"Noix","Dures à ouvrir, longues à garder.",K_FOOD,2,0,0,0,0,0,0,0,0,0,0x414,0u,0u,0u,-1,-1,-1,-1,-1,0,0,2,0,0,0,0,0,0,0,0,0,0},
 {"Miel sauvage","Sucré, énergétique, désinfectant.",K_FOOD,1,0,0,0,0,0,0,0,0,0,0xe4,0u,0u,0u,-1,-1,-1,-1,-1,0,0,3,0,1,0,0,0,0,0,0,0,0},
 {"Insectes grillés","Croquants. On s'y fait.",K_FOOD,2,0,3,0,0,0,0,0,0,0,0x3e5,0u,64u,0u,-1,-1,-1,-1,-1,0,0,2,0,0,0,0,0,0,0,0,0,0},
 {"Ration militaire","Lourde, salée, indestructible.",K_FOOD,1,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,-1,-1,0,0,4,0,0,0,0,0,0,0,0,0,0},
 {"Rosée","Recueillie sur les pierres à l'aube.",K_FOOD,2,0,0,0,0,0,0,0,0,0,0x799,131072u,0u,0u,-1,-1,-1,-1,-1,0,0,0,2,0,0,0,0,0,0,0,0,0},
 {"Pelle","Creuse, déterre, aplanit.",K_OBJET,1,6,0,0,0,0,0,0,0,0,0x7ff,4u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Sac à dos","Main de 2 cartes de plus.",K_OBJET,1,0,0,0,0,0,0,0,0,0,0x7ff,33554432u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Miroir de signalisation","Un éclat de soleil porte loin : le signal ne demande plus de bois.",K_OBJET,1,8,0,0,0,0,0,0,0,0,0x7ff,67108864u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Lunettes de neige","Évite la cécité des neiges.",K_OBJET,1,6,0,0,0,0,0,0,0,0,0x7ff,134217728u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,1,0,0,0,0},
 {"Poncho","Toile cirée enfilée par la tête.",K_OBJET,1,6,0,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,1,1,0,0,0},
 {"Nasse","Un panier piège. Tendue la nuit, elle prend du poisson.",K_OBJET,1,5,0,0,0,0,0,0,0,0,0x7ff,768u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Carte topographique","Ne vous laisse plus tourner en rond.",K_OBJET,1,0,0,0,0,0,0,0,0,0,0x7ff,32768u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Panier","Tressé : porte l'eau, garde les vivres.",K_OBJET,1,6,0,0,0,0,0,0,0,0,0x7ff,1024u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Hyène","Un rire qui n'a rien de drôle.",K_PRED,1,0,0,3,0,0,0,0,0,0,0x81,0u,0u,65664u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Lynx","Silencieux, patient, rapide.",K_PRED,1,0,0,3,0,0,0,0,0,0,0x714,0u,0u,65664u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Sanglier","Charge tête baissée.",K_PRED,1,0,0,3,0,0,0,0,0,0,0x164,0u,0u,128u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Barracuda","Des dents, de la vitesse, aucune patience.",K_PRED,1,0,0,3,0,0,0,0,0,0,0x2,0u,0u,128u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Piranhas","Un banc de dents dans l'eau trouble.",K_PRED,1,0,0,2,0,0,0,0,0,0,0x60,0u,0u,128u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Chèvre de montagne","Sûre d'elle sur la paroi.",K_PROIE,2,0,0,0,0,0,0,2,0,0,0x610,0u,0u,48u,-1,31,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Perdrix","Elle s'envole au dernier moment.",K_PROIE,2,0,0,0,0,0,0,1,0,0,0x395,0u,0u,528u,-1,31,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Crabes","De côté, toujours.",K_PROIE,2,0,0,0,0,0,0,2,0,0,0x422,0u,0u,768u,-1,29,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Renne","Troupeau dans la plaine blanche.",K_PROIE,2,0,0,0,0,0,0,2,0,0,0x508,0u,0u,32u,-1,31,3,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Gazelle","Une silhouette, puis plus rien.",K_PROIE,1,0,0,0,0,0,0,2,0,0,0x181,0u,0u,32u,-1,31,3,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Grenouilles","Une dizaine, dans la vase.",K_PROIE,2,0,0,0,0,0,0,1,0,0,0x60,0u,0u,528u,-1,31,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Thon","Une prise qui fait plier la canne.",K_PROIE,1,0,0,0,0,0,0,3,0,0,0x2,0u,0u,256u,-1,30,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Fièvre des marais","Les moustiques, les eaux mortes, les frissons.",K_MALUS,1,0,0,0,0,0,0,0,0,0,0xe0,0u,0u,524288u,-1,-1,-1,-1,-1,0,0,0,0,-1,0,0,0,0,0,0,2,0},
 {"Avalanche","La pente entière se met en marche.",K_MALUS,1,0,0,0,0,0,0,0,0,0,0x18,0u,0u,2113536u,-1,-1,-1,-1,-1,0,0,0,0,-3,-1,0,0,0,0,0,0,0},
 {"Crampes","La déshydratation tord les muscles.",K_MALUS,1,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,131072u,-1,-1,-1,-1,-1,0,0,0,0,0,-2,0,0,0,0,0,0,0},
 {"Pied tordu","Un faux pas. Des bottes montantes évitent le pire.",K_MALUS,1,0,0,0,0,0,0,0,0,0,0x7f5,0u,0u,8192u,-1,-1,-1,-1,-1,0,0,0,0,-1,0,0,0,0,0,0,4,0},
 {"Marée montante","Elle emporte ce qui traîne.",K_MALUS,1,0,0,0,0,0,0,0,0,0,0x422,0u,0u,2113536u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,1},
 {"Coup de soleil","Peau brûlée, gorge sèche.",K_MALUS,1,0,0,0,0,0,0,0,0,0,0x283,0u,0u,1050624u,-1,-1,-1,-1,-1,0,0,0,-1,-1,0,0,0,0,0,0,0,0},
 {"Pluie bienvenue","Les nuages s'ouvrent juste au bon moment.",K_CHANCE,2,0,0,0,0,0,0,0,0,0,0x7f6,0u,0u,0u,-1,-1,-1,-1,-1,0,0,0,3,0,0,1,0,0,0,0,0,0},
 {"Ruche sauvage","Bourdonnement et or liquide.",K_CHANCE,1,0,0,0,0,0,0,0,0,0,0xe4,0u,0u,0u,-1,-1,-1,96,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Trousse oubliée","Un sac déchiré, mais la trousse est intacte.",K_CHANCE,1,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,45,46,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Aurore magnifique","Une lumière qui vaut tous les discours.",K_CHANCE,2,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,1,2,0,0,0,0,0,0},
 {"Prairie médicinale","Des plantes qui poussent à l'écart de tout.",K_CHANCE,1,0,0,0,0,0,0,0,0,0,0x574,0u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Oasis","Un point d'eau, des palmiers, un mirage qui tient bon.",K_CHANCE,1,0,0,0,0,0,0,0,0,0,0x1,0u,0u,0u,-1,-1,-1,-1,-1,0,0,1,6,0,0,0,0,0,0,0,0,0},
 {"Rochers aux algues","La marée basse découvre un garde-manger.",K_CHANCE,1,0,0,0,0,0,0,0,0,0,0x402,0u,0u,0u,-1,-1,-1,-1,29,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Jaguar","Une ombre tachetée. Il attend que vous baissiez la garde.",K_PRED,2,0,0,4,0,0,0,0,0,0,0x40,0u,0u,65664u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Fourmis légionnaires","Une marée vivante qui avance sur le sol.",K_PRED,1,0,0,2,0,0,0,0,0,0,0x40,0u,0u,524416u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Lion","Il chasse à la tombée du jour, en groupe.",K_PRED,2,0,0,4,0,0,0,0,0,0,0x80,0u,0u,128u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Lionne en chasse","Silencieuse, patiente, mortelle.",K_PRED,1,0,0,3,0,0,0,0,0,0,0x80,0u,0u,65664u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Ours brun","Affamé avant l'hiver.",K_PRED,1,0,0,4,0,0,0,0,0,0,0x100,0u,0u,128u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Puma","Il vous suit depuis la corniche.",K_PRED,1,0,0,3,0,0,0,0,0,0,0x200,0u,0u,65664u,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Antilope","Un troupeau à l'horizon : une seule flèche.",K_PROIE,2,0,0,0,0,0,0,2,0,0,0x80,0u,0u,32u,-1,31,3,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Marmotte","Elle siffle puis plonge au terrier.",K_PROIE,2,0,0,0,0,0,0,1,0,0,0x100,0u,0u,528u,-1,31,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Tapir","Lourd, lent, énorme.",K_PROIE,1,0,0,0,0,0,0,3,0,0,0x40,0u,0u,32u,-1,31,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Saumon","Ils remontent le courant par dizaines.",K_PROIE,2,0,0,0,0,0,0,3,0,0,0x400,0u,0u,256u,-1,30,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {"Crue éclair","Un orage lointain, un mur d'eau soudain. Montez sur un replat.",K_MALUS,2,0,0,0,0,0,0,0,0,0,0x200,0u,0u,2113536u,-1,-1,-1,-1,-1,0,0,0,0,-2,0,0,0,0,0,0,0,3},
 {"Moustiques","Des nuées, et la fièvre qui peut suivre.",K_MALUS,2,0,0,0,0,0,0,0,0,0,0xe0,0u,0u,524352u,-1,-1,-1,-1,-1,0,0,0,0,-1,0,0,0,0,0,0,2,0},
 {"Gastro-entérite","Eau ou nourriture douteuse : fièvre et diarrhée qui assèchent le corps.",K_MALUS,2,0,0,0,0,0,0,0,0,0,0x7ff,0u,0u,131136u,-1,-1,-1,-1,-1,0,0,0,-2,-1,0,0,0,0,0,0,8,0},
 {"Hypothermie de mer","Une chute à l'eau : le froid saisit tout.",K_MALUS,1,0,0,0,0,0,0,0,0,0,0x400,0u,0u,1048640u,-1,-1,-1,-1,-1,0,0,0,0,-2,-1,0,0,0,0,0,0,0},
 {"Guelta","Une vasque d'eau fraîche dans l'ombre d'un surplomb.",K_CHANCE,1,0,0,0,0,0,0,0,0,0,0x280,0u,0u,0u,-1,-1,-1,-1,-1,0,0,0,5,0,0,0,0,0,0,0,0,0},
 {"Berger sur la piste","Un homme à cheval vous voit et partage ce qu'il porte.",K_CHANCE,1,0,0,0,0,0,0,0,0,0,0x380,0u,0u,0u,-1,-1,-1,33,44,0,0,0,0,0,0,1,0,0,0,0,0,0},
 {"Trouée dans la canopée","Un coin de ciel : idéal pour un signal.",K_CHANCE,1,0,0,0,0,0,0,0,0,0,0x40,0u,0u,0u,-1,-1,-1,-1,-1,0,0,0,0,0,1,1,0,0,0,0,0,0},
};
struct EnvDef{const char*nom;const char*desc;uint8_t stress,niv,faim,soif;int16_t kit;uint8_t yB,yP,yF,forP,nForage;int16_t forage[3];uint16_t color;};
static const EnvDef ENVS[N_ENV]={
 {"Désert","Chaleur écrasante, eau presque introuvable, proies rares. L'ombre et les réserves décident de tout.",0,2,1,1,16,0,2,1,40,1,{28,-1,-1},0xb3a5},
 {"Océan","Embruns et tempêtes. Le poisson nourrit, mais l'eau douce ne vient que du ciel.",2,2,1,1,12,1,1,1,60,1,{29,-1,-1},0x2bb2},
 {"Forêt","Généreuse en eau, bois et gibier, mais pleine de prédateurs.",2,1,1,1,4,2,1,2,85,3,{25,28,26},0x3b86},
 {"Glacier","Le froid mord chaque nuit. Pas de bois : il faut du feu, de la fourrure et de la patience.",1,2,1,1,18,0,1,0,30,1,{26,-1,-1},0x4c34},
 {"Montagne","Vent, éboulis et grands carnassiers. La pierre abonde.",1,2,1,1,20,1,2,1,50,2,{28,26,-1},0x7b8c},
 {"Marais","Humidité, infections et crocodiles. L'eau est partout, rarement saine.",2,2,1,1,20,1,0,2,70,3,{25,28,29},0x6ba5},
 {"Jungle","Chaleur moite, pluie quasi quotidienne, canopée dense. L'eau est partout, les infections aussi.",2,2,1,1,4,2,0,3,85,3,{25,28,97},0x1b47},
 {"Savane","Herbes hautes, chaleur du jour, eau rare en saison sèche. La nuit, les grands fauves chassent.",0,1,1,1,17,1,1,2,50,3,{28,26,97},0xbc45},
 {"Steppe","Plateau nu balayé par le vent, presque sans bois. Gel en hiver, orages d'été, loups.",1,2,1,1,4,1,2,2,35,2,{28,26,-1},0x8c6b},
 {"Canyons","Parois de grès, chaleur écrasante, eau rarissime. Une crue éclair peut survenir par temps clair.",0,2,1,1,16,1,3,1,30,2,{28,97,-1},0xa265},
 {"Fjords","Pluie, vent, mer glaciale. Les vêtements mouillés tuent plus vite que la faim.",2,2,1,1,19,1,2,1,60,3,{29,25,26},0x3b70},
};
struct WxDef{const char*nom;const char*txt;int8_t st,eau,ap,expl,rain;};
static const WxDef WXS[N_WX]={
 {"Ciel dégagé","Une journée sans surprise.",0,0,0,0,0},
 {"Canicule","Chaleur accrue : stress +1, soif +1.",1,1,0,0,0},
 {"Vent de sable","On y voit mal : −1 point d'action.",0,0,-1,0,0},
 {"Vague de froid","Le froid s'installe : stress +1.",1,0,0,0,0},
 {"Blizzard","Stress +1 et −1 point d'action.",1,0,-1,0,0},
 {"Grand vent","Il glace les doigts : stress +1.",1,0,0,0,0},
 {"Pluie","Eau à récolter avec un récipient : +3 eau.",0,-1,0,0,1},
 {"Orage","Stress +1 et −1 point d'action.",1,0,-1,0,1},
 {"Brouillard","Explorer coûte 2 points d'action.",0,0,0,1,0},
 {"Grosse houle","Le sol bouge : −1 point d'action.",0,0,-1,0,0},
};
static const uint8_t WX_TABLE[N_ENV][8]={
 {0,0,0,0,1,1,2,2},
 {0,0,0,9,9,7,8,6},
 {0,0,0,6,6,6,8,7},
 {0,0,0,3,3,4,8,8},
 {0,0,0,5,5,3,8,7},
 {6,6,8,8,0,0,0,1},
 {6,6,6,7,8,0,0,1},
 {0,0,0,0,1,1,7,2},
 {0,0,0,5,5,3,7,8},
 {0,0,0,1,1,2,7,3},
 {6,6,6,8,8,5,5,0},
};
struct SeasonFx{int8_t st,eau,food;const char*txt;};
static const SeasonFx SEASON_FX[N_ENV][4]={
 {{0,0,0,"Journées tempérées."},{1,1,-10,"Chaleur extrême : stress +1, soif +1."},{0,0,5,"Les nuits fraîchissent."},{-1,0,-5,"Jours supportables : stress −1."}},
 {{0,0,5,"Mer calme, poissons nombreux."},{-1,0,10,"Belle mer : stress −1."},{1,0,0,"Tempêtes d'automne : stress +1."},{1,0,-10,"Mer dure et froide : stress +1, pêche difficile."}},
 {{0,0,10,"Tout pousse : baies et œufs."},{-1,0,10,"Nuits douces : stress −1."},{0,0,15,"Saison des récoltes."},{1,0,-20,"Gel et disette : stress +1, cueillette rare."}},
 {{0,0,5,"Dégel : un peu de vie revient."},{-1,0,10,"Été polaire : stress −1."},{0,0,0,"Les jours raccourcissent."},{1,0,-10,"Nuit polaire : stress +1."}},
 {{0,-1,0,"Fonte des neiges : soif −1."},{-1,0,5,"Beaux jours : stress −1."},{0,0,0,"Premières neiges."},{1,0,-15,"Neige et vent : stress +1."}},
 {{0,0,5,"Crues : l'eau est partout."},{1,0,0,"Chaleur moite : stress +1."},{0,0,10,"Brumes, mais gibier abondant."},{0,0,-10,"Marais gelé, nuits fraîches."}},
 {{0,0,10,"Saison des pluies : tout pousse."},{1,-1,5,"Chaleur moite : stress +1."},{0,0,5,"Pluies qui diminuent."},{0,0,0,"Saison plus sèche."}},
 {{0,-1,5,"Pluies : l'eau revient."},{1,1,-10,"Saison sèche : chaleur, stress +1, soif +1."},{1,1,-10,"Herbe sèche, points d'eau rares."},{0,0,0,"Journées tempérées."}},
 {{0,-1,5,"Dégel : ruisseaux."},{-1,0,10,"Été doux : stress −1."},{0,0,0,"Premiers gels."},{1,0,-15,"Hiver rude : stress +1, vivres rares."}},
 {{0,0,0,"Journées tempérées."},{1,1,-10,"Chaleur extrême : stress +1, soif +1."},{0,0,0,"Nuits fraîches."},{0,-1,-5,"Hiver froid mais sec."}},
 {{0,0,5,"Beaucoup de pluie."},{-1,0,10,"Jours très longs : stress −1."},{1,0,0,"Tempêtes d'automne : stress +1."},{1,0,-15,"Nuits longues, mer froide : stress +1."}},
};
static const char*const SEASON_NAME[4]={"Printemps","Été","Automne","Hiver"};
static const char*const HAB_NAME[4]={"Aucun habitat","Abri de fortune","Cabane","Refuge fortifié"};
static const char*const STRESS_NAME[3]={"Chaleur","Froid","Humidité"};
static const char*const COND_NAME[4]={"Saignement","Infection","Fracture","Gastro-entérite"};
static const char*const COND_TXT[4]={"−1 PV chaque nuit pendant 3 nuits. Un pansement l'arrête.","−1 PV chaque nuit pendant 4 nuits. Antidote ou plantes la guérissent.","−1 point d'action pendant 4 nuits. Une attelle la guérit.","−2 eau chaque nuit pendant 2 nuits, puis elle passe seule. Gardez de l'eau en réserve."};
static const uint8_t COND_DAYS[4]={3,4,4,2};
static const uint8_t RAW_RISK[N_ENV]={0,0,12,0,6,60,45,40,15,35,10};
static const char*const CARRIER[N_ENV]={"hélicoptère","navire","hélicoptère","avion de reconnaissance","hélicoptère de montagne","bateau à fond plat","hélicoptère","avion de brousse","hélicoptère","hélicoptère de secours","bateau de secours"};
struct DiffDef{const char*nom;const char*txt;int8_t ap,st,pv,drain,pw,loc,start;uint8_t chance100;uint8_t wear100;};
#define N_DIFF 5
static const DiffDef DIFFS[N_DIFF]={
 {"Randonneur","+1 point d'action, nuits plus douces.",1,-1,0,0,0,0,0,100,100},
 {"Survivaliste","Les règles telles quelles.",0,0,0,0,0,0,0,100,100},
 {"Extrême","Départ affaibli, un peu moins de chance, matériel qui s'use 50 % plus vite.",0,0,-2,0,0,0,0,85,150},
 {"Enfer","Le maximum : 1 PA de moins, faim et soif doublées, bêtes plus fortes, usure presque double, moins de chance, Habitants méfiants.",-1,0,-1,1,1,10,0,70,175},
 {"Impitoyable","Au-delà de l'Enfer : nuits glaciales, bêtes plus fortes, presque aucune chance, départ très affaibli.",-1,2,-3,1,2,15,-2,45,200},
};
struct Recipe{int16_t out;uint8_t bois,pierre,fibres,peau;uint32_t tools;uint16_t notEnv;};
#define N_REC 19
static const Recipe RECIPES[N_REC]={
 {52,2,0,1,0,0u,0x0},
 {53,3,0,2,0,4u,0x0},
 {7,1,1,0,0,4u,0x0},
 {5,1,2,0,0,0u,0x0},
 {6,1,0,2,0,4u,0x0},
 {14,0,0,2,0,0u,0x0},
 {22,0,0,2,0,0u,0x0},
 {13,0,0,3,0,0u,0x0},
 {12,1,0,1,0,0u,0x0},
 {9,0,2,1,0,0u,0x0},
 {10,1,0,1,0,64u,0x0},
 {11,2,0,0,0,64u,0x0},
 {47,1,0,1,0,0u,0x0},
 {18,0,0,1,2,4u,0x0},
 {19,0,0,1,1,4u,0x0},
 {21,2,0,0,1,4u,0x0},
 {91,2,0,2,0,4u,0x0},
 {92,1,0,2,0,4u,0x9},
 {93,2,1,0,0,64u,0x0},
};
/* ===== B. MOTEUR DE JEU (aucune dépendance matérielle : testable sur PC) ===== */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

static uint32_t hwrand();                       /* fourni par la plateforme */
static inline int rnd(int n){return n<=1?0:(int)(hwrand()%(uint32_t)n);}
static inline int clampi(int v,int a,int b){return v<a?a:(v>b?b:v);}
static inline int mini(int a,int b){return a<b?a:b;}
static inline int maxi(int a,int b){return a>b?a:b;}

#define FL_SET 1      /* collet / filet tendu pour la nuit */
#define FL_TMP 2      /* carte créée en cours de partie : ne retourne pas dans la pioche */
#define HAND_CAP 16   /* la main peut déborder pendant la journée, jamais le soir */
#define CACHE_CAP 5
#define MAXDECK 300
struct Card{uint8_t def;int8_t dur;uint8_t age;uint8_t fl;};
struct Msg{char t[18][88];char c[18];int n=0;};
static void mp(Msg&m,char tone,const char*f,...){
  if(m.n>=18)return;
  va_list a;va_start(a,f);vsnprintf(m.t[m.n],88,f,a);va_end(a);
  m.c[m.n]=tone;m.n++;
}
/* tone : 'g' bon, 'b' mauvais, ' ' neutre */

struct Player{
  uint8_t env,hab,ap,apMax,fort,foyer,garde,wx,wxNext,cond,alive,mort,sig;
  int8_t pv,sat,eau,ene,moral;
  uint8_t cd[4];
  char cause[20];
  Card hand[HAND_CAP];uint8_t nHand;
  Card inv[INV_MAX];uint8_t nInv;
  Card cache[CACHE_CAP];uint8_t nCache;
};
struct Game{
  uint8_t diff,jours,jour,s0,signal,watch,rescue,over,rescued,started;
  Card deck[MAXDECK];uint16_t nDeck;
  Card disc[MAXDECK];uint16_t nDisc;
  Player p;
};
static Game G;
static const CardDef& DEF_OF(const Card&c){return DEFS[c.def];}
static const DiffDef& DF(){return DIFFS[G.diff];}
static const EnvDef& ENV(){return ENVS[G.p.env];}

/* ---------- cartes ---------- */
static Card mkCard(int def,bool tmp){Card c;c.def=(uint8_t)def;c.dur=(int8_t)DEFS[def].dur;c.age=0;c.fl=tmp?FL_TMP:0;return c;}
static void discard(const Card&c){if(!(c.fl&FL_TMP)&&G.nDisc<MAXDECK)G.disc[G.nDisc++]=c;}
template<typename A> static void removeAt(A*arr,uint8_t&n,int i){for(int k=i;k<n-1;k++)arr[k]=arr[k+1];n--;}
static void shuffleCards(Card*a,int n){for(int i=n-1;i>0;i--){int j=rnd(i+1);Card t=a[i];a[i]=a[j];a[j]=t;}}
static void buildDeck(){
  G.nDeck=0;G.nDisc=0;
  for(int d=0;d<N_DEF;d++){
    for(int i=0;i<DEFS[d].n;i++){
      if(DEFS[d].k==K_CHANCE&&rnd(100)>=DF().chance100)continue;
      if(G.nDeck<MAXDECK)G.deck[G.nDeck++]=mkCard(d,false);
    }
  }
  shuffleCards(G.deck,G.nDeck);
}
static bool isThreat(const CardDef&d){return d.k==K_PRED||d.k==K_PROIE||d.k==K_MALUS;}
static bool isEvent(const CardDef&d){return isThreat(d)||d.k==K_CHANCE;}
static bool inBiome(const CardDef&d,int env){return (d.biomes>>env)&1;}
static bool drawCard(Card&out){
  Player&p=G.p;
  for(int t=0;t<60;t++){
    if(!G.nDeck){
      if(!G.nDisc)return false;
      memcpy(G.deck,G.disc,sizeof(Card)*G.nDisc);G.nDeck=G.nDisc;G.nDisc=0;
      shuffleCards(G.deck,G.nDeck);
    }
    Card c=G.deck[--G.nDeck];
    if(!inBiome(DEF_OF(c),p.env)){discard(c);continue;}
    out=c;return true;
  }
  return false;
}
static int  findDef(const Card*a,int n,int def){for(int i=0;i<n;i++)if(a[i].def==def)return i;return -1;}
static int  countDef(const Card*a,int n,int def){int k=0;for(int i=0;i<n;i++)if(a[i].def==def)k++;return k;}
static void gainCard(int def,int n,Msg*m){
  Player&p=G.p;
  for(int i=0;i<n&&p.nHand<HAND_CAP;i++)p.hand[p.nHand++]=mkCard(def,true);
  if(m&&n>0)mp(*m,'g',"+%d %s.",n,DEFS[def].nom);
}
static int matCount(int def){return countDef(G.p.hand,G.p.nHand,def);}

/* ---------- capacités calculées ---------- */
static uint32_t tagMask(const Player&p){
  uint32_t t=0;
  for(int i=0;i<p.nInv;i++)t|=DEFS[p.inv[i].def].tags;
  if(p.hab>=1)t|=T_ABRI;
  if(p.hab>=2)t|=T_SOLIDE;
  if(p.hab>=3||p.foyer>0)t|=T_FEU|T_FOYER;
  return t;
}
static bool has(uint32_t tag){return (tagMask(G.p)&tag)!=0;}
static int  pvMax(const Player&p){return 8+2*p.hab;}
static int  handMax(const Player&p){return HAND_MAX+((tagMask(p)&T_SAC)?2:0);}
static int  ATK(const Player&p){int s=0;for(int i=0;i<p.nInv;i++)s+=DEFS[p.inv[i].def].atk;return s;}
static int  DEFN(const Player&p){int s=p.hab;for(int i=0;i<p.nInv;i++)s+=DEFS[p.inv[i].def].def;return s;}
static int  RES(const Player&p,int type){int s=0;for(int i=0;i<p.nInv;i++){const CardDef&d=DEFS[p.inv[i].def];s+=type==0?d.r0:type==1?d.r1:d.r2;}return s;}
static void mor(Player&p,int d){p.moral=(int8_t)clampi(p.moral+d,0,10);}
static void die(Player&p,const char*cause){if(!p.alive)return;p.alive=0;p.mort=G.jour;snprintf(p.cause,sizeof(p.cause),"%s",cause);}
static void hurt(Player&p,int n,const char*cause){if(n<=0)return;p.pv=(int8_t)(p.pv-n);if(p.pv<=0){p.pv=0;die(p,cause);}}
static void addCond(Player&p,uint8_t c,Msg*m){
  int i=0;while(((1<<i)&c)==0&&i<4)i++;
  if(p.cond&c){p.cd[i]=COND_DAYS[i];return;}
  p.cond|=c;p.cd[i]=COND_DAYS[i];
  if(m)mp(*m,'b',"%s : %s",COND_NAME[i],COND_TXT[i]);
}
static void cureCond(Player&p,uint8_t mask,Msg*m){
  for(int i=0;i<4;i++)if((mask&(1<<i))&&(p.cond&(1<<i))){p.cond&=~(1<<i);p.cd[i]=0;if(m)mp(*m,'g',"%s soigné.",COND_NAME[i]);}
}
static bool wear(Player&p,int invIdx,int n){
  Card&c=p.inv[invIdx];
  if(DEFS[c.def].dur<=0)return false;
  int w100=n*DF().wear100;
  c.dur=(int8_t)(c.dur-(w100/100+(rnd(100)<(w100%100)?1:0)));
  if(c.dur<=0){Card g=c;removeAt(p.inv,p.nInv,invIdx);discard(g);return true;}
  return false;
}
static void wearTag(uint32_t tag){
  Player&p=G.p;
  if(tag==T_FEU&&p.foyer>0)return;                /* un foyer entretenu s'use à la place de l'outil */
  for(int i=0;i<p.nInv;i++)if(DEFS[p.inv[i].def].tags&tag){wear(p,i,1);return;}
}
static void spend(Player&p,int n){p.ap=(uint8_t)maxi(0,p.ap-n);}

/* ---------- saisons, météo ---------- */
static int seasonIdx(){return (G.s0+(G.jour-1)/SEASON_LEN)%4;}
static const SeasonFx& seasonFx(const Player&p){return SEASON_FX[p.env][seasonIdx()];}
static int seasonStress(const Player&p){return seasonFx(p).st+(G.jours?0:mini(2,(G.jour-1)/(SEASON_LEN*4)));}
static uint8_t pickWx(int env){return WX_TABLE[env][rnd(8)];}
static int stressType(){return ENV().stress;}
static int stressNight(const Player&p){
  const EnvDef&e=ENVS[p.env];
  int v=e.niv+WXS[p.wx].st+DF().st+seasonStress(p)-RES(p,e.stress)-p.hab-p.fort-((p.garde&&(tagMask(p)&T_FEU))?1:0);
  return maxi(0,v);
}
static int signalGoal(){return SIGNAL_GOAL-1+(G.diff>=3?1:0);}
static int rescueChance(){int ex=maxi(0,G.signal-signalGoal());return clampi(28+ex*12-(G.diff>=3?8:0),5,85);}

/* ---------- points d'action ---------- */
static int calcAP(const Player&p){
  int a=AP_BASE+DF().ap+WXS[p.wx].ap;
  if(p.ene<6)a-=p.ene>=3?1:p.ene>=1?2:3;
  if(p.cond&CD_FRACTURE)a--;
  if(p.moral<=2)a--;
  return maxi(1,a);
}
static int exploreCost(const Player&p){return 1+WXS[p.wx].expl;}
static void startDay(Msg*m){
  Player&p=G.p;
  p.ap=p.apMax=(uint8_t)calcAP(p);
  if(WXS[p.wx].rain&&(tagMask(p)&T_RECIPIENT)){p.eau=(int8_t)mini(EAU_MAX,p.eau+3);if(m)mp(*m,'g',"Récipients pleins de pluie : eau +3.");}
}

/* ---------- nouvelle partie ---------- */
static void newGame(int diffIdx,int jours){
  memset(&G,0,sizeof(G));
  G.diff=(uint8_t)diffIdx;G.jours=(uint8_t)jours;G.jour=1;G.s0=(uint8_t)rnd(4);G.started=1;
  Player&p=G.p;
  p.env=(uint8_t)rnd(N_ENV);p.alive=1;
  buildDeck();
  const EnvDef&e=ENVS[p.env];
  if(e.kit>=0)p.inv[p.nInv++]=mkCard(e.kit,true);
  while(p.nHand<5){
    Card c;if(!drawCard(c))break;
    const CardDef&d=DEF_OF(c);
    if(isEvent(d)||(d.k==K_CONTRE&&p.nHand<2)){discard(c);continue;}
    p.hand[p.nHand++]=c;
  }
  const DiffDef&D=DF();
  p.pv=(int8_t)maxi(3,pvMax(p)+D.pv);p.sat=(int8_t)(7+D.start);p.eau=(int8_t)(7+D.start);
  p.ene=(int8_t)(8+mini(0,D.start));p.moral=7;
  p.wx=pickWx(p.env);p.wxNext=pickWx(p.env);
  startDay(NULL);
}

/* ---------- récolte ---------- */
struct Water{int n;const char*warn;};
static Water waterYield(const Player&p){
  uint32_t t=tagMask(p);bool rec=t&T_RECIPIENT,feu=t&T_FEU,cout=t&T_COUTEAU;
  int n=0;const char*warn="";
  switch(p.env){
    case E_FORET:n=3;break;
    case E_MARAIS:n=3;if(!feu)warn="non bouillie : risque d'infection";break;
    case E_MONTAGNE:n=2+(rec?1:0);break;
    case E_GLACIER:n=feu?3:1;if(!feu)warn="sans feu, la neige vous glace";break;
    case E_OCEAN:n=rec?1:0;break;
    case E_DESERT:n=cout?2:0;break;
    case E_JUNGLE:n=3;if(!feu)warn="non bouillie : risque de gastro et d'infection";break;
    case E_SAVANE:n=cout?2:1;if(!feu)warn="mare souillée : risque de gastro";break;
    case E_STEPPE:n=2;if(!feu)warn="risque de gastro";break;
    case E_CANYON:n=cout?2:0;break;
    case E_FJORD:n=3;break;
  }
  if(WXS[p.wx].rain&&rec)n+=2;
  Water w;w.n=n;w.warn=warn;return w;
}
enum { CO_BOIS=0,CO_PIERRE,CO_FIBRES,CO_EAU,CO_VIVRES };
static int collectYield(const Player&p,int w){
  const EnvDef&e=ENVS[p.env];
  if(w==CO_EAU)return waterYield(p).n;
  if(w==CO_VIVRES)return clampi(e.forP+((tagMask(p)&T_COUTEAU)?10:0)+seasonFx(p).food,5,95);
  int y=w==CO_BOIS?e.yB:w==CO_PIERRE?e.yP:e.yF;
  return (y>0&&w==CO_BOIS&&(tagMask(p)&T_HACHE))?y+1:y;
}
static bool rawWaterRisk(Msg&m){
  Player&p=G.p;
  if(has(T_FEU))return false;
  if(rnd(100)<RAW_RISK[p.env]){
    if(p.env==E_MARAIS||p.env==E_JUNGLE)addCond(p,CD_INFECTION,&m);
    addCond(p,CD_GASTRO,&m);return true;
  }
  return false;
}
static char doCollect(int w,Msg&m){
  Player&p=G.p;spend(p,1);char tone='g';
  if(w==CO_EAU){
    Water y=waterYield(p);p.eau=(int8_t)mini(EAU_MAX,p.eau+y.n);mp(m,'g',"Eau +%d.",y.n);
    if(y.n>0&&p.env!=E_GLACIER&&p.env!=E_OCEAN&&p.env!=E_MONTAGNE&&rawWaterRisk(m))tone='b';
    if(p.env==E_GLACIER&&!has(T_FEU)){p.ene=(int8_t)maxi(0,p.ene-1);mp(m,'b',"Énergie −1 (froid).");}
  }else if(w==CO_VIVRES){
    const EnvDef&e=ENVS[p.env];
    if(rnd(100)<collectYield(p,CO_VIVRES)){
      int nom=e.forage[rnd(e.nForage)];if(nom>=0)gainCard(nom,1,&m);
      if((p.env==E_FORET||p.env==E_MARAIS)&&(tagMask(p)&T_OUTIL)&&rnd(100)<40){int n2=e.forage[rnd(e.nForage)];if(n2>=0)gainCard(n2,1,&m);}
    }else{mp(m,'b',"Vous ratissez le secteur sans rien trouver.");tone='b';}
  }else{
    int def=w==CO_BOIS?D_BOIS:w==CO_PIERRE?D_PIERRE:D_FIBRES;
    gainCard(def,collectYield(p,w),&m);
  }
  return tone;
}
static void doRest(Msg&m){
  Player&p=G.p;spend(p,1);p.ene=(int8_t)mini(ENE_MAX,p.ene+2);mp(m,'g',"Énergie +2.");
  if(p.hab>=1&&p.pv<pvMax(p)){p.pv++;mp(m,'g',"À l'abri : santé +1.");}
}

/* ---------- fabrication ---------- */
static bool canCraft(const Recipe&r,char*why,int n){
  Player&p=G.p;
  if(r.notEnv&&((r.notEnv>>p.env)&1)){if(why)snprintf(why,n,"impossible dans ce milieu");return false;}
  int nb=matCount(D_BOIS),np=matCount(D_PIERRE),nf=matCount(D_FIBRES),ne=matCount(D_PEAU);
  char need[64]="";
  auto add=[&](int miss,const char*nm){if(miss>0){char t[24];snprintf(t,sizeof(t),"%s%d %s",need[0]?", ":"",miss,nm);strncat(need,t,sizeof(need)-strlen(need)-1);}};
  add(r.bois-nb,"Bois");add(r.pierre-np,"Pierre");add(r.fibres-nf,"Fibres");add(r.peau-ne,"Peau");
  bool toolsOk=(tagMask(p)&r.tools)==r.tools;
  if(!need[0]&&toolsOk)return true;
  if(why){
    if(need[0])snprintf(why,n,"manque : %s",need);
    else snprintf(why,n,"il faut %s",(r.tools&T_FEU)?"du feu":"un outil");
  }
  return false;
}
static void removeMats(int def,int n){
  Player&p=G.p;
  for(int k=0;k<n;k++){int i=findDef(p.hand,p.nHand,def);if(i<0)return;Card c=p.hand[i];removeAt(p.hand,p.nHand,i);discard(c);}
}
static void doCraft(const Recipe&r,Msg&m){
  Player&p=G.p;spend(p,1);
  removeMats(D_BOIS,r.bois);removeMats(D_PIERRE,r.pierre);removeMats(D_FIBRES,r.fibres);removeMats(D_PEAU,r.peau);
  if(r.tools&T_FEU)wearTag(T_FEU);
  Card c=mkCard(r.out,true);
  if(DEFS[r.out].k==K_OBJET&&p.nInv<INV_MAX){p.inv[p.nInv++]=c;mp(m,'g',"%s fabriqué et équipé.",DEFS[r.out].nom);}
  else if(p.nHand<HAND_CAP){p.hand[p.nHand++]=c;mp(m,'g',"%s fabriqué (dans votre main).",DEFS[r.out].nom);}
}

/* ---------- signal ---------- */
static bool canSignal(char*why,int n){
  uint32_t t=tagMask(G.p);
  if(!(t&T_FEU)&&!(t&T_MIROIR)){snprintf(why,n,"il faut du feu ou un miroir");return false;}
  if(matCount(D_BOIS)<2&&!(t&T_MIROIR)){snprintf(why,n,"il faut 2 Bois en main");return false;}
  return true;
}
static void doSignal(Msg&m){
  Player&p=G.p;spend(p,1);
  bool mir=(tagMask(p)&T_MIROIR)!=0;
  wearTag(mir?T_MIROIR:T_FEU);
  if(!mir)removeMats(D_BOIS,2);
  G.signal++;p.sig++;mor(p,1);
  mp(m,'g',"Le signal grandit : %d/%d.",G.signal,signalGoal());
  if(G.signal>=signalGoal()&&!G.watch){G.watch=1;mp(m,'g',"Assez fort : les secours tenteront de vous repérer chaque jour (%d %%).",rescueChance());}
  else if(G.watch)mp(m,'g',"Chance de repérage : %d %% par jour.",rescueChance());
}

/* ---------- cache, renfort, veille, foyer ---------- */
static int cacheMax(const Player&p){return mini(CACHE_CAP,2+p.hab);}
static bool cacheable(const Card&c){const CardDef&d=DEF_OF(c);return d.k!=K_CONTRE&&d.perish==0;}
static int  cacheCount(const Player&p){int k=0;for(int i=0;i<p.nHand;i++)if(cacheable(p.hand[i]))k++;return k;}
static void doStash(int handIdx,Msg&m){
  Player&p=G.p;spend(p,1);Card c=p.hand[handIdx];removeAt(p.hand,p.nHand,handIdx);p.cache[p.nCache++]=c;
  mp(m,'g',"%s est caché : ni volé ni emporté.",DEF_OF(c).nom);
}
static bool doTakeCache(int ci){
  Player&p=G.p;if(p.nHand>=handMax(p))return false;
  p.hand[p.nHand++]=p.cache[ci];removeAt(p.cache,p.nCache,ci);return true;
}
static bool isMat(int def){return def==D_BOIS||def==D_PIERRE||def==D_FIBRES;}
static int  fortMats(const Player&p){int k=0;for(int i=0;i<p.nHand;i++)if(isMat(p.hand[i].def))k++;return k;}
static bool canFort(char*why,int n){
  Player&p=G.p;
  if(p.hab<1){snprintf(why,n,"il faut déjà un abri");return false;}
  if(p.fort>=2){snprintf(why,n,"renfort au maximum (2/2)");return false;}
  if(fortMats(p)<2){snprintf(why,n,"2 matériaux en main (Bois, Pierre, Fibres)");return false;}
  return true;
}
static void doFort(Msg&m){
  Player&p=G.p;spend(p,1);
  for(int k=0;k<2;k++){
    int pick=-1;int order[3]={D_BOIS,D_PIERRE,D_FIBRES};
    for(int o=0;o<3&&pick<0;o++)pick=findDef(p.hand,p.nHand,order[o]);
    if(pick>=0){Card c=p.hand[pick];removeAt(p.hand,p.nHand,pick);discard(c);}
  }
  p.fort++;mp(m,'g',"Abri renforcé : stress de nuit −1 en plus (renfort %d/2). Une tempête peut l'abîmer.",p.fort);
}
static bool canGarde(char*why,int n){
  Player&p=G.p;
  if(p.garde){snprintf(why,n,"veille déjà prévue");return false;}
  if(p.ene<4){snprintf(why,n,"trop fatigué (énergie 4 mini)");return false;}
  return true;
}
static void doGarde(Msg&m){
  Player&p=G.p;spend(p,1);p.garde=1;
  mp(m,'g',"Vous veillerez cette nuit : aucune surprise nocturne%s. Énergie −2 au matin.",(tagMask(p)&T_FEU)?", stress −1 avec le feu":"");
}
static int fireToolIdx(const Player&p){for(int i=0;i<p.nInv;i++)if(DEFS[p.inv[i].def].tags&T_FEU)return i;return -1;}
static bool canFoyer(char*why,int n){
  Player&p=G.p;
  if(p.hab>=3){snprintf(why,n,"le foyer du refuge suffit");return false;}
  if(p.foyer>=3){snprintf(why,n,"foyer plein (3/3)");return false;}
  if(fireToolIdx(p)<0){snprintf(why,n,"il faut un outil à feu en jeu");return false;}
  if(matCount(D_BOIS)<1){snprintf(why,n,"il faut 1 Bois en main");return false;}
  return true;
}
static void doFoyer(Msg&m){
  Player&p=G.p;spend(p,1);removeMats(D_BOIS,1);int was=p.foyer;p.foyer=3;
  mp(m,'g',was?"Foyer ravivé (3/3).":"Le foyer brûle (3/3).");
  mp(m,' ',"Il fuit les bêtes, réchauffe, compte comme feu et n'use plus l'outil.");
}

/* ---------- affût (pêche / chasse), bête blessée ---------- */
#define FISH_MASK ((1<<E_OCEAN)|(1<<E_MARAIS)|(1<<E_JUNGLE)|(1<<E_FJORD)|(1<<E_GLACIER))
enum { AF_PECHE=0, AF_CHASSE=1 };
static int affutTool(int mode){
  Player&p=G.p;uint32_t tag=mode==AF_PECHE?T_CANNE:T_ARME;
  for(int i=0;i<p.nInv;i++)if(DEFS[p.inv[i].def].tags&tag)return i;return -1;
}
static bool affutInfo(int mode,int&chance,char*why,int n){
  Player&p=G.p;int ti=affutTool(mode);
  if(ti<0){snprintf(why,n,mode==AF_PECHE?"il faut une canne ou un filet":"il faut un arc ou une lance");return false;}
  if(mode==AF_PECHE&&!((FISH_MASK>>p.env)&1)){snprintf(why,n,"pas de poisson ici");return false;}
  if(p.ene<2){snprintf(why,n,"trop fatigué (énergie 2 mini)");return false;}
  int ch=(p.env==E_DESERT||p.env==E_GLACIER?38:56)+((DEFS[p.inv[ti].def].tags&T_ARC)?8:0)+((mode==AF_PECHE&&p.wx==W_PLUIE)?8:0)-((p.wx==W_ORAGE||p.wx==W_SABLE||p.wx==W_BLIZZARD)?18:0);
  chance=clampi(ch,15,90);return true;
}
static int woundedPower(){return 2+rnd(3)+(G.diff>=3?1:0);}
/* retourne la force de la bête si elle se retourne (>0), sinon 0 */
static int doAffut(int mode,Msg&m,char&tone){
  Player&p=G.p;int ch=0;char w[8];affutInfo(mode,ch,w,8);
  int ti=affutTool(mode);const CardDef tool=DEFS[p.inv[ti].def];
  spend(p,1);p.ene=(int8_t)maxi(0,p.ene-1);
  tone=' ';
  if(rnd(100)<ch){
    if(mode==AF_CHASSE&&rnd(100)<((tool.tags&T_ARC)?18:26)){
      wear(p,ti,1);mp(m,'b',"Touchée, mais pas abattue : la bête se retourne !");tone='b';return woundedPower();
    }
    int d=mode==AF_PECHE?D_POISSON:D_GIBIER;gainCard(d,1,&m);tone='g';
  }else mp(m,'b',mode==AF_PECHE?"Rien ne mord. Le fil reste mou.":"Rien ne bouge. La piste est vide.");
  if(ti<p.nInv&&DEFS[p.inv[ti].def].tags==tool.tags&&wear(p,ti,1))mp(m,'b',"%s est hors d'usage.",tool.nom);
  mp(m,' ',"Énergie −1.");
  return 0;
}
static char resolveWounded(int power,bool finish,Msg&m){
  Player&p=G.p;
  if(!finish){p.moral=(int8_t)clampi(p.moral,0,10);mp(m,'b',"Vous lâchez prise. La bête disparaît avec votre prise.");return 'b';}
  int a=ATK(p)+rnd(3);
  for(int i=p.nInv-1;i>=0;i--)if(DEFS[p.inv[i].def].atk>0&&DEFS[p.inv[i].def].dur>0)wear(p,i,1);
  if(a>=power){mp(m,'g',"Vous l'achevez avant qu'elle ne vous touche.");gainCard(D_GIBIER,1,&m);if(rnd(2))gainCard(D_PEAU,1,&m);return 'g';}
  if(a==power-1){
    int d=maxi(0,power-1-DEFN(p));
    if(d)mp(m,'b',"Vous l'achevez, mais elle vous griffe : −%d PV.",d);else mp(m,'g',"Vous l'achevez de justesse, sans une égratignure.");
    gainCard(D_GIBIER,1,&m);if(d){hurt(p,d,"bête blessée");if(p.alive&&d>=3)addCond(p,CD_SAIGNEMENT,&m);}
    return d?'b':'g';
  }
  int d=maxi(1,power-DEFN(p));mp(m,'b',"Elle vous charge et s'échappe : −%d PV.",d);hurt(p,d,"bête blessée");
  if(p.alive&&d>=3)addCond(p,CD_SAIGNEMENT,&m);
  return 'b';
}

/* ---------- fumage, séchage, collet, réparation ---------- */
static int smokeTarget(int def){return def==D_POISSON?D_POISSON_FUME:def==D_GIBIER?D_GIBIER_FUME:-1;}
static int smokeCount(const Player&p){int k=0;for(int i=0;i<p.nHand;i++)if(smokeTarget(p.hand[i].def)>=0&&k<4)k++;return k;}
static int smokerIdx(const Player&p){for(int i=0;i<p.nInv;i++)if(DEFS[p.inv[i].def].tags&T_FUMOIR)return i;return -1;}
static bool canSmoke(char*why,int n){
  Player&p=G.p;
  if(smokerIdx(p)<0){snprintf(why,n,"il faut un Fumoir en jeu");return false;}
  if(!has(T_FEU)){snprintf(why,n,"il faut du feu ou un foyer");return false;}
  if(!smokeCount(p)){snprintf(why,n,"aucun Poisson ni Gibier frais");return false;}
  return true;
}
static void doSmoke(Msg&m){
  Player&p=G.p;spend(p,1);wearTag(T_FEU);
  int done=0;
  for(int i=0;i<p.nHand&&done<4;i++){
    int t=smokeTarget(p.hand[i].def);
    if(t>=0){mp(m,'g',"%s → %s.",DEFS[p.hand[i].def].nom,DEFS[t].nom);p.hand[i]=mkCard(t,true);done++;}
  }
  int si=smokerIdx(p);if(si>=0&&wear(p,si,1))mp(m,'b',"Le Fumoir est hors d'usage.");
  mp(m,'g',"Ça se garde : plus de pourriture.");
}
static bool canDry(const Card&c){return DEF_OF(c).dry>=0&&has(T_FEU)&&G.p.ap>=1;}
static void doDry(int handIdx,Msg&m){
  Player&p=G.p;spend(p,1);wearTag(T_FEU);Card c=p.hand[handIdx];int to=DEF_OF(c).dry;
  removeAt(p.hand,p.nHand,handIdx);discard(c);
  if(to>=0&&p.nHand<HAND_CAP)p.hand[p.nHand++]=mkCard(to,true);
  mp(m,'g',"%s séché : %s se conserve.",DEF_OF(c).nom,to>=0?DEFS[to].nom:"?");
}
static void doTrap(int invIdx,Msg&m){Player&p=G.p;spend(p,1);p.inv[invIdx].fl|=FL_SET;mp(m,' ',"%s tendu pour la nuit.",DEF_OF(p.inv[invIdx]).nom);}
static int cheapestMatIdx(const Player&p){
  int order[4]={D_BOIS,D_PIERRE,D_FIBRES,D_PEAU};
  for(int o=0;o<4;o++){int i=findDef(p.hand,p.nHand,order[o]);if(i>=0)return i;}
  return -1;
}
static bool canRepair(const Card&c){
  Player&p=G.p;const CardDef&d=DEF_OF(c);
  return d.dur>0&&c.dur<d.dur&&(tagMask(p)&T_OUTIL)&&cheapestMatIdx(p)>=0&&p.ap>=1;
}
static void doRepair(int invIdx,Msg&m){
  Player&p=G.p;spend(p,1);int mi=cheapestMatIdx(p);Card mat=p.hand[mi];removeAt(p.hand,p.nHand,mi);discard(mat);
  Card&c=p.inv[invIdx];int before=c.dur;c.dur=(int8_t)mini(DEF_OF(c).dur,c.dur+3);
  mp(m,'g',"%s réparé avec %s : %d → %d.",DEF_OF(c).nom,DEFS[mat.def].nom,before,c.dur);
}

/* ---------- jouer une carte ---------- */
static const char* canPlay(const Card&c){
  Player&p=G.p;const CardDef&d=DEF_OF(c);
  if(d.k==K_MAT)return "Sert à fabriquer, réparer, signaler.";
  if(d.k==K_CONTRE){return (d.cure&&(d.cure&p.cond))?NULL:"Se joue en réaction à un aléa.";}
  if(d.k==K_OBJET)return p.nInv>=INV_MAX?"Inventaire plein.":NULL;
  if(d.req&&((tagMask(p)&d.req)!=d.req))return (d.req&T_FEU)?"Il faut du feu.":"Il manque un outil.";
  if(d.k==K_SOIN){
    bool useful=(d.pv&&p.pv<pvMax(p))||(d.ene&&p.ene<ENE_MAX)||(d.moral&&p.moral<10)||(d.cure&p.cond);
    if(!useful)return "Rien à soigner.";
  }
  if(d.k==K_FOOD){
    bool useful=(d.sat&&p.sat<SAT_MAX)||(d.eau&&p.eau<EAU_MAX);
    if(!useful)return "Pas nécessaire maintenant.";
  }
  if(d.k==K_HABITAT){
    if(p.hab>=d.lvl)return "Niveau déjà atteint.";
    if(p.hab<d.need)return "Il faut d'abord le niveau inférieur.";
    if(p.nHand-1<d.cost)return "Cartes à défausser insuffisantes.";
    if(p.ap<2)return "Construire coûte 2 PA.";
  }
  return NULL;
}
/* discards : indices de main à défausser (habitat de coût > 0) */
static void playCard(int handIdx,const int*discards,int nd,Msg&m){
  Player&p=G.p;Card c=p.hand[handIdx];const CardDef&d=DEF_OF(c);
  removeAt(p.hand,p.nHand,handIdx);
  if(d.k==K_OBJET){p.inv[p.nInv++]=c;mp(m,'g',"%s équipé.",d.nom);return;}
  if(d.k==K_CONTRE){cureCond(p,d.cure,&m);discard(c);return;}
  if(d.req&T_FEU)wearTag(T_FEU);
  if(d.k==K_FOOD){
    char b[48]="";
    if(d.sat){p.sat=(int8_t)mini(SAT_MAX,p.sat+d.sat);snprintf(b+strlen(b),48-strlen(b),"faim +%d ",d.sat);}
    if(d.eau){p.eau=(int8_t)mini(EAU_MAX,p.eau+d.eau);snprintf(b+strlen(b),48-strlen(b),"eau +%d ",d.eau);}
    if(d.pv){p.pv=(int8_t)mini(pvMax(p),p.pv+d.pv);snprintf(b+strlen(b),48-strlen(b),"santé +%d",d.pv);}
    mp(m,'g',"%s : %s",d.nom,b);
  }
  if(d.k==K_SOIN){
    if(d.pv)p.pv=(int8_t)mini(pvMax(p),p.pv+d.pv);
    if(d.ene)p.ene=(int8_t)mini(ENE_MAX,p.ene+d.ene);
    if(d.moral)mor(p,d.moral);
    cureCond(p,d.cure,&m);mp(m,'g',"%s utilisé.",d.nom);
  }
  if(d.k==K_HABITAT){
    spend(p,2);
    /* défausse par indices décroissants, en tenant compte du retrait déjà fait */
    int tmp[8];int n=mini(nd,8);for(int i=0;i<n;i++)tmp[i]=discards[i]>handIdx?discards[i]-1:discards[i];
    for(int a=0;a<n;a++)for(int b2=a+1;b2<n;b2++)if(tmp[b2]>tmp[a]){int t=tmp[a];tmp[a]=tmp[b2];tmp[b2]=t;}
    for(int i=0;i<n;i++){if(tmp[i]>=0&&tmp[i]<p.nHand){Card x=p.hand[tmp[i]];removeAt(p.hand,p.nHand,tmp[i]);discard(x);}}
    p.hab=d.lvl;p.pv=(int8_t)mini(pvMax(p),p.pv+2);mp(m,'g',"%s construit : santé max %d.",d.nom,pvMax(p));
  }
  discard(c);
}

/* ---------- menaces ---------- */
struct Counter{int where;int idx;const char*label;};   /* where : 1 habitat, 2 équipement, 3 main */
static bool findCounter(const CardDef&d,Counter&out){
  Player&p=G.p;uint32_t mask=d.link;int best=9;
  for(int b=0;b<32;b++){
    uint32_t tag=1u<<b;if(!(mask&tag))continue;
    if(best>1&&((tag==T_ABRI&&p.hab>=1)||(tag==T_SOLIDE&&p.hab>=2)||(tag==T_FEU&&p.hab>=3))){out.where=1;out.idx=-1;out.label=HAB_NAME[p.hab];best=1;}
    if(best>2)for(int i=0;i<p.nInv;i++)if(DEFS[p.inv[i].def].tags&tag){out.where=2;out.idx=i;out.label=DEFS[p.inv[i].def].nom;best=2;break;}
    if(best>3)for(int i=0;i<p.nHand;i++){const CardDef&h=DEF_OF(p.hand[i]);if(h.k!=K_OBJET&&h.k!=K_MAT&&h.k!=K_HABITAT&&(h.tags&tag)){out.where=3;out.idx=i;out.label=h.nom;best=3;break;}}
  }
  return best<9;
}
static void useCounter(const Counter&c){
  Player&p=G.p;
  if(c.where==2)wear(p,c.idx,1);
  if(c.where==3){Card x=p.hand[c.idx];removeAt(p.hand,p.nHand,c.idx);discard(x);}
}
static int predPower(const CardDef&d){return d.power+DF().pw;}
static int catcherIdx(const CardDef&d){Player&p=G.p;for(int i=0;i<p.nInv;i++)if(DEFS[p.inv[i].def].tags&d.link)return i;return -1;}
enum { CH_COUNTER=1,CH_FIGHT,CH_ENDURE,CH_HUNT,CH_LET };
static char resolveThreat(const Card&t,int ch,Msg&m){
  Player&p=G.p;const CardDef&d=DEF_OF(t);char tone=' ';
  if(d.k==K_PRED){
    if(ch==CH_COUNTER){Counter c;if(findCounter(d,c)){useCounter(c);mp(m,'g',"%s recule : %s.",d.nom,c.label);tone='g';}}
    else if(ch==CH_FIGHT){
      int a=ATK(p);for(int i=p.nInv-1;i>=0;i--)if(DEFS[p.inv[i].def].atk>0&&DEFS[p.inv[i].def].dur>0)wear(p,i,1);
      if(a>=predPower(d)){mp(m,'g',"Vous terrassez %s.",d.nom);gainCard(D_GIBIER,1,&m);gainCard(D_PEAU,1,&m);tone='g';}
      else{int dm=maxi(1,predPower(d)-DEFN(p));mp(m,'b',"%s vous blesse : −%d PV.",d.nom,dm);if(dm>=3)addCond(p,CD_SAIGNEMENT,&m);hurt(p,dm,d.nom);tone='b';}
    }else{
      int dm=maxi(0,predPower(d)-DEFN(p));
      if(dm)mp(m,'b',"Vous encaissez %s : −%d PV.",d.nom,dm);else mp(m,'g',"Votre défense tient. %s s'en va.",d.nom);
      if(dm>=3)addCond(p,CD_SAIGNEMENT,&m);hurt(p,dm,d.nom);tone=dm?'b':'g';
    }
  }
  if(d.k==K_PROIE){
    if(ch==CH_HUNT){
      int ci=catcherIdx(d);
      if(ci>=0){mp(m,'g',"%s pris avec %s.",d.nom,DEFS[p.inv[ci].def].nom);wear(p,ci,1);}
      if(d.loot>=0)gainCard(d.loot,d.lootN,&m);if(d.extra>=0)gainCard(d.extra,1,&m);tone='g';
    }else mp(m,' ',"%s file dans les broussailles.",d.nom);
  }
  if(d.k==K_MALUS){
    if(ch==CH_COUNTER){Counter c;if(findCounter(d,c)){useCounter(c);mp(m,'g',"%s contré : %s.",d.nom,c.label);tone='g';}}
    else{
      tone='b';
      if(d.pv)mp(m,'b',"%s : −%d PV.",d.nom,-d.pv);
      if(d.sat){p.sat=(int8_t)maxi(0,p.sat+d.sat);mp(m,'b',"Faim %d.",d.sat);}
      if(d.eau){p.eau=(int8_t)maxi(0,p.eau+d.eau);mp(m,'b',"Eau %d.",d.eau);}
      if(d.ene){p.ene=(int8_t)clampi(p.ene+d.ene,0,ENE_MAX);mp(m,'b',"Énergie %d.",d.ene);}
      if(d.cond)addCond(p,d.cond,&m);
      if(d.lose==1&&p.nHand){int i=rnd(p.nHand);Card c=p.hand[i];removeAt(p.hand,p.nHand,i);discard(c);mp(m,'b',"Perdu : %s.",DEF_OF(c).nom);}
      if(d.lose==2){int f[HAND_CAP],n=0;for(int i=0;i<p.nHand;i++)if(DEF_OF(p.hand[i]).k==K_FOOD)f[n++]=i;if(n){int i=f[rnd(n)];Card c=p.hand[i];removeAt(p.hand,p.nHand,i);discard(c);mp(m,'b',"Vivres perdus : %s.",DEF_OF(c).nom);}}
      if(d.lose==3&&p.nInv){int i=rnd(p.nInv);Card c=p.inv[i];removeAt(p.inv,p.nInv,i);discard(c);mp(m,'b',"Emporté : %s.",DEF_OF(c).nom);}
      if(d.pv)hurt(p,-d.pv,d.nom);
    }
  }
  discard(t);
  return tone;
}
static void resolveChance(const Card&c,Msg&m){
  Player&p=G.p;const CardDef&d=DEF_OF(c);
  if(d.eau){p.eau=(int8_t)mini(EAU_MAX,p.eau+d.eau);mp(m,'g',"Eau +%d.",d.eau);}
  if(d.sat){p.sat=(int8_t)mini(SAT_MAX,p.sat+d.sat);mp(m,'g',"Faim +%d.",d.sat);}
  if(d.ene){p.ene=(int8_t)mini(ENE_MAX,p.ene+d.ene);mp(m,'g',"Énergie +%d.",d.ene);}
  if(d.pv){p.pv=(int8_t)mini(pvMax(p),p.pv+d.pv);mp(m,'g',"Santé +%d.",d.pv);}
  if(d.moral){mor(p,d.moral);mp(m,'g',"Moral +%d.",d.moral);}
  if(d.gain0>=0)gainCard(d.gain0,1,&m);
  if(d.gain1>=0)gainCard(d.gain1,1,&m);
  discard(c);
}

/* ---------- nuit ---------- */
static int nightEvents(Msg&m){
  Player&p=G.p;
  if(p.garde){
    p.garde=0;p.ene=(int8_t)maxi(0,p.ene-2);if(tagMask(p)&T_FEU)wearTag(T_FEU);
    mp(m,' ',"Vous avez veillé : rien n'a pu vous surprendre. Énergie −2.");return 0;
  }
  bool hell=G.diff>=3,fire=(tagMask(p)&T_FEU)!=0;
  int ch=17+(hell?9:0)+(G.diff==0?-10:0)-(fire?10:0)-(p.hab>=2?8:0)-(p.hab>=1?4:0);
  if(rnd(100)>=ch){if(rnd(100)<10){mp(m,'g',"Nuit claire et étoilée : le moral remonte.");mor(p,1);}return 0;}
  int r=rnd(3),bad=0;
  if(r==0){
    if(fire){mp(m,'g',"Des yeux brillent à la lisière, mais le feu les tient à distance.");wearTag(T_FEU);}
    else{
      int dm=maxi(0,1+rnd(2)+(hell?1:0)-DEFN(p)/2);
      if(dm){mp(m,'b',"Un rôdeur s'approche pendant votre sommeil : −%d PV.",dm);hurt(p,dm,"rôdeur nocturne");bad=1;}
      else mp(m,' ',"Un rôdeur tourne autour de l'abri, sans oser entrer.");
    }
  }else if(r==1){
    int fi=-1;for(int i=0;i<p.nInv;i++)if((DEFS[p.inv[i].def].tags&T_FEU)&&DEFS[p.inv[i].def].dur>0){fi=i;break;}
    if(fi>=0){char nom[40];snprintf(nom,sizeof(nom),"%s",DEFS[p.inv[fi].def].nom);bool gone=wear(p,fi,1);mp(m,'b',gone?"Le vent achève votre feu : %s est hors d'usage.":"Le vent attaque votre feu : %s s'use davantage.",nom);bad=1;}
    else if(p.hab>=3)mp(m,'g',"Le vent hurle autour du refuge, mais le foyer tient bon.");
    else{mp(m,'b',"Une nuit sans feu : le froid s'insinue.");if(rnd(2))p.ene=(int8_t)maxi(0,p.ene-1);bad=1;}
  }else{mp(m,'b',"Nuit agitée : bruits, ombres, mauvais sommeil.");bad=1;}
  return bad;
}
static void endDay(Msg&m){
  Player&p=G.p;const EnvDef&e=ENVS[p.env];const WxDef&w=WXS[p.wx];
  /* collets et filets tendus */
  for(int i=p.nInv-1;i>=0;i--){
    Card&c=p.inv[i];if(!(c.fl&FL_SET))continue;
    const CardDef&d=DEF_OF(c);c.fl&=~FL_SET;
    int base=(p.env==E_DESERT||p.env==E_GLACIER)?35:55;
    if(rnd(100)<base){
      bool fish=(d.tags&T_CANNE)&&((FISH_MASK>>p.env)&1);
      char nom[40];snprintf(nom,sizeof(nom),"%s",d.nom);
      gainCard(fish?D_POISSON:D_GIBIER,1,NULL);mp(m,'g',"%s : une prise cette nuit (%s).",nom,fish?"Poisson":"Gibier");
      wear(p,i,1);
    }else mp(m,' ',"%s : rien cette nuit.",d.nom);
  }
  int sd=stressNight(p);
  if(p.cond&CD_GASTRO){p.eau=(int8_t)maxi(0,p.eau-2);mp(m,'b',"Gastro-entérite : eau −2.");}
  if(sd){mp(m,'b',"%s%s%s : −%d PV.",STRESS_NAME[e.stress],w.st?" (":"",w.st?w.nom:"",sd);hurt(p,sd,STRESS_NAME[e.stress]);if(sd>=2)p.ene=(int8_t)maxi(0,p.ene-1);}
  else mp(m,'g',"%s : vous êtes protégé.",STRESS_NAME[e.stress]);
  int md=0;
  if(p.alive){if(nightEvents(m))md--;}
  if(p.alive&&p.foyer>0){
    bool wet=(p.wx==W_PLUIE||p.wx==W_ORAGE||p.wx==W_BLIZZARD||p.wx==W_VENT)&&p.hab<2;
    p.foyer=(uint8_t)maxi(0,p.foyer-(wet?2:1));
    if(p.foyer)mp(m,' ',"Les braises tiennent (foyer %d/3).",p.foyer);
    else mp(m,'b',wet?"%s : le foyer est noyé.":"Le foyer s'éteint faute d'entretien.",w.nom);
  }
  if(p.alive&&p.fort>0&&(p.wx==W_ORAGE||p.wx==W_VENT||p.wx==W_BLIZZARD||p.wx==W_SABLE)){p.fort--;mp(m,'b',"%s : une partie du renfort cède (renfort %d/2).",w.nom,p.fort);}
  /* passifs : citerne, jardin */
  if(p.alive)for(int i=p.nInv-1;i>=0;i--){
    const CardDef&d=DEF_OF(p.inv[i]);if(!d.passif)continue;
    if(d.passif==1){int g=1+(w.rain?1:0);p.eau=(int8_t)mini(EAU_MAX,p.eau+g);mp(m,'g',"Citerne : eau +%d.",g);}
    if(d.passif==2&&rnd(100)<55){gainCard(rnd(2)?D_RACINES:D_BAIES_SAUVAGES,1,NULL);mp(m,'g',"Jardin : une récolte.");}
    if(wear(p,i,1))mp(m,'b',"%s est hors d'usage.",d.nom);
  }
  if(p.alive){
    for(int i=p.nInv-1;i>=0;i--){const CardDef&d=DEF_OF(p.inv[i]);int r=e.stress==0?d.r0:e.stress==1?d.r1:d.r2;if(r>0){char nom[40];snprintf(nom,sizeof(nom),"%s",d.nom);if(wear(p,i,1))mp(m,'b',"%s est hors d'usage.",nom);}}
    int fd=e.faim+DF().drain;p.sat=(int8_t)(p.sat-fd);
    if(p.sat<=0){p.sat=0;mp(m,'b',"Le ventre vide : −2 PV.");hurt(p,2,"faim");md-=2;}else mp(m,' ',"Faim −%d.",fd);
  }
  if(p.alive){
    int d=maxi(0,e.soif+w.eau+DF().drain+seasonFx(p).eau);p.eau=(int8_t)(p.eau-d);
    if(p.eau<=0){p.eau=0;mp(m,'b',"La gorge sèche : −3 PV.");hurt(p,3,"soif");md-=2;}else if(d)mp(m,' ',"Soif −%d.",d);
  }
  if(p.alive){
    if(p.cond&CD_SAIGNEMENT){mp(m,'b',"Saignement : −1 PV.");hurt(p,1,"hémorragie");}
    if(p.alive&&(p.cond&CD_INFECTION)){mp(m,'b',"Infection : −1 PV.");hurt(p,1,"infection");}
    if(p.alive)for(int i=0;i<4;i++)if(p.cond&(1<<i)){if(--p.cd[i]<=0){p.cond&=~(1<<i);mp(m,'g',"%s : guéri de lui-même.",COND_NAME[i]);}}
  }
  if(p.alive&&!p.cond&&p.sat>=6&&p.eau>=6&&p.pv<pvMax(p)){p.pv++;mp(m,'g',"Bien nourri et hydraté : santé +1.");}
  if(p.alive){
    if(p.sat>=5&&p.eau>=5&&p.hab>=1)md++;
    if(sd>=2)md--;
    if(p.cond)md--;
    int m0=p.moral;mor(p,md);
    if(p.moral!=m0)mp(m,p.moral>m0?'g':'b',"Moral %d/10 (%+d).",p.moral,p.moral-m0);
    if(p.moral<=0){mp(m,'b',"Le désespoir vous ronge : −1 PV.");hurt(p,1,"désespoir");}
    int used=p.apMax-p.ap;
    int rec=2+p.hab+(sd>=2?-1:0)+(p.moral>=8?1:p.moral<=3?-1:0);
    p.ene=(int8_t)clampi(p.ene-used+rec,0,ENE_MAX);
    mp(m,' ',"Sommeil : énergie %+d.",rec-used);
    if(p.ene<=0){mp(m,'b',"Épuisement : −1 PV.");hurt(p,1,"épuisement");}
  }
  if(p.alive){
    int keep=((tagMask(p)&T_RECIPIENT)?1:0)+(p.hab>=2?1:0)+((tagMask(p)&T_FUMOIR)?1:0);
    for(int i=p.nHand-1;i>=0;i--){
      const CardDef&d=DEF_OF(p.hand[i]);if(!d.perish)continue;
      p.hand[i].age++;
      if(p.hand[i].age>d.perish+keep){Card c=p.hand[i];removeAt(p.hand,p.nHand,i);discard(c);mp(m,'b',"%s a pourri.",d.nom);}
    }
    for(int i=p.nInv-1;i>=0;i--)if(DEF_OF(p.inv[i]).burn){char nom[40];snprintf(nom,sizeof(nom),"%s",DEF_OF(p.inv[i]).nom);if(wear(p,i,1))mp(m,' ',"%s s'est consumé.",nom);}
    p.wx=p.wxNext;p.wxNext=pickWx(p.env);
  }
}
/* passe au jour suivant ; renvoie les messages du matin */
static void nextDay(Msg&m){
  Player&p=G.p;
  if(!p.alive){G.over=1;return;}
  G.jour++;
  if(G.jour>1&&(G.jour-1)%SEASON_LEN==0)mp(m,' ',"Nouvelle saison : %s. %s",SEASON_NAME[seasonIdx()],seasonFx(p).txt);
  if(G.watch&&!G.rescue){
    if(rnd(100)<rescueChance()){G.rescue=G.jour+1;mp(m,'g',"Un %s a repéré votre signal ! Les secours arrivent demain.",CARRIER[p.env]);}
    else{G.signal=(uint8_t)maxi(0,G.signal-2);if(G.signal<signalGoal())G.watch=0;mp(m,'b',"Un %s est passé sans vous voir. Le signal s'étiole (%d/%d).",CARRIER[p.env],G.signal,signalGoal());mor(p,-1);}
  }
  if(G.rescue&&G.jour>=G.rescue){G.over=1;G.rescued=1;return;}
  if(G.jours&&G.jour>G.jours){G.over=1;return;}
  startDay(&m);
}
static int scoreOf(const Player&p){return p.pv*2+p.sat+p.eau+p.ene+p.hab*5+p.nInv+p.sig*2;}
/* ===== C. INTERFACE M5Cardputer Adv (écran 240x135, clavier 56 touches) ===== */
#include <M5Cardputer.h>
#include <Preferences.h>
#include <functional>

static M5Canvas cv(&M5Cardputer.Display);
static Preferences prefs;
static bool gSound=true;static uint8_t gBright=70;static uint16_t gBest=0;
static uint32_t hwrand(){return esp_random();}

#define SW 240
#define SH 135
static uint16_t C_BG,C_FG,C_DIM,C_ACC,C_GOOD,C_BAD,C_BAR,C_SEL,C_WARN;
static void initColors(){
  C_BG=cv.color565(14,16,14);C_FG=cv.color565(226,222,206);C_DIM=cv.color565(122,124,112);
  C_ACC=cv.color565(214,160,70);C_GOOD=cv.color565(110,200,120);C_BAD=cv.color565(226,96,84);
  C_BAR=cv.color565(40,44,38);C_SEL=cv.color565(58,52,34);C_WARN=cv.color565(230,200,80);
}
static uint16_t toneCol(char t){return t=='g'?C_GOOD:t=='b'?C_BAD:C_FG;}

/* ---- texte : la police efont n'a pas tous les symboles ---- */
static const char* clean(const char*s){
  static char b[200];int j=0;
  for(int i=0;s[i]&&j<198;){
    const uint8_t c=(uint8_t)s[i];
    if(c==0xE2&&(uint8_t)s[i+1]==0x88&&(uint8_t)s[i+2]==0x92){b[j++]='-';i+=3;}          /* − */
    else if(c==0xE2&&(uint8_t)s[i+1]==0x86&&(uint8_t)s[i+2]==0x92){b[j++]='>';i+=3;}     /* → */
    else if(c==0xE2&&(uint8_t)s[i+1]==0x97&&(uint8_t)s[i+2]==0x8F){b[j++]='*';i+=3;}     /* ● */
    else if(c==0xC5&&(uint8_t)s[i+1]==0x93){b[j++]='o';b[j++]='e';i+=2;}                 /* œ */
    else if(c==0xC5&&(uint8_t)s[i+1]==0x92){b[j++]='O';b[j++]='e';i+=2;}                 /* Œ */
    else b[j++]=s[i++];
  }
  b[j]=0;return b;
}
static void T(int x,int y,const char*s,uint16_t col){cv.setTextColor(col,C_BG);cv.drawString(clean(s),x,y);}
static void TC(int x,int y,const char*s,uint16_t col,uint16_t bg){cv.setTextColor(col,bg);cv.drawString(clean(s),x,y);}
static int wrapLines(const char*s,int w,char out[][64],int maxL){
  const char*t=clean(s);int n=0;char cur[64]="";int cl=0;
  while(*t&&n<maxL){
    const char*e=t;while(*e&&*e!=' ')e++;
    char word[48];int wl=(int)(e-t);if(wl>47)wl=47;memcpy(word,t,wl);word[wl]=0;
    char test[64];snprintf(test,sizeof(test),"%s%s%s",cur,cl?" ":"",word);
    if(cl&&cv.textWidth(test)>w){memcpy(out[n],cur,cl+1);n++;cur[0]=0;cl=0;continue;}
    snprintf(cur,sizeof(cur),"%s",test);cl=(int)strlen(cur);
    t=*e?e+1:e;
  }
  if(cl&&n<maxL){memcpy(out[n],cur,cl+1);n++;}
  return n;
}
static void drawWrap(int x,int y,int w,int maxL,const char*s,uint16_t col){
  char L[6][64];int n=wrapLines(s,w,L,mini(maxL,6));
  for(int i=0;i<n;i++)T(x,y+i*11,L[i],col);
}

/* ---- sons ---- */
static void snd(int k){
  if(!gSound)return;
  switch(k){
    case 0:M5Cardputer.Speaker.tone(1800,15);break;                  /* navigation */
    case 1:M5Cardputer.Speaker.tone(2400,40);break;                  /* valider */
    case 2:M5Cardputer.Speaker.tone(500,120);break;                  /* mauvais */
    case 3:M5Cardputer.Speaker.tone(1500,80);delay(90);M5Cardputer.Speaker.tone(2000,100);break;
    case 4:M5Cardputer.Speaker.tone(300,300);break;
  }
}

/* ---- clavier ---- */
enum { KY_NONE=0,KY_UP,KY_DN,KY_LF,KY_RT,KY_OK,KY_BK,KY_NUM0=100 };
static int readKey(){
  M5Cardputer.update();
  if(!M5Cardputer.Keyboard.isChange()||!M5Cardputer.Keyboard.isPressed())return KY_NONE;
  auto st=M5Cardputer.Keyboard.keysState();
  if(st.enter||st.space)return KY_OK;
  if(st.del)return KY_BK;
  for(char c:st.word){
    switch(c){
      case ';':case 'w':case 'W':return KY_UP;
      case '.':case 's':case 'S':return KY_DN;
      case ',':case 'a':case 'A':return KY_LF;
      case '/':case 'd':case 'D':return KY_RT;
      case '`':case 'q':case 'Q':return KY_BK;
      case 'e':case 'E':return KY_OK;
      default:if(c>='0'&&c<='9')return KY_NUM0+(c-'0');
    }
  }
  return KY_NONE;
}
static int waitKey(){int k;do{k=readKey();delay(8);}while(!k);return k;}

/* ---- jauges ---- */
static void bar(int x,int y,int w,int v,int mx,uint16_t col){
  cv.fillRect(x,y,w,7,C_BAR);
  if(v>0)cv.fillRect(x,y,(w*v)/mx,7,col);
}
static const char* weatherShort(int w){return WXS[w].nom;}

/* ---- menu générique ---- */
struct Item{char label[44];char info[96];bool ok;char mark;};
typedef std::function<void(int,Item&)> ItemFn;
static void header(const char*title){
  cv.fillRect(0,0,SW,14,C_BAR);T(3,1,title,C_ACC);
  int pct=M5Cardputer.Power.getBatteryLevel();char b[8];snprintf(b,sizeof(b),"%d%%",pct);
  T(SW-cv.textWidth(b)-3,1,b,C_DIM);
}
static int menu(const char*title,int n,ItemFn fn,int sel=0,const char*hint=NULL){
  if(n<=0)return -1;
  int top=0;sel=clampi(sel,0,n-1);
  for(;;){
    cv.fillSprite(C_BG);header(title);
    const int rows=6;if(sel<top)top=sel;if(sel>=top+rows)top=sel-rows+1;
    for(int r=0;r<rows&&top+r<n;r++){
      int i=top+r;Item it;it.label[0]=0;it.info[0]=0;it.ok=true;it.mark=0;fn(i,it);
      int y=16+r*13;
      if(i==sel)cv.fillRect(0,y-1,SW,13,C_SEL);
      uint16_t col=it.ok?C_FG:C_DIM;
      TC(4,y,it.label,col,i==sel?C_SEL:C_BG);
      if(it.mark)TC(SW-12,y,"*",it.mark=='g'?C_GOOD:C_WARN,i==sel?C_SEL:C_BG);
    }
    if(n>rows){int bh=(rows*80)/n+4;int by=16+(top*(80-bh))/maxi(1,n-rows);cv.fillRect(SW-3,by,2,bh,C_DIM);}
    cv.drawFastHLine(0,96,SW,C_BAR);
    Item cur;cur.label[0]=0;cur.info[0]=0;cur.ok=true;cur.mark=0;fn(sel,cur);
    drawWrap(4,99,SW-8,3,cur.info[0]?cur.info:(hint?hint:""),cur.ok?C_FG:C_WARN);
    cv.pushSprite(0,0);
    int k=waitKey();
    if(k==KY_UP){sel=(sel+n-1)%n;snd(0);}
    else if(k==KY_DN){sel=(sel+1)%n;snd(0);}
    else if(k==KY_OK){snd(1);return sel;}
    else if(k==KY_BK){return -1;}
    else if(k>=KY_NUM0+1&&k<=KY_NUM0+9&&k-KY_NUM0<=n){sel=k-KY_NUM0-1;snd(1);return sel;}
  }
}
/* menu à libellés fixes (aucune désactivation) */
static int simpleMenu(const char*title,int n,const char*const*labels,const char*const*infos=NULL,int sel=0){
  return menu(title,n,[&](int i,Item&it){snprintf(it.label,44,"%s",labels[i]);if(infos)snprintf(it.info,96,"%s",infos[i]);},sel);
}

/* ---- messages (défilement) ---- */
static void showMsg(const char*title,Msg&m){
  if(!m.n)return;
  static char L[60][64];static char col[60];int nl=0;
  for(int i=0;i<m.n&&nl<56;i++){
    char tmp[6][64];int k=wrapLines(m.t[i],SW-12,tmp,4);
    for(int j=0;j<k&&nl<60;j++){snprintf(L[nl],64,"%s%s",j?"  ":"",tmp[j]);col[nl]=m.c[i];nl++;}
  }
  int top=0;const int rows=9;bool bad=false;for(int i=0;i<m.n;i++)if(m.c[i]=='b')bad=true;
  snd(bad?2:3);
  for(;;){
    cv.fillSprite(C_BG);header(title);
    for(int r=0;r<rows&&top+r<nl;r++)T(4,16+r*12,L[top+r],toneCol(col[top+r]));
    if(nl>rows)T(SW-24,SH-12,top+rows<nl?"v":"",C_DIM);
    T(4,SH-12,"OK : continuer",C_DIM);
    cv.pushSprite(0,0);
    int k=waitKey();
    if(k==KY_DN&&top+rows<nl)top++;else if(k==KY_UP&&top>0)top--;
    else if(k==KY_OK||k==KY_BK)return;
  }
}
static void note(const char*s,char tone=' '){Msg m;mp(m,tone,"%s",s);showMsg("Info",m);}
static bool confirm(const char*q){
  const char*l[2]={"Oui","Non"};
  return menu(q,2,[&](int i,Item&it){snprintf(it.label,44,"%s",l[i]);},1)==0;
}

/* ---- sauvegarde ---- */
#define SAVE_MAGIC 0x54483031u
static void saveGame(){
  prefs.begin("terres",false);
  prefs.putUInt("magic",SAVE_MAGIC^(uint32_t)sizeof(Game));
  prefs.putBytes("game",&G,sizeof(Game));
  prefs.putBool("snd",gSound);prefs.putUChar("bri",gBright);prefs.putUShort("best",gBest);
  prefs.end();
}
static bool loadGame(){
  prefs.begin("terres",true);
  gSound=prefs.getBool("snd",true);gBright=prefs.getUChar("bri",70);gBest=prefs.getUShort("best",0);
  bool ok=prefs.getUInt("magic",0)==(SAVE_MAGIC^(uint32_t)sizeof(Game))&&prefs.getBytesLength("game")==sizeof(Game);
  if(ok){prefs.getBytes("game",&G,sizeof(Game));
    ok=G.started&&G.p.alive&&!G.over&&G.diff<N_DIFF&&G.p.env<N_ENV&&G.p.nHand<=HAND_CAP&&G.p.nInv<=INV_MAX&&G.p.nCache<=CACHE_CAP&&G.nDeck<=MAXDECK&&G.nDisc<=MAXDECK;}
  prefs.end();return ok;
}
static void clearSave(){prefs.begin("terres",false);prefs.remove("magic");prefs.end();}
static void saveSettings(){prefs.begin("terres",false);prefs.putBool("snd",gSound);prefs.putUChar("bri",gBright);prefs.putUShort("best",gBest);prefs.end();}

/* ---- écran principal ---- */
static const char* const MAIN_ITEMS[8]={"Explorer","Récolter","Fabriquer","Actions","Main","Équipé","Cache","Fin de journée"};
static void drawMain(int sel){
  Player&p=G.p;
  cv.fillSprite(C_BG);
  char h[64];
  int s=seasonIdx();
  if(G.jours)snprintf(h,sizeof(h),"J%d/%d %s · %s",G.jour,G.jours,SEASON_NAME[s],ENV().nom);else snprintf(h,sizeof(h),"J%d %s · %s",G.jour,SEASON_NAME[s],ENV().nom);
  header(h);
  /* jauges */
  struct{const char*n;int v;int mx;uint16_t c;}g[5]={{"Santé",p.pv,pvMax(p),C_BAD},{"Faim",p.sat,SAT_MAX,C_ACC},{"Eau",p.eau,EAU_MAX,cv.color565(90,150,230)},{"Énergie",p.ene,ENE_MAX,C_WARN},{"Moral",p.moral,10,cv.color565(170,120,220)}};
  for(int i=0;i<5;i++){
    int y=18+i*14;T(3,y-2,g[i].n,C_DIM);bar(52,y,56,g[i].v,g[i].mx,g[i].c);
    char b[10];snprintf(b,sizeof(b),"%d",g[i].v);T(112,y-2,b,C_FG);
  }
  /* ligne d'état */
  char st[64];snprintf(st,sizeof(st),"PA %d/%d  %s",p.ap,p.apMax,weatherShort(p.wx));T(3,88,st,C_FG);
  char st2[64];snprintf(st2,sizeof(st2),"%s",HAB_NAME[p.hab]);
  if(p.foyer)snprintf(st2+strlen(st2),sizeof(st2)-strlen(st2)," · foyer %d",p.foyer);
  if(p.fort)snprintf(st2+strlen(st2),sizeof(st2)-strlen(st2)," · renfort %d",p.fort);
  T(3,100,st2,C_DIM);
  char st3[64]="";
  for(int i=0;i<4;i++)if(p.cond&(1<<i))snprintf(st3+strlen(st3),sizeof(st3)-strlen(st3),"%s ",COND_NAME[i]);
  if(p.garde)strncat(st3,"veille ",sizeof(st3)-strlen(st3)-1);
  T(3,112,st3[0]?st3:"En forme.",st3[0]?C_BAD:C_DIM);
  char sg[40];snprintf(sg,sizeof(sg),"Signal %d/%d%s",G.signal,signalGoal(),G.watch?" (veille)":"");T(3,SH-12,sg,C_DIM);
  /* menu */
  for(int i=0;i<8;i++){
    int y=16+i*14;bool on=i==sel;
    if(on)cv.fillRect(132,y-1,106,14,C_SEL);
    TC(136,y,MAIN_ITEMS[i],on?C_ACC:C_FG,on?C_SEL:C_BG);
    if(i==4&&p.nHand){char b[8];snprintf(b,sizeof(b),"%d",p.nHand);TC(222,y,b,C_DIM,on?C_SEL:C_BG);}
    if(i==5&&p.nInv){char b[8];snprintf(b,sizeof(b),"%d",p.nInv);TC(222,y,b,C_DIM,on?C_SEL:C_BG);}
    if(i==6&&p.nCache){char b[8];snprintf(b,sizeof(b),"%d",p.nCache);TC(222,y,b,C_DIM,on?C_SEL:C_BG);}
  }
  T(132,SH-12,"; . haut/bas  OK  Esc:menu",C_DIM);
  cv.pushSprite(0,0);
}

/* ---- description d'une carte ---- */
static void cardInfo(const Card&c,char*out,int n){
  const CardDef&d=DEF_OF(c);char b[96]="";
  if(d.dur){snprintf(b+strlen(b),sizeof(b)-strlen(b),"[usure %d/%d] ",c.dur,d.dur);}
  if(d.perish){snprintf(b+strlen(b),sizeof(b)-strlen(b),"[pourrit %d] ",maxi(0,d.perish-c.age));}
  snprintf(out,n,"%s%s",b,d.txt);
}

/* ---- confirmation de défausse pour habitat ---- */
static bool pickDiscards(int handIdx,int cost,int*out){
  int chosen[8];int nc=0;
  while(nc<cost){
    Player&p=G.p;
    int idx[HAND_CAP],ni=0;for(int i=0;i<p.nHand;i++){if(i==handIdx)continue;bool used=false;for(int j=0;j<nc;j++)if(chosen[j]==i)used=true;if(!used)idx[ni++]=i;}
    char t[40];snprintf(t,sizeof(t),"Défausser %d/%d",nc+1,cost);
    int r=menu(t,ni,[&](int i,Item&it){snprintf(it.label,44,"%s",DEF_OF(p.hand[idx[i]]).nom);cardInfo(p.hand[idx[i]],it.info,96);});
    if(r<0)return false;chosen[nc++]=idx[r];
  }
  for(int i=0;i<cost;i++)out[i]=chosen[i];return true;
}

/* ---- jouer une carte de la main ---- */
static bool afterAction(const char*title,Msg&m){
  showMsg(title,m);
  if(!G.p.alive)return true;
  return false;
}
static bool handCardMenu(int hi){
  Player&p=G.p;Card c=p.hand[hi];const CardDef&d=DEF_OF(c);
  const char*why=canPlay(c);
  int ids[5],n=0;const char*lab[5];
  if(!why){ids[n]=0;lab[n++]=d.k==K_OBJET?"Équiper":d.k==K_HABITAT?"Construire":d.k==K_FOOD?"Consommer":"Utiliser";}
  if(canDry(c)){ids[n]=1;lab[n++]="Sécher (1 PA)";}
  if(cacheable(c)&&p.nCache<cacheMax(p)&&p.ap>=1){ids[n]=2;lab[n++]="Cacher (1 PA)";}
  ids[n]=3;lab[n++]="Défausser";
  int r=menu(d.nom,n,[&](int i,Item&it){snprintf(it.label,44,"%s",lab[i]);if(i==0&&why&&ids[0]!=0)it.info[0]=0;},0,why?why:NULL);
  if(r<0)return false;
  Msg m;
  if(ids[r]==0){
    int dis[8];int nd=0;
    if(d.k==K_HABITAT&&d.cost>0){if(!pickDiscards(hi,d.cost,dis))return false;nd=d.cost;}
    playCard(hi,dis,nd,m);
  }else if(ids[r]==1)doDry(hi,m);
  else if(ids[r]==2)doStash(hi,m);
  else{if(!confirm("Défausser ?"))return false;Card x=p.hand[hi];removeAt(p.hand,p.nHand,hi);discard(x);mp(m,' ',"%s défaussé.",d.nom);}
  return afterAction(d.nom,m);
}
static bool handScreen(){
  Player&p=G.p;int sel=0;
  for(;;){
    if(!p.nHand){note("Votre main est vide.");return false;}
    char t[32];snprintf(t,sizeof(t),"Main %d/%d",p.nHand,handMax(p));
    sel=menu(t,p.nHand,[&](int i,Item&it){
      const Card&c=p.hand[i];const CardDef&d=DEF_OF(c);
      snprintf(it.label,44,"%s",d.nom);cardInfo(c,it.info,96);
      it.mark=(canPlay(c)==NULL&&d.k!=K_MAT)?'g':0;
    },sel);
    if(sel<0)return false;
    if(handCardMenu(sel))return true;
    if(sel>=p.nHand)sel=maxi(0,p.nHand-1);
  }
}

/* ---- équipement ---- */
static bool equipScreen(){
  Player&p=G.p;int sel=0;
  for(;;){
    if(!p.nInv){note("Aucun équipement.");return false;}
    char t[32];snprintf(t,sizeof(t),"Équipé %d/%d",p.nInv,INV_MAX);
    sel=menu(t,p.nInv,[&](int i,Item&it){
      const Card&c=p.inv[i];const CardDef&d=DEF_OF(c);
      snprintf(it.label,44,"%s%s",d.nom,(c.fl&FL_SET)?" (tendu)":"");cardInfo(c,it.info,96);
      it.mark=canRepair(c)?'g':0;
    },sel);
    if(sel<0)return false;
    Card c=p.inv[sel];const CardDef&d=DEF_OF(c);
    int ids[3],n=0;const char*lab[3];
    if((d.tags&(T_PIEGE|T_CANNE))&&!(c.fl&FL_SET)&&p.ap>=1){ids[n]=0;lab[n++]="Tendre pour la nuit (1 PA)";}
    if(canRepair(c)){ids[n]=1;lab[n++]="Réparer (1 PA + 1 matériau)";}
    ids[n]=2;lab[n++]="Jeter";
    int r=simpleMenu(d.nom,n,lab);
    if(r<0)continue;
    Msg m;
    if(ids[r]==0)doTrap(sel,m);
    else if(ids[r]==1)doRepair(sel,m);
    else{if(!confirm("Jeter l'objet ?"))continue;Card x=p.inv[sel];removeAt(p.inv,p.nInv,sel);discard(x);mp(m,' ',"%s jeté.",d.nom);}
    if(afterAction(d.nom,m))return true;
    if(sel>=p.nInv)sel=maxi(0,p.nInv-1);
  }
}

/* ---- cache ---- */
static bool cacheScreen(){
  Player&p=G.p;
  const char*l[2]={"Voir / reprendre","Cacher une carte"};
  for(;;){
    char t[40];snprintf(t,sizeof(t),"Cache %d/%d",p.nCache,cacheMax(p));
    int r=simpleMenu(t,2,l);if(r<0)return false;
    if(r==0){
      if(!p.nCache){note("La cache est vide.");continue;}
      int s=menu("Reprendre",p.nCache,[&](int i,Item&it){snprintf(it.label,44,"%s",DEF_OF(p.cache[i]).nom);cardInfo(p.cache[i],it.info,96);});
      if(s>=0){if(doTakeCache(s))snd(1);else note("Main pleine.",'b');}
    }else{
      if(p.ap<1){note("Il faut 1 PA.",'b');continue;}
      if(p.nCache>=cacheMax(p)){note("Cache pleine (amélioration de l'habitat = plus de place).",'b');continue;}
      int idx[HAND_CAP],ni=0;for(int i=0;i<p.nHand;i++)if(cacheable(p.hand[i]))idx[ni++]=i;
      if(!ni){note("Rien de cachable (pas de denrée périssable, pas de contre).");continue;}
      int s=menu("Cacher",ni,[&](int i,Item&it){snprintf(it.label,44,"%s",DEF_OF(p.hand[idx[i]]).nom);cardInfo(p.hand[idx[i]],it.info,96);});
      if(s>=0){Msg m;doStash(idx[s],m);showMsg("Cache",m);}
    }
  }
}

/* ---- menaces (choix) ---- */
static bool threatScreen(Card t,Msg&m){
  Player&p=G.p;const CardDef&d=DEF_OF(t);
  char title[64];snprintf(title,sizeof(title),"%s !",d.nom);
  int ids[4],n=0;char lab[4][44],inf[4][96];
  Counter ct;bool hasC=findCounter(d,ct);
  if(d.k==K_PRED){
    if(hasC){ids[n]=CH_COUNTER;snprintf(lab[n],44,"Repousser (%s)",ct.label);snprintf(inf[n],96,"Sans dégât.");n++;}
    ids[n]=CH_FIGHT;snprintf(lab[n],44,"Combattre");snprintf(inf[n],96,"Attaque %d contre force %d. Perdre = dégâts.",ATK(p),predPower(d));n++;
    ids[n]=CH_ENDURE;snprintf(lab[n],44,"Encaisser");snprintf(inf[n],96,"Dégâts estimés : %d (défense %d).",maxi(0,predPower(d)-DEFN(p)),DEFN(p));n++;
  }else if(d.k==K_PROIE){
    int ci=catcherIdx(d);
    if(ci>=0){ids[n]=CH_HUNT;snprintf(lab[n],44,"Capturer (%s)",DEFS[p.inv[ci].def].nom);snprintf(inf[n],96,"%s",d.txt);n++;}
    ids[n]=CH_LET;snprintf(lab[n],44,"Laisser filer");snprintf(inf[n],96,"%s",ci<0?"Aucun outil adapté pour la prendre.":"Ne rien faire.");n++;
  }else{
    if(hasC){ids[n]=CH_COUNTER;snprintf(lab[n],44,"Contrer (%s)",ct.label);snprintf(inf[n],96,"Annule l'aléa.");n++;}
    ids[n]=CH_ENDURE;snprintf(lab[n],44,"Subir");snprintf(inf[n],96,"%s",d.txt);n++;
  }
  /* auto si un seul choix */
  int r=0;
  if(n>1){
    snd(2);
    r=menu(title,n,[&](int i,Item&it){snprintf(it.label,44,"%s",lab[i]);snprintf(it.info,96,"%s",inf[i]);},0,d.txt);
    if(r<0)r=n-1;
  }
  char tone=resolveThreat(t,ids[r],m);(void)tone;
  return !p.alive;
}
static bool explore(){
  Player&p=G.p;
  int cost=exploreCost(p);
  if(p.ap<cost){note("Pas assez de PA pour explorer.",'b');return false;}
  spend(p,cost);Msg m;
  for(int e=0;e<EXPLORE_DRAWS&&p.alive;e++){
    Card c;if(!drawCard(c)){mp(m,' ',"Rien de nouveau.");break;}
    const CardDef&d=DEF_OF(c);
    if(d.k==K_PRED||d.k==K_PROIE||d.k==K_MALUS){
      if(m.n){showMsg("Exploration",m);m.n=0;}
      threatScreen(c,m);
    }else if(d.k==K_CHANCE){mp(m,'g',"%s : %s",d.nom,d.txt);resolveChance(c,m);}
    else if(p.nHand<HAND_CAP){p.hand[p.nHand++]=c;mp(m,'g',"Trouvé : %s.",d.nom);}
    else{discard(c);mp(m,'b',"Main pleine : %s abandonné.",d.nom);}
  }
  showMsg("Exploration",m);
  return !p.alive;
}

/* ---- récolter / fabriquer / actions ---- */
static bool collectMenu(){
  Player&p=G.p;
  const char*lab[5]={"Bois","Pierre","Fibres","Eau","Vivres"};
  char inf[5][96];
  for(int i=0;i<5;i++){
    if(i==CO_EAU){Water w=waterYield(p);snprintf(inf[i],96,"Eau +%d. %s",w.n,w.warn);}
    else if(i==CO_VIVRES)snprintf(inf[i],96,"%d %% de trouver de quoi manger.",collectYield(p,i));
    else snprintf(inf[i],96,"+%d %s.",collectYield(p,i),lab[i]);
  }
  int r=menu("Récolter (1 PA)",5,[&](int i,Item&it){snprintf(it.label,44,"%s",lab[i]);snprintf(it.info,96,"%s",inf[i]);it.ok=p.ap>=1&&!(i<3&&collectYield(p,i)<=0);if(p.ap<1)snprintf(it.info,96,"Plus de PA.");});
  if(r<0||p.ap<1)return false;
  Msg m;char tone=doCollect(r,m);(void)tone;return afterAction(lab[r],m);
}
static bool craftMenu(){
  Player&p=G.p;
  int r=menu("Fabriquer (1 PA)",N_REC,[&](int i,Item&it){
    const Recipe&rc=RECIPES[i];char why[64]="";
    snprintf(it.label,44,"%s",DEFS[rc.out].nom);
    bool ok=canCraft(rc,why,64)&&p.ap>=1;
    if(!ok&&!why[0])snprintf(why,64,"plus de PA");
    char need[64]="";if(rc.bois)snprintf(need+strlen(need),64-strlen(need),"%dBois ",rc.bois);if(rc.pierre)snprintf(need+strlen(need),64-strlen(need),"%dPierre ",rc.pierre);if(rc.fibres)snprintf(need+strlen(need),64-strlen(need),"%dFibres ",rc.fibres);if(rc.peau)snprintf(need+strlen(need),64-strlen(need),"%dPeau ",rc.peau);
    snprintf(it.info,96,"%s%s%s",need,ok?"":"· ",ok?"":why);it.ok=ok;it.mark=ok?'g':0;
  });
  if(r<0)return false;
  char why[64];if(!canCraft(RECIPES[r],why,64)||p.ap<1){note("Impossible pour l'instant.",'b');return false;}
  Msg m;doCraft(RECIPES[r],m);return afterAction(DEFS[RECIPES[r].out].nom,m);
}
static bool affutMenu(int mode){
  Player&p=G.p;int ch;char why[64];
  if(!affutInfo(mode,ch,why,64)||p.ap<1){note(p.ap<1?"Plus de PA.":why,'b');return false;}
  char q[64];snprintf(q,sizeof(q),"%s : %d %% de réussite",mode==AF_PECHE?"Pêche":"Chasse",ch);
  if(!confirm(q))return false;
  Msg m;char tone;int w=doAffut(mode,m,tone);
  if(w>0){showMsg("À l'affût",m);m.n=0;
    const char*l[2]={"L'achever","Lâcher prise"};
    char inf[2][96];snprintf(inf[0],96,"Attaque %d contre force %d : risque de blessure.",ATK(p),w);snprintf(inf[1],96,"Vous perdez la prise.");
    int r=menu("Bête blessée !",2,[&](int i,Item&it){snprintf(it.label,44,"%s",l[i]);snprintf(it.info,96,"%s",inf[i]);},0);
    resolveWounded(w,r==0,m);
  }
  return afterAction(mode==AF_PECHE?"Pêche":"Chasse",m);
}
static bool actionsMenu(){
  Player&p=G.p;char why[64];
  enum{A_REST,A_SIG,A_FOY,A_FORT,A_GARDE,A_PECHE,A_CHASSE,A_FUME,A_N};
  const char*lab[A_N]={"Se reposer","Signal de détresse","Entretenir le foyer","Renforcer l'abri","Veiller cette nuit","Pêcher à l'affût","Chasser à l'affût","Fumer poisson/gibier"};
  int sel=0;
  for(;;){
    bool ok[A_N];char inf[A_N][96];
    for(int i=0;i<A_N;i++){ok[i]=true;why[0]=0;inf[i][0]=0;}
    inf[A_REST][0]=0;snprintf(inf[A_REST],96,"+2 énergie%s (1 PA).",p.hab>=1?" et +1 santé à l'abri":"");ok[A_REST]=p.ap>=1;
    ok[A_SIG]=canSignal(why,64)&&p.ap>=1;snprintf(inf[A_SIG],96,"%s",ok[A_SIG]?"2 Bois ou miroir. Fait monter le signal (1 PA).":(p.ap<1?"Plus de PA.":why));
    ok[A_FOY]=canFoyer(why,64)&&p.ap>=1;snprintf(inf[A_FOY],96,"%s",ok[A_FOY]?"1 Bois : repousse les bêtes, compte comme feu (1 PA).":(p.ap<1?"Plus de PA.":why));
    ok[A_FORT]=canFort(why,64)&&p.ap>=1;snprintf(inf[A_FORT],96,"%s",ok[A_FORT]?"2 matériaux : stress de nuit -1 (1 PA).":(p.ap<1?"Plus de PA.":why));
    ok[A_GARDE]=canGarde(why,64)&&p.ap>=1;snprintf(inf[A_GARDE],96,"%s",ok[A_GARDE]?"Aucune surprise nocturne, énergie -2 (1 PA).":(p.ap<1?"Plus de PA.":why));
    {int ch;ok[A_PECHE]=affutInfo(AF_PECHE,ch,why,64)&&p.ap>=1;if(ok[A_PECHE])snprintf(inf[A_PECHE],96,"%d %% de Poisson. Énergie -1 (1 PA).",ch);else snprintf(inf[A_PECHE],96,"%s",p.ap<1?"Plus de PA.":why);}
    {int ch;ok[A_CHASSE]=affutInfo(AF_CHASSE,ch,why,64)&&p.ap>=1;if(ok[A_CHASSE])snprintf(inf[A_CHASSE],96,"%d %% de Gibier, la bête peut se retourner (1 PA).",ch);else snprintf(inf[A_CHASSE],96,"%s",p.ap<1?"Plus de PA.":why);}
    ok[A_FUME]=canSmoke(why,64)&&p.ap>=1;snprintf(inf[A_FUME],96,"%s",ok[A_FUME]?"Jusqu'à 4 prises : elles se gardent (1 PA).":(p.ap<1?"Plus de PA.":why));
    sel=menu("Actions",A_N,[&](int i,Item&it){snprintf(it.label,44,"%s",lab[i]);snprintf(it.info,96,"%s",inf[i]);it.ok=ok[i];it.mark=ok[i]?'g':0;},sel);
    if(sel<0)return false;
    if(!ok[sel]){snd(2);continue;}
    Msg m;
    switch(sel){
      case A_REST:doRest(m);break;case A_SIG:doSignal(m);break;case A_FOY:doFoyer(m);break;
      case A_FORT:doFort(m);break;case A_GARDE:doGarde(m);break;case A_FUME:doSmoke(m);break;
      case A_PECHE:return affutMenu(AF_PECHE);case A_CHASSE:return affutMenu(AF_CHASSE);
    }
    if(afterAction(lab[sel],m))return true;
  }
}

/* ---- fin de journée ---- */
static bool endOfDay(){
  Player&p=G.p;
  while(p.nHand>handMax(p)){
    char t[40];snprintf(t,sizeof(t),"Main pleine : jetez (%d en trop)",p.nHand-handMax(p));
    int r=menu(t,p.nHand,[&](int i,Item&it){snprintf(it.label,44,"%s",DEF_OF(p.hand[i]).nom);cardInfo(p.hand[i],it.info,96);});
    if(r<0)r=p.nHand-1;
    Card x=p.hand[r];removeAt(p.hand,p.nHand,r);discard(x);
  }
  if(p.ap>0&&!confirm("Il reste des PA. Dormir ?"))return false;
  Msg m;
  endDay(m);
  showMsg("La nuit",m);
  if(!p.alive)return true;
  Msg m2;nextDay(m2);
  if(G.over)return true;
  char t[24];snprintf(t,sizeof(t),"Jour %d",G.jour);
  mp(m2,' ',"Météo : %s. PA : %d.",WXS[p.wx].nom,p.ap);
  mp(m2,' ',"Demain : %s.",WXS[p.wxNext].nom);
  showMsg(t,m2);
  saveGame();
  return !p.alive;
}

/* ---- fin de partie ---- */
static void endScreen(){
  Player&p=G.p;clearSave();
  int sc=scoreOf(p);bool rescued=G.rescued&&p.alive;
  bool survived=p.alive&&(G.rescued||(G.jours&&G.jour>G.jours));
  if(survived&&sc>gBest){gBest=(uint16_t)sc;}
  saveSettings();
  cv.fillSprite(C_BG);header(survived?"Survivant !":"Fin de partie");
  char b[96];
  if(rescued)snprintf(b,sizeof(b),"Secouru au jour %d.",G.jour);
  else if(survived)snprintf(b,sizeof(b),"Vous avez tenu %d jours.",G.jours);
  else snprintf(b,sizeof(b),"Mort au jour %d : %s.",p.mort?p.mort:G.jour,p.cause);
  T(6,22,b,survived?C_GOOD:C_BAD);
  snprintf(b,sizeof(b),"Score %d  (record %d)",survived?sc:0,gBest);T(6,40,b,C_FG);
  snprintf(b,sizeof(b),"%s · %s",ENV().nom,DIFFS[G.diff].nom);T(6,56,b,C_DIM);
  snprintf(b,sizeof(b),"Signaux %d · habitat : %s",p.sig,HAB_NAME[p.hab]);T(6,70,b,C_DIM);
  T(6,SH-14,"OK : retour au menu",C_DIM);
  cv.pushSprite(0,0);snd(survived?3:4);
  for(;;){int k=waitKey();if(k==KY_OK||k==KY_BK)break;}
}

/* ---- nouvelle partie / réglages ---- */
static bool newGameMenu(){
  const char*const durL[4]={"Court : 8 jours","Normal : 12 jours","Long : 16 jours","Sans fin"};
  static const uint8_t durV[4]={8,12,16,0};
  int d=menu("Difficulté",N_DIFF,[&](int i,Item&it){snprintf(it.label,44,"%s",DIFFS[i].nom);snprintf(it.info,96,"%s",DIFFS[i].txt);},1);
  if(d<0)return false;
  int j=simpleMenu("Durée",4,durL,NULL,1);if(j<0)return false;
  newGame(d,durV[j]);
  Msg m;mp(m,' ',"%s",ENV().nom);mp(m,' ',"%s",ENV().desc);
  if(G.p.nInv)mp(m,'g',"Départ avec : %s.",DEF_OF(G.p.inv[0]).nom);
  mp(m,' ',"Objectif : tenir %s ou être secouru (signal).",G.jours?"la durée":"le plus longtemps possible");
  showMsg("Atterrissage",m);
  saveGame();return true;
}
static void settings(){
  for(;;){
    int r=menu("Réglages",4,[&](int i,Item&it){
      if(i==0)snprintf(it.label,44,"Son : %s",gSound?"oui":"non");
      else if(i==1)snprintf(it.label,44,"Luminosité : %d %%",gBright);
      else if(i==2)snprintf(it.label,44,"Abandonner la partie");
      else snprintf(it.label,44,"Aide des touches");
    });
    if(r<0)break;
    if(r==0){gSound=!gSound;snd(1);}
    else if(r==1){gBright=gBright>=100?20:gBright+20;M5Cardputer.Display.setBrightness(gBright*255/100);}
    else if(r==2){if(confirm("Abandonner ?")){die(G.p,"abandon");return;}}
    else{Msg m;mp(m,' ',"; haut   . bas   , gauche   / droite");mp(m,' ',"Entrée ou Espace : valider");mp(m,' ',"Retour arrière ou ` : annuler");mp(m,' ',"1-9 : choix direct dans un menu");mp(m,' ',"Les points * indiquent une action disponible.");showMsg("Touches",m);}
    saveSettings();
  }
  saveSettings();
}

/* ---- boucle principale ---- */
static void playLoop(){
  int sel=0;
  while(!G.over&&G.p.alive){
    drawMain(sel);
    int k=waitKey();bool dead=false;
    if(k==KY_UP){sel=(sel+7)%8;snd(0);}
    else if(k==KY_DN){sel=(sel+1)%8;snd(0);}
    else if(k>=KY_NUM0+1&&k<=KY_NUM0+8){sel=k-KY_NUM0-1;k=KY_OK;}
    if(k==KY_BK){settings();saveGame();continue;}
    if(k==KY_OK||k==KY_RT){
      snd(1);
      switch(sel){
        case 0:dead=explore();break;
        case 1:dead=collectMenu();break;
        case 2:dead=craftMenu();break;
        case 3:dead=actionsMenu();break;
        case 4:dead=handScreen();break;
        case 5:dead=equipScreen();break;
        case 6:dead=cacheScreen();break;
        case 7:dead=endOfDay();break;
      }
      if(G.p.alive&&!dead)saveGame();
    }
  }
}
static void splash(){
  cv.fillSprite(C_BG);
  cv.setTextColor(C_ACC,C_BG);cv.setTextSize(2);cv.drawString("TERRES HOSTILES",8,24);cv.setTextSize(1);
  T(8,56,"Jeu de survie en solitaire",C_FG);
  T(8,72,"pour M5Stack Cardputer Adv",C_DIM);
  T(8,SH-16,"Appuyez sur une touche",C_DIM);
  cv.pushSprite(0,0);
}
void setup(){
  auto cfg=M5.config();
  M5Cardputer.begin(cfg,true);
  M5Cardputer.Display.setRotation(1);
  cv.setColorDepth(16);cv.createSprite(SW,SH);
  cv.setFont(&fonts::efontJA_12);cv.setTextDatum(top_left);cv.setTextWrap(false);
  initColors();
  loadGame();                 /* charge aussi les réglages */
  M5Cardputer.Display.setBrightness(gBright*255/100);
  splash();waitKey();
}
void loop(){
  bool can=loadGame();
  if(can){
    const char*l[3]={"Continuer","Nouvelle partie","Réglages"};
    char info[96];snprintf(info,96,"Jour %d · %s · %s",G.jour,ENV().nom,DIFFS[G.diff].nom);
    const char*inf[3]={info,"Efface la partie en cours.","Son, luminosité, aide."};
    int r=simpleMenu("Terres Hostiles",3,l,inf);
    if(r==0){playLoop();if(G.over||!G.p.alive)endScreen();}
    else if(r==1){if(confirm("Écraser la sauvegarde ?")&&newGameMenu()){playLoop();endScreen();}}
    else if(r==2)settings();
  }else{
    const char*l[2]={"Nouvelle partie","Réglages"};
    char info[96];snprintf(info,96,"Record : %d",gBest);
    const char*inf[2]={info,"Son, luminosité, aide."};
    int r=simpleMenu("Terres Hostiles",2,l,inf);
    if(r==0){if(newGameMenu()){playLoop();endScreen();}}
    else if(r==1)settings();
  }
}
