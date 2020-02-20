11/02/2019 - Initial commit 


3/03/2019 - Ajout d'une première version du cahier des charges et du compte rendu du 13/02 :
	Toujours vérifier que vous disposez bien de la dernière version du git sur votre ordinateur avant
	toute modification.

14/03/2019 - Ajout d'une base commune + Assets.
	J'ai ajouté une base commune pour tout le monde pour qu'on se mette d'accord sur les différentes valeurs, la taille de la fenêtre pour le jeu me paraît raisonnable comme ça. J'ai aussi ajouté les fichiers jeu.h et constantes.h ainsi que les librairies SDL. S'il y a des erreurs au niveau du linker sur C:Blocks, dites le moi rapidement. 
	
<<<<<<< HEAD
=======
19/03/2019 - Antoine - Ajout des derniers compte-rendus et réorganisation des fichiers du projet
	J'ai ajouté les derniers compte rendus en pdf. J'ai aussi réorganisé comme demandé les différents fichiers *.h et *.c du projet dans les dossiers qui leur correspondent. Il ne faut pas non plus oublier de retirer les fichiers *.o avant de déposer sur le git. Je modifierai très prochainement la librairie SDL 1.2 par la 2.0.

24/03/2019 - Passage de la SDL1.2 vers la SDL2.0 + ajout d'un fichier environnement.h
	Création des fenêtres grâce à la SDL2.0 et ajout du fichier environnement.h avec sa structure et d'une fonction permettant d'importer facilement une image.
	
26/03/2019 - Ajout de fonction de génération de la map à partir de la struct environnement + génération de fichier contenant le 'code' de la map.
	Création d'une fonction nous permettant d'initialiser la map dans un tableau à 2D. Ajout en plus d'une fonction nous permettant de remplir la map[X][Y] contenu dans la structure environnement. Ajout d'une fonction permettant de générer une nombre de façon pseudo-aléatoire pour pouvoir remplir la map. Création d'une fonction permettant de générer une map à partir d'un fichier 'code' en cours.
>>>>>>> Moteur_graphique
