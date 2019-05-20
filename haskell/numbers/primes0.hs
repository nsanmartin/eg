primalityTester :: [Integer] -> ([Integer] -> a) -> a
primalityTester primes = \msg -> msg primes

-- type PrimalityTester = ([Integer] -> a) -> a
newPrimalityTester :: ([Integer] -> a) -> a
newPrimalityTester = primalityTester [3,2]

ttr = newPrimalityTester

getPrimes :: (([Integer] -> [Integer]) -> [Integer]) -> [Integer]
getPrimes tester = tester reverse

getLast :: (([Integer] -> [Integer]) -> [Integer]) -> Integer
getLast tester = head $ tester id


hasDivisor :: (([Integer] -> [Integer]) -> [Integer]) -> Integer -> Bool
hasDivisor tester n =  any (\x -> x*x <= n && divides x n) primes
  where primes = getPrimes tester
        divides = (\x y -> mod y x == 0)


oddsAhead :: (([Integer] -> [Integer]) -> [Integer]) -> [Integer]
oddsAhead tester = filter odd [nextNum..]
  where nextNum = 2 + getLast tester

nextPrime :: (([Integer] -> [Integer]) -> [Integer]) -> Integer
nextPrime tester = head candidates
  where candidates
          = filter (\n -> not $ hasDivisor tester n) (oddsAhead tester)

addNextPrime tester = primalityTester (next : previousOnes)
  where next = nextPrime tester
        previousOnes = tester id

expandBounded tester n =
  if lastPrime * lastPrime  >= n then tester
  else expandBounded (addNextPrime tester) n
  where lastPrime = getLast tester


                    
isPrime n = not $ hasDivisor tester n
  where tester = expandBounded newPrimalityTester n
