# LongInt

L'objectif de ce laboratoire est de mettre en oeuvre une classe `LongInt`
qui permet de réaliser des calculs avec des entiers de longueur arbitrairement longue,
ainsi que plusieurs programmes principaux utilisant cette classe pour

- en tester toutes les fonctionalités
- calculer le 1000ème nombre de [Fibonacci](https://fr.wikipedia.org/wiki/Suite_de_Fibonacci)
- calculer le 1000ème nombre de la suite [A061084](https://oeis.org/A061084)
- calculer la [factorielle](https://fr.wikipedia.org/wiki/Factorielle) de 100.

Les fonctions calculant Fibonacci, factorielle et A061084 doivent être écrites
pour un type générique vous permettant de vérifier pour de
petits paramètres que le résultat est identique avec `int` ou `LongInt`, et
avec le type `double` si l'ordre de grandeur et les premiers chiffres sont
corrects.

La class `LongInt` doit
- définir le type `LongIng::digit_t` comme un alias d'un type entier non signé
- définir la constante `LongInt::radix` de type `LongInt::digit_t` qui est la base de la représentation de vos nombres et vaudra typiquement 10, ou une puissance de 10 plus petite que la moitié du plus grand `LongIng::digit_t` représentable.
- stocker les données dans 2 attributs privés, un `std::vector<LongInt::digit_t>` pour les chiffres et un `bool` pour le signe. La valeur `true` code un nombre négatif.
- permettre de convertir implicitement tout type entier en `LongInt`
- permettre de convertir explicitement seulement un `LongInt` en `long long` ou en `int`
- fournir les 6 opérations de comparaison: `==, !=, <, >, <=, >=`.
- fournir 3 opérations arithmétiques entre `LongInt` : `+, -, *` et leurs versions avec affectation composée.
- fournir les opérations d'incrémentation et de décrémentation préfixes et postfixes
- fournir les opérateurs unaires `+` et `-`
- fournir l'opérateur de flux `<<`. L'affichage doit tenir compte de la largeur de colonne demandée, de l'état `showpos` ou pas, et de l'alignement `left`, `right` ou `internal`. Vous trouverez plus d'informations sur comment déterminer ces modes [ici](https://chat.openai.com/share/d453744b-e084-4465-be96-746c84fca752).
- fournir l'opérateur de flux `>>`. La lecture doit sauter les espaces, lire le signe (optionnel pour +) et tous les chiffres jusqu'à ce qu'il rencontre un autre symbole. Si l'entrée est mal formée, il met le flux en état `fail`.

**Conseils** :

- Commencez par utiliser une base `LongInt::radix = 10`, qui est la plus intuitive.
- Réfléchissez au sens dans lequel vous voulez stocker les chiffres dans le `vector`: l'unité est-elle coté `front()` ou `back()` ?
- Dans quel ordre allez vous mettre en oeuvre les fonctions et opérateurs ? Disposer assez vite d'un operator<< peut par exemple vous simplifier la vie.
- Testez, testez, testez ...

Note : les opérateurs `/` et `%` ne sont pas demandés. 