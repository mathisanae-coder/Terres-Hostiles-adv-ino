# TERRES HOSTILES — M5Stack Cardputer Adv

Jeu de survie en solitaire, à cartes, pour le **M5Stack Cardputer Adv** (ESP32‑S3, écran 240×135, clavier 56 touches).
Tout le jeu tient dans un seul sketch Arduino : `TerresHostiles_Cardputer.ino`.

## Contenu du dossier

| Fichier | Rôle |
|---|---|
| `TerresHostiles_Cardputer_complet.bin` | Image de flash complète (bootloader + partitions + application, 4 Mo). **À flasher à l'adresse `0x0`.** |
| `TerresHostiles_Cardputer_app.bin` | Application seule. À flasher à `0x10000` (bootloader et partitions déjà présents). |
| `TerresHostiles_Cardputer.ino` | Code source du jeu (moteur + interface + animations). |
| `terres-hostiles-sim.html` | Simulateur pour smartphone/navigateur : fait tourner le vrai code du jeu (compilé en WebAssembly). |
| `README.md` | Ce fichier. |

## Installer le jeu sur le Cardputer

Choisis **une** méthode.

**1. Flasheur web (le plus simple, depuis Chrome/Edge sur ordinateur ou Android)**
1. Branche le Cardputer en USB‑C. Si le port n'apparaît pas, maintiens la touche **G0** (bouton latéral) en le branchant, ou en appuyant sur reset.
2. Ouvre un flasheur web ESP (par exemple `esp.huhn.me`), connecte‑toi au port.
3. Ajoute `TerresHostiles_Cardputer_complet.bin` à l'adresse **0x0**, puis lance le flash.

**2. esptool (ligne de commande, y compris Termux)**
```bash
esptool.py --chip esp32s3 --port /dev/ttyACM0 --baud 921600 \
  write_flash 0x0 TerresHostiles_Cardputer_complet.bin
```

**3. M5Burner**
Ajoute `TerresHostiles_Cardputer_complet.bin` comme firmware local (adresse 0x0), puis grave.

> Le flash remplace le programme actuel du Cardputer. La sauvegarde de la partie est stockée à part (mémoire non volatile, espace « terres »).

## Commandes

| Action | Touches |
|---|---|
| Haut / bas | `;` et `.` (ou `W` / `S`) |
| Gauche / droite | `,` et `/` (ou `A` / `D`) |
| Valider | `Entrée`, `Espace` ou `E` |
| Annuler / retour | `Retour arrière`, `` ` `` ou `Q` |
| Choix direct dans un menu | `1` à `9` |

Sur l'écran titre, **n'importe quelle touche** lance le jeu.

## Principe du jeu

- Tu choisis une **difficulté** (Randonneur, Survivaliste, Extrême, Enfer, Impitoyable) puis une **durée** (8, 12, 16 jours ou sans fin).
- Tu atterris dans un **environnement** tiré au hasard (forêt, désert, glacier, marais, océan, etc.) avec un objet de départ.
- Chaque jour, tu disposes de **points d'action (PA)** pour : *Explorer*, *Récolter*, *Fabriquer*, faire des *Actions* (se reposer, signal de détresse, entretenir le foyer, renforcer l'abri, veiller, pêcher ou chasser à l'affût…), gérer ta *Main*, ton *Équipement* et ta *Cache*.
- Tu surveilles **Santé, Faim, Eau, Énergie et Moral**, la **météo** et les **saisons**. Blessures, infections, prédateurs et objets qui s'usent rendent la survie plus dure.
- Fin de partie : **tenir la durée choisie**, ou **être secouru** en entretenant un signal de détresse.
- Le soir, « **Fin de journée** » fait passer la nuit (animation de nuit), puis le jour suivant commence. La partie est sauvegardée automatiquement.
- Un meilleur score est conservé (« Record »).

Menu **Réglages** : son, luminosité, abandon de la partie, aide des touches.

## Animations et musique

- **Écran titre** : aube qui se lève, titre qui tombe lettre par lettre, thème d'aventure 8 bits **en boucle jusqu'à un appui sur une touche**.
- **Petit personnage** : à chaque boucle il enchaîne 2 activités tirées parmi 10 (regarder autour de lui, couper du bois, feu de camp, pêche, baies, saut de joie, salut, gourde, étoiles, lapin).
- **Nuit** : coucher de soleil, étoiles, lune, étoile filante, tente et feu de camp, météo du jour (pluie, orage, neige, brouillard), aube. Une touche passe l'animation.
- Le réglage **Son** coupe aussi la musique.

## Simulateur smartphone

Ouvre `terres-hostiles-sim.html` dans le navigateur du téléphone (aucune connexion nécessaire).
- Appuie sur **Allumer** : le navigateur n'autorise le son qu'après un toucher.
- Boutons à l'écran : `1`–`9`, croix directionnelle, `Entrée`, `Retour` ; un clavier physique fonctionne aussi.
- La sauvegarde du simulateur reste dans le navigateur, séparée de celle du Cardputer.

## Compiler soi‑même

**Arduino IDE**
- Carte : **M5Cardputer** (paquet de cartes ESP32 / M5Stack en version 3.x), partition par défaut.
- Bibliothèques : `M5Cardputer` (≥ 1.1.1), `M5Unified`, `M5GFX`.

**arduino-cli**
```bash
arduino-cli compile -b esp32:esp32:m5stack_cardputer \
  --output-dir build TerresHostiles_Cardputer
```
Le fichier `build/…ino.merged.bin` est l'image complète à flasher à `0x0`.

Version utilisée pour les binaires fournis : cœur ESP32 **3.2.0**, M5Cardputer 1.1.1, M5Unified 0.2.26, M5GFX 0.2.33. Occupation : environ 71 % de la flash et 9 % de la RAM.

## Organisation du code

Le sketch est découpé en trois blocs :
- **A. Données** : cartes, environnements, météos, difficultés (générées depuis le jeu web).
- **B. Moteur de jeu** : règles, pioche, saisons, fin de journée ; sans dépendance matérielle.
- **C. Interface Cardputer** : écran, clavier, menus, sons, sauvegarde, animations (intro et nuit).

Les animations n'utilisent pas le hasard du jeu : elles ne changent pas le déroulement d'une partie.
