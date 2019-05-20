primalityTester :: [Integer] -> ([Integer] -> a) -> a
primalityTester ls = (\f -> f ls)

-- type PrimalityTester = ([Integer] -> a) -> a
newPrimalityTester :: ([Integer] -> a) -> a
newPrimalityTester = primalityTester [3,2]

ttr = newPrimalityTester

getLast :: (([Integer] -> Integer) -> Integer) -> Integer
getLast tester = tester head

getPrimes :: (([Integer] -> [Integer]) -> [Integer]) -> [Integer]
getPrimes tester = tester reverse

addOne :: (([Integer] -> [Integer]) -> [Integer]) -> Integer -> ([Integer] -> a) -> a
addOne tester i = primalityTester (i:oldPrimes)
   where oldPrimes = getPrimes tester

divides :: Integer -> Integer -> Bool
divides x y = mod y x == 0

--hasDivisor :: (([Integer] -> [Integer]) -> [Integer]) -> Integer -> Bool
hasDivisor tester n =  hasDivisorIn primes n
  where primes = getPrimes tester

hasDivisorIn :: [Integer] -> Integer -> Bool
hasDivisorIn ls n =  any (\x -> x*x <= n && divides x n) ls

-- --foo :: (([Integer] -> a) -> a) -> Integer
-- foo tester = filter bar oddsAhead
--   where testerPrimes = getPrimes tester
--         bar = (\x -> hasDivisorIn testerPrimes x)
--         oddsAhead = map (2*) [(succ nextNum)..]
--         nextNum = getLast tester

--oddsAhead :: (([Integer] -> a) -> a) -> [Integer]
oddsAhead tester = map (\x -> 2*x + 1) [(div nextNum 2)..]
  where nextNum = 2 + getLast tester

-- foo tester = take 123 $ filter fun oddNums
--   where fun = (\num -> hasDivisor tester num)
--         oddNums = oddsAhead tester

-- -- foo1 tester = take 1 primesAhead
-- --   where primesAhead = filter (\x -> hasDivisor tester x) (foo0 tester)
