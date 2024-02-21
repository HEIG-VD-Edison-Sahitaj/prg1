[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/szbdXlWJ)
# PRG1-D - Labo 3

## Exposé du problème

Le but de ce laboratoire est d'analyser l'historique des cours de plusieurs 
instruments d'investissement pour en déduire leurs performances moyenne,
min et max pour diverses durées d'investissement. 

Ces historiques sont disponibles dans le répertoire [data](./data) au format `.csv`. 
On y trouve les informations sur 4 Exchange Traded Funds (ETF) et une action.

- [QQQ](https://finance.yahoo.com/quote/QQQ), un ETF qui suit le cours de l'indice Nasdaq-100 des grandes entreprises technologiques US
- [SPY](https://finance.yahoo.com/quote/SPY), un ETF qui suit le cours de l'indice S&P 500 des 500 plus grandes entreprises US
- [SHY](https://finance.yahoo.com/quote/SHY), un ETF qui investit dans les bonds du trésor US à court terme (1 à 3 ans)
- [TLT](https://finance.yahoo.com/quote/TLT), un ETF qui investit dans les bonds du trésor US à long terme (+ de 20 ans)
- [BRK-B](https://finance.yahoo.com/quote/BRK-B), action de l'entreprise Berkshire Hathaway Inc, dirigée par Warren Buffet

Pour chacun de ces instruments, on dispose d'un fichier `.csv` qui contient l'historique journalier des cours
où chaque ligne correspond à un jour ouvrable de la bourse. Par exemple, le
fichier [QQQ.csv](./data/QQQ.csv) commence par 

~~~
Date,Open,High,Low,Close,Adj Close,Volume
1999-03-10,51.125000,51.156250,50.281250,51.062500,43.715073,5232000
1999-03-11,51.437500,51.734375,50.312500,51.312500,43.929104,9688600
1999-03-12,51.125000,51.156250,49.656250,50.062500,42.858948,8743600
~~~

Chaque ligne contient une date, le cours d'ouverture, les cours les plus hauts
et plus bas de la journée, la cours de clôture, un cours de cloture ajusté 
que nous ignorerons ici, et le volume d'actions / fonds échangés ce 
jour là. 

Pour les instruments qui distribuent des dividendes en cash (les 4 ETFs, mais pas BRK-B),
il y a un deuxième fichier dont le nom se termine par `-2.csv` qui contient
ligne par ligne les dates et montants des dividendes distribués. Par exemple,
le fichier [QQQ-2.csv](./data/QQQ-2.csv) commence par 

~~~
Date,Dividends
2003-12-24,0.014000
2004-12-17,0.379000
2005-06-17,0.035000
~~~

Toutes ces données proviennent de [https://finance.yahoo.com](https://finance.yahoo.com). 

## Logiciel a réaliser 

Vous devez écrire un logiciel qui demande à l'utilisateur dans quel 
produit il veut investir (BRK-B, QQQ, SPY, SHY ou TLT) et quelles 
durées d'investissement en mois il veut analyser.

Le programme affiche alors à la console un tableau où chaque ligne
correspond à une durée d'investissement de N mois. Il considère toutes les 
périodes de N mois présentes dans les données `.csv` et calcule 
un Return On Investment (ROI) pour chacune de ces périodes et supposant 
que l'instrument est acheté et vendu au cours de clotûre du premier et
dernier jour. 

A partir de tous ces ROIs, il calcule les ROIs moyen, minimum et maximum 
et les affiche. Il calcule aussi le ROI moyen annualisé et indique les 
dates de début d'investissement des ROIs min et max. 

Exemple d'exécution :

~~~
Dans quel produit voulez-vous investir ? BRK-B
Pas de dividendes (../data/BRK-B-2.csv illisible)
Durees a considerer en mois ? 12 24 36 48 60 120
   Nr Mois |  ROI moyen |  Annualise |    ROI min |   Date min |    ROI max |   Date max
        12 |     12.47% |     12.47% |    -50.10% | 2008/03/05 |     90.76% | 1997/04/11
        24 |     24.06% |     11.38% |    -36.64% | 2007/03/09 |    158.81% | 1996/06/27
        36 |     33.38% |     10.08% |    -24.67% | 2008/10/03 |    129.65% | 1996/06/03
        48 |     45.24% |      9.78% |    -23.64% | 2005/03/09 |    127.74% | 2000/03/10
        60 |     59.26% |      9.75% |    -26.81% | 2004/03/09 |    168.61% | 2009/03/09
       120 |    148.70% |      9.54% |     -5.21% | 1999/03/08 |    347.29% | 2012/04/10
~~~

Pour les instruments distribuant des dividendes, ceux qui sont distribués
pendant la périodes d'investissement sont conservés en cash et participent
au ROI en plus du gain ou de la perte en capital dus à la fluctuation du cours. 

## Consignes 

Votre logiciel doit gérer proprement des entrées utilisateurs erronées 
ou l'absence des fichiers demandés. Par contre, il peut supposer que 
le format des données dans les fichiers est correct. 

Il doit afficher les résultats en colonnes, avec une précision au 
centième de pourcent pour les ROIs. Les dates sont affichées au 
format YYYY/MM/DD. 

Définissez des structures ( `struct` ) pour 
- les dates
- l'ensemble des informations présentes dans une ligne d'un fichier `.csv`
- l'ensemble des informations présentes dans une ligne d'un fichier `-2.csv` 

Stoquez les informations lues depuis les fichiers dans des [std::vector](https://cplusplus.com/reference/vector/vector/) contenant
ces structures. Les seules méthodes de `std::vector` dont vous devriez avoir besoin sont
- `push_back(val)`
- `size()`
- `[index]` ou `at(index)`

Structurez votre code en fonctions bien choisies, et répartissez les 
dans plusieurs fichiers `.cpp` et `.h`. Groupez ensemble les fonctions 
qui agissent sur les mêmes structures. Entre 6 et 12 fichiers au total 
devraient suffire.

## Conseils

Ne foncez pas tête baissée mais réfléchissez à la structure de votre
programme et aux structures et fonctions dont vous aurez besoin. 

Testez que vos fonctions fonctionnent correctement AVANT de les utiliser
ailleurs dans votre code. 
