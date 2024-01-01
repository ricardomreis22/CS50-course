-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Descricao dos crimes que houveram no dia 28 de 07 de 2021 na Humphrey Street

SELECT description FROM crime_scene_reports WHERE  year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

-- Descricao do roubo: "Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time - each of their interview transcripts mentions the bakery."

-- Ver o relatorio das testumhas

SELECT transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';

-- 1st Transcript: " Sometime within tem minutes of the theft, i saw the thief get into a car in the bakery parking lot and drive away.
-- If you have a security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame."

-- Ver as pessoas que tem carros com matricula das que sairam do parque do assalto
SELECT name
FROM people
WHERE license_plate
IN
    (SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 and activity = "exit");

-- Suspeitos: Vanessa Barry Iman Sofia Luca Diana Kelsey Bruce


-- 2nd transcript: " I dont know the thiefs name, but it was someone i recognized. Earlier this morning, before i arrived at Emmas bakery,
-- i was walking by the ATM on Legget Street and saw the thief there withdrawing some money."


-- Ver as pessoas que levantaram dinheiro naquele ATM

SELECT name
FROM people p
JOIN bank_accounts ba
ON ba.person_id = p.id
WHERE account_number
IN
    (SELECT account_number
    FROM atm_transactions
    WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw');

-- Suspeitos: Bruce Diana Iman Luca

SELECT name
FROM people p
JOIN bank_accounts ba ON ba.person_id = p.id
JOIN atm_transactions atm ON atm.account_number = ba.account_number
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';


--3rd transcript: " As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, i heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket."

-- Ver nome de pessoas que fizeram chamadas no dia do roubo com duracao menor que 60 segs

SELECT DISTINCT name
FROM people
WHERE phone_number
IN (SELECT caller
    FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration <60);

-- Suspeitos: Diana Bruce

-- Ver nomes das pessoas que viajaram no 1 voo do dia seguinte
SELECT name
FROM people
WHERE passport_number
IN
    (SELECT passport_number
    FROM passengers
    WHERE flight_id
    IN
        (SELECT id
        FROM flights
        WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")
    ORDER BY hour, minute ASC
    LIMIT 1));

-- Thief: Bruce



-- Cidade para onde ladrao fugiu
SELECT city
FROM airports
WHERE id = (SELECT destination_airport_id
            FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")
ORDER BY hour, minute ASC
LIMIT 1);


-- New York City


-- Cumplice

SELECT DISTINCT name
FROM people
WHERE phone_number = (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <60 AND caller = (SELECT phone_number FROM people WHERE name = 'Bruce'));


-- Cumplice: Robin


-- Suspeitos tudo junto (nao necessario)

SELECT *
FROM bank_accounts ba
JOIN people p
ON p.id = ba.person_id
WHERE ba.account_number
IN
    (SELECT account_number
    FROM atm_transactions
    WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')
AND p.license_plate
IN
    (SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND  minute >= 15 AND minute <= 25 AND activity = 'exit')
AND p.phone_number
IN
    (SELECT caller
    FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration <60 )
AND p.passport_number
IN
    (SELECT passport_number
    FROM passengers
    WHERE flight_id
    IN
        (SELECT id
        FROM flights
        WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29
        ORDER BY hour, minute ASC
        LIMIT 1));
