# LongInt<T,R>

L'objectif de ce laboratoire est de modifier le [précédent](Precedent.md) pour rendre la classe `LongInt` générique.

Elle aura 2 arguments génériques, i.e. `LongInt<T,R>` avec

- `T`, le type des éléments du vecteur des données. On aura donc `using digit_t = T;`
- `R`, la valeur de la base. On aura donc `static const digit_t radix = R;`

Ces arguments respecteront les contraintes suivantes
- `T` doit être obligatoirement de type entier non signé, ce que l'on garantit en utilisant le concept `std::unsigned_integral`
- `R` doit être une puissance strictement positive de 10, et ne pas être trop grand par rapport au type `T` utilisé pour que les calculs restent exacts. Par exemple, si `T` est `uint8_t`, alors `R` peut valoir 10 ou 100, mais pas plus. Ces deux contraintes doivent être vérifiées avec deux `static_assert`

Par ailleurs, `R` doit avoir une valeur par défaut qui correspond à la plus grand puissance de 10 qui fonctionne pour le type T choisi, de sorte que l'on
puisse utiliser le type `LongInt<unsigned int>` sans devoir préciser `R = 1'000'000'000`. Une technique possible consiste à
écrire une structure générique `Radix` et ses spécialisations de sorte que `Radix<T>::value` donne la valeur attendue pour
le type `T`.

Toutes les fonctionnalités du laboratoire précédent doivent fonctionner avec le type générique, pour tous les types
non-signés de `unsigned char` à `unsigned long long` et toutes les valeurs de R que votre code annonce supporter (mais pas
seulement `R = 10`)

En plus, il doit être possible de convertir explicitement d'un `LongInt<T1,R1>` à un `LongInt<T2,R2>` avec des types
`T1, T2` et/ou des bases `R1, R2` différentes. Il est probable que cela requiert de rendre les différentes instances de
la classe génériques amies l'une de l'autre. 