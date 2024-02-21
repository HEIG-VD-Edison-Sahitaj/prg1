# PRG1-L4 - Snake game

Le but de ce laboratoire est de programmer un jeu vidéo de
type "[Snake](https://fr.wikipedia.org/wiki/Snake_(genre_de_jeu_vidéo))" qui se 
joue à la console de votre ordinateur. 

Un exemple de mise en oeuvre est disponible ici: 

[https://youtu.be/tm_t0dL8YFs](https://youtu.be/tm_t0dL8YFs)

On ré-oriente le serpent avec les lettres a, s, d, et w du clavier. 

La mise en oeuvre du jeu nécessite d'utiliser des fonctionnalités de 
la console qui ne sont pas disponibles via le standard C++ mais
uniquement via des appels au système d'exploitation, et donc 
qui varient selon le systèmes. Ces appels sont fournis via 
les fichiers [console_io.h](./console_io.h) et [console_io.cpp](./console_io.cpp) 
qui fonctionnent sous unix et windows. 

Le fichier principal avec la boucle de jeu vous est fourni dans [main.cpp](main.cpp). 
A vous de choisir que stocker dans la structure retournée par la 
fonction `init_game()` et qui sert à communiquer entre les 
différentes fonctions sans utiliser de variables globales. 

Le jeu en lui même consiste à déplacer le serpent sans qu'il
ne touche les parois ou ne se touche lui-même. Il grandit d'une
pièce à chaque fois qu'il mange de la nourriture ( `*` ). 
Une nouvelle nourriture apparait alors instantanément. 
Il oriente toujours sa bouche dans la direction où il se 
déplace. Le jeu s'arrête quand le serpent entre en collision 
avec les parois ou lui-même. Le score final est le nombre 
de nourritures mangées. 
