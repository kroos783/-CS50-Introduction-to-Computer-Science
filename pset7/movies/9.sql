--Dans 9.sql, écrivez une requête SQL pour répertorier les noms de toutes les personnes qui ont joué dans un film sorti en 2004, classées par année de naissance.
    --Votre requête doit générer une table avec une seule colonne pour le nom de chaque personne.
    --Les personnes ayant la même année de naissance peuvent être répertoriées dans n'importe quel ordre.
    --Pas besoin de s'inquiéter pour les personnes qui n'ont pas d'année de naissance répertoriée, tant que celles qui ont une année de naissance sont répertoriées dans l'ordre.
    --Si une personne est apparue dans plus d'un film en 2004, elle ne devrait apparaître qu'une seule fois dans vos résultats.

SELECT name
FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON stars.movie_id = movies.id
WHERE movies.year = "2004"
GROUP BY person_id
ORDER BY birth;