main = do
    contents <- getContents
    mapM_ putStrLn $ words contents
