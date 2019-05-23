import System.Environment

main = do
     contents <- getContents
     mapM putStrLn (map show (filterPrimes (map read (lines contents))))

     
data PrimalityTester = PrimalityTester [Integer] 
instance Show PrimalityTester where
    show (PrimalityTester ls) = "primes: " ++ (show $ reverse ls)

newPrimalityTester :: PrimalityTester 
newPrimalityTester = PrimalityTester [3,2]

getPrimes :: PrimalityTester -> [Integer]
getPrimes (PrimalityTester ls) = reverse ls

getLast :: PrimalityTester -> Integer
getLast (PrimalityTester (x:xs)) = x

hasDivisor :: PrimalityTester -> Integer -> Bool
hasDivisor (PrimalityTester ls) n = any (divides n) primes
    where divides n = (\x -> mod n x == 0)
          primes = filter (\x -> x * x <= n) $ reverse ls


oddsAhead :: PrimalityTester -> [Integer]
oddsAhead (PrimalityTester (x:xs)) = filter odd [(x + 2)..]

nextPrime :: PrimalityTester -> Integer
nextPrime tester = head candidates
    where candidates = filter (not . hasDivisor tester) largerNums
          largerNums = oddsAhead tester

addNextPrime :: PrimalityTester -> PrimalityTester
addNextPrime (PrimalityTester ls) = PrimalityTester (next : ls)
    where next = nextPrime (PrimalityTester ls)

expandBounded :: PrimalityTester -> Integer -> PrimalityTester
expandBounded (PrimalityTester (x:xs)) n =  if x * x >= n
                               then tester
                               else expandBounded (addNextPrime tester) n
    where tester = PrimalityTester (x:xs)

primesBounded :: Integer -> [Integer]
primesBounded n = getPrimes (expandBounded newPrimalityTester (n * n))

isPrime :: PrimalityTester -> Integer -> Bool
isPrime tester  n =  n < 4 || not (hasDivisor tester n)

filterPrimes :: [Integer] -> [Integer]
filterPrimes ls = filter (\n -> isPrime tester n) ls
    where tester = expandBounded newPrimalityTester (maximum ls)
