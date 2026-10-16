# Terres Hostiles — Cardputer Adv

Jeu de survie en solitaire, à cartes, pour le **M5Stack Cardputer Adv** (ESP32-S3, écran 240×135, clavier 56 touches).
Port du jeu web *Terres Hostiles* : un seul sketch Arduino, sans fichier de ressources.

> **État** : le moteur de jeu a été testé sur PC (parties simulées, contrôle des bornes) et l'interface a été passée au fuzzing sur PC contre une copie simulée de l'API M5. Le sketch n'a **pas** encore été compilé avec la chaîne ESP32 ni testé sur un appareil. Les retours de compilation sont les bienvenus (voir [Problèmes](#problèmes-connus)).

## Le jeu

Vous atterrissez dans un milieu hostile tiré au hasard. Tenez jusqu'à la fin de la durée choisie, ou allumez un signal assez fort pour être repéré et secouru.

- **11 milieux** : désert, océan, forêt, glacier, montagne, marais, jungle, savane, steppe, canyon, fjord.
- **Saisons** (8 jours chacune) et **météo** qui changent les besoins, la récolte et le stress de la nuit.
- **Jauges** : santé, faim, eau, énergie, moral. **Points d'action** (PA) par jour, réduits par la fatigue, la fracture, le mauvais temps.
- **150 cartes** : matériaux, outils, nourriture, soins, abris, prédateurs, proies, aléas, coups de chance.
- **19 recettes** de fabrication (bois, pierre, fibres, peau, outils requis).
- **Habitat** en 3 niveaux (abri de fortune, cabane, refuge fortifié) : santé max, protection la nuit, conservation des vivres.
- **Conditions** : saignement, infection, fracture, gastro-entérite, avec leurs remèdes.
- **Mécaniques avancées** : cache (rien n'y est volé), renfort d'abri, veille de nuit, foyer à entretenir, pêche et chasse à l'affût (une bête blessée peut se retourner), fumage du poisson et du gibier, collets et filets, réparation d'outils.
- **Signal et secours** : chaque signal fait monter la jauge ; une fois le seuil atteint, un secours peut vous repérer chaque jour.
- **5 niveaux de difficulté** : Randonneur, Survivaliste, Extrême, Enfer, Impitoyable.
- **Durées** : 8, 12, 16 jours ou sans fin. Score et record enregistrés.

Absent de cette version (écran trop petit) : plantes et remèdes, habitants et visiteurs, scénarios, défi du jour, température corporelle, peur, compétences, objectifs, journal.

## Matériel

| | |
|---|---|
| Appareil | M5Stack Cardputer Adv (ESP32-S3FN8, 8 Mo de flash, sans PSRAM) |
| Mémoire | partie en cours : environ 2,5 Ko (stockée dans la mémoire NVS) |
| Bibliothèques | M5Cardputer ≥ 1.1.1, M5Unified, M5GFX |

## Installation (Arduino IDE 2)

1. *Fichier → Préférences* : ajouter dans « URL de gestionnaire de cartes supplémentaires »
   `https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json`
2. *Outils → Carte → Gestionnaire de cartes* : installer **M5Stack**.
3. *Outils → Gérer les bibliothèques* : installer **M5Cardputer** (M5Unified et M5GFX suivent).
4. Placer `TerresHostiles_Cardputer.ino` dans un dossier du même nom `TerresHostiles_Cardputer/`.
5. *Outils → Carte → M5Stack → M5Cardputer*, partition par défaut.
6. Brancher l'appareil en USB-C, choisir le port, téléverser.

Si aucun port n'apparaît : éteindre, maintenir **G0**, rallumer, relâcher, puis téléverser.

### Arduino CLI

```bash
URL=https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json
arduino-cli core update-index --additional-urls $URL
arduino-cli core install m5stack:esp32 --additional-urls $URL
arduino-cli lib install M5Cardputer M5Unified M5GFX
arduino-cli compile --fqbn m5stack:esp32:m5stack_cardputer TerresHostiles_Cardputer
arduino-cli upload  -p /dev/ttyACM0 --fqbn m5stack:esp32:m5stack_cardputer TerresHostiles_Cardputer
```

## Commandes

| Touche | Action |
|---|---|
| `;` | haut |
| `.` | bas |
| `,` | gauche |
| `/` | droite |
| Entrée ou Espace | valider |
| Retour arrière ou `` ` `` | annuler / réglages (depuis l'écran principal) |
| `1` à `9` | choix direct dans un menu |

Les lettres `W A S D` et `E` / `Q` fonctionnent aussi. Une pastille `*` à droite d'une ligne signale une action ou une carte utilisable.

## Déroulement d'une journée

1. **Explorer** (1 PA, plus selon la météo) : on tire 2 cartes. Matériaux et vivres vont dans la main, les bêtes et aléas demandent un choix (repousser, combattre, encaisser, capturer).
2. **Récolter** (1 PA) : bois, pierre, fibres, eau, vivres.
3. **Fabriquer**, **Actions** (repos, signal, foyer, renfort, veille, affût, fumage), **Main**, **Équipé**, **Cache**.
4. **Fin de journée** : la main est ramenée à sa taille maximale, puis la nuit se résout (stress du milieu, rôdeurs, faim, soif, soins, sommeil). La partie est enregistrée.

## Structure du sketch

Un seul fichier `.ino`, en trois sections :

- **A. Données** : cartes, milieux, météo, saisons, recettes. Générées depuis le jeu web.
- **B. Moteur** : règles du jeu, sans aucun appel matériel.
- **C. Interface** : écran (sprite M5Canvas 240×135), clavier, son, sauvegarde NVS.

Le tirage aléatoire passe par `hwrand()` (`esp_random()` sur l'appareil).

### Régénérer les données

Si le jeu web `index.html` change, `dump_data.js` et `gen_data.js` (Node.js) recréent la section A :

```bash
node gen_data.js   # écrit th_data.h
```

## Problèmes connus

- **Compilation** : une erreur sur `M5Cardputer.h` ou `fonts::efontJA_12` vient presque toujours d'une bibliothèque trop ancienne. Mettre à jour M5GFX et M5Unified.
- **Affichage** : si des accents ou symboles manquent, ouvrir une issue avec une photo de l'écran. Le sketch remplace déjà `−`, `→`, `●`, `œ`.
- **Équilibrage** : la difficulté a été portée telle quelle depuis le jeu web, mais n'a pas été rejouée sur l'appareil.
- **Carte absente de la liste** : choisir `ESP32S3 Dev Module` avec *USB CDC On Boot : Enabled*.

## Licence

À définir par l'auteur.

