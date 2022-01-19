SELECT DISTINCT name
FROM people JOIN stars ON stars.person_id = people.id
WHERE movie_id
IN(SELECT movie_id
FROM movies JOIN stars ON stars.movie_id = movies.id JOIN people ON people.id = stars.person_id
WHERE people.name = "Kevin Bacon" AND people.birth = "1958")
AND name != "Kevin Bacon";