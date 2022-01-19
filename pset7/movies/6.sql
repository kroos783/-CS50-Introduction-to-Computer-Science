SELECT AVG(rating)
FROM ratings
JOIN movies
ON movies.id = ratings.movie_id
WHERE year
LIKE "2012";