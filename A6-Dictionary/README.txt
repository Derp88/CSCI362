1. Make sure the program is executed with the first argument being the name of the file.
    ex: ./dictionary Dictionary.txt
2. Enter the word you want to search
    2.1 If the word is found, the program retursn true and print words starting with same 2 letters
    2.2 If the word is not found, but there is a suitable alternative, the user is asked if the alternative is correct.
        2.2.1 If the user answers yes, return all other words with the same starting 2 letters
        2.2.2 If the user enters false, the program returns false
    2.3 If the word is not found return false


OTHER CASES:
 - If a word only contains one letter, we treat still as normal. We try to find it in the dictionary, if not we try to find alternatives.