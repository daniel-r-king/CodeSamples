# Daniel King
# CS3180
# 11/23/2021
# This file engages the user in a game of Hangman.

import random
if __name__ == '__main__':
    print("Welcome to Hangman!")

    # Lines 6-14 attempt to open wordlist.txt and exit gracefully on failure.
    try:
        file = open("wordlist.txt", "r")
        wordHash = {}
        for line in file:
            wordHash[line.strip()] = len(line.strip())
        file.close()
    except FileNotFoundError:
        print("Oops! Looks like we couldn't find the word bank...")
        exit(-1)

    # Lines 17-29 collect and validate an input to determine the length of the magic word.
    inputValid = False
    while not inputValid:
        try:
            n = input("What length word would you like to play? ==> ")
            n = int(n)
            if n < 3:
                print("Sorry, the smallest word we've got is 3 letters long.")
            elif n > 10:
                print("Whoa there, cowboy! The biggest word we've got is only 10 letters long.")
            else:
                inputValid = True
        except ValueError:
            print("That wasn't a number...\n")

    # Lines 31-35 collect all words of the inputted length from the word list.
    words = []
    for word in wordHash:
        if wordHash[word] == n:
            words.append(word)

    # Lines 38-45 initialize variables used in the main game loop.
    nGuesses = (2 * n) - 1
    guessesRem = nGuesses
    magicWord = random.choice(words)
    lettersGuessed = []
    lettersFound = []
    starStr = ""
    for i in range(n):
        starStr += "* "
    gameOver = False

    # Main game loop begins at line 49.
    while not gameOver:
        print("WORD: " + starStr)
        print("LIVES: " + str(guessesRem))

        # Lines 54-78 collect, validate, and act on the input for the player's guess.
        inputValid = False
        win = False
        while not inputValid:
            guess = input("Type a letter or a word guess: ")

            if guess in lettersGuessed:
                print("You guessed " + guess + " before!")
            elif len(guess) >= 3 and guess == magicWord:
                inputValid = True
                win = True
            elif len(guess) >= 3 and guess != magicWord:
                print("Sorry, " + guess + " is incorrect!")
                inputValid = True
                lettersGuessed.append(guess)
                guessesRem -= 1
            elif len(guess) == 2:
                print("Hey now, one letter at a time, buddy.")
            else:
                inputValid = True
                lettersGuessed.append(guess)
                guessesRem -= 1
        if win:
            print("Congratulations, " + guess + " is correct! You win!")
            gameOver = True
            break

        # Lines 81-84 determine how many instances of the player's guess exist in the magic word.
        hitCount = 0
        for i in range(len(magicWord)):
            if magicWord[i] == guess:
                hitCount += 1

        # Lines 87-101 use the information obtained above to decide whether or not the player supplied a correct guess,
        # and act accordingly.
        letterFound = False
        if hitCount == 0:
            print("Sorry, there are no " + guess + "'s.")
        elif hitCount == 1:
            print("There is one " + guess + "!")
            letterFound = True
            if guessesRem == 0:
                print("but...")
        elif hitCount > 1:
            print("There are " + str(hitCount) + " " + guess + "'s!")
            letterFound = True
            if guessesRem == 0:
                print("but...")
        if letterFound:
            lettersFound.append(guess)

        # Lines 105-120 determine if the game is over based on the results of the previous round.
        starStr = ""
        for i in range(len(magicWord)):
            if magicWord[i] in lettersFound:
                starStr += magicWord[i] + " "
            else:
                starStr += "* "

        if "*" not in starStr:
            print("The word is complete: " + magicWord + "!")
            print("You win!")
            win = True
            gameOver = True

        if guessesRem == 0 and not win:
            print("You ran out of LIVES! You lose!")
            gameOver = True












