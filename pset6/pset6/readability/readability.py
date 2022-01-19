from cs50 import get_string


def main():  # def main function
    text = get_string("Text: ")
    letters = count_letters(text)
    print(f"{letters} letter(s)")
    words = count_words(text)
    print(f"{words} word(s)")
    sentences = count_sentences(text)
    print(f"{sentences} sentence(s)")
    L = float(letters) / float(words) * 100
    S = float(sentences) / float(words) * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    if(index > 16):
        print("Grade 16+")
    elif(index < 1):
        print("Before Grade 1")
    elif(index < 16 and index > 1):
        print(f"Grade {round(index)}")


def count_letters(text):
    letters = 0
    i = 0
    for i in range(i, len(text)):   # boucle to 0 char to len string
        if text[i].isalpha() == True:   # check if is alpha per each char
            letters += 1
            i += 1
    return letters


def count_words(text):
    words = 1
    i = 0
    for i in range(i, len(text)):   # boucle again to check
        if(" " == text[i]):   # check if is a space for count a word
            words += 1
            i += 1
    return words


def count_sentences(text):
    sentences = 0
    i = 0
    for i in range(i, len(text)):   # boucle again to check
        if("." == text[i] or "?" == text[i] or "!" == text[i]):  # check if its end of sentence
            sentences += 1
            i += 1
    return sentences


main()