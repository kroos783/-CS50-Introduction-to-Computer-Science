SELECT title, rating
FROM movies
JOIN ratings
ON ratings.movie_id = movies.id
WHERE year
LIKE "2010"
ORDER BY rating DESC, title ASC;