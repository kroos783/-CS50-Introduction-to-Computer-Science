-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description
FROM crime_scene_reports
WHERE day = 28 and month = 7 and street = "Chamberlin Street";

-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

SELECT transcript FROM interviews WHERE transcript LIKE "%courthouse%";

-- I work at the courthouse, and I saw the hit-and-run on my way into work this morning.
-- I saw him talking on the phone outside the courthouse at 3:00pm.
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT name
FROM people
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
WHERE year = "2020" and month = "7" and day ="28" and hour = "10" and minute > "15" and minute <= "25" and activity = "exit";

-- suspect : Patrick, Ernest, Amber, Danielle, Roger, Elizabeth, Russell, Evelyn

SELECT name
FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_location = "Fifer Street" and year = "2020" and month = "7" and day = "28" and transaction_type = "withdraw";

-- Result : Ernest, Russell, Roy, Bobby, Elizabeth, Danielle, Madison, Victoria
-- Suspect : Ernest, Russell, Elizabeth, Danielle

SELECT name
FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE flight_id = (
SELECT flights.id
FROM flights
JOIN airports ON airports.id = flights.origin_airport_id
WHERE year = "2020" and month = "7" and day = "29"
ORDER BY hour, minute
LIMIT 1);

-- suspect : Doris, Roger, Ernest, Edward, Evelyn, Madison, Bobby, Danielle

SELECT name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60";

-- suspect : Roger, Evelyn, Ernest, Evelyn, Madison, Russell, Kimberly, Bobby, Victoria

SELECT name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE flight_id =
(SELECT id
FROM flights
WHERE day = "29" AND month = "7" AND year = "2020"
ORDER BY hour, minute
LIMIT 1)
INTERSECT
SELECT DISTINCT name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street"
INTERSECT
SELECT name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60"
INTERSECT
SELECT name
FROM people
JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit";

-- Thief : Ernest


SELECT city
FROM airports
WHERE id = (
SELECT destination_airport_id
FROM flights
WHERE year = "2020" and month = "7" and day = "29"
GROUP BY hour, minute
LIMIT 1);

-- London

SELECT name
FROM people
JOIN phone_calls ON phone_calls.receiver = people.phone_number
WHERE phone_calls.id = (
SELECT phone_calls.id
FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE year = "2020" and month = "7" and day = "28" and duration < "60" and name = "Ernest");

-- accomplice : Berthold