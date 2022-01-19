ccNumber = ""

 
#Hello ! This code is developed by Arsalan Ghassemi for the Problem Set 6 of CS50's introduction to Computer Science's course.

#It checks the credit card number of the user's input and returns if the card is a valid AMEX, MASTERCARD or VISA.

#It first checks the length of the credit card number and if it's incorrect it returns "invalid"

#Then it checks the credit card number with Luhn's algorithm and returns "invalid" if the result does not match.

#Finally it checks the first digits of the credit card to return if the credit card type.

#Feel free to send any ameliorations suggestions at contact@arsadevs.com


def main():
    getInput()
    checkSum()
    checkType()


def getInput():
    global ccNumber
    while len(str(ccNumber)) <= 1:
        try:
            ccNumber = int(input("Number: "))
            checklength = str(ccNumber)
            length = len(checklength)
            if length != 13 and length != 15 and length != 16:
                exit("INVALID")
            else:
                break
        except ValueError:
            continue
    return 0


def checkSum():
    global ccNumber
    ccCopy = ccNumber
    sums = 0
    i = 0
    while ccCopy != 0:
        if i % 2 == 0:
            sums += ccCopy % 10
        else:
            last = (ccCopy % 10) * 2
            sums += last if last < 9 else last - 9
        i += 1
        ccCopy /= 10
        ccCopy = int(ccCopy)
    if int(sums) % 10 != 0:
        exit("INVALID")
    return 0


def checkType():
    global ccNumber
    ccType = 0
    ccType = int(str(ccNumber)[:2])
    if ccType == 34 or ccType == 37:
        print("AMEX")
    elif 51 <= ccType <= 55:
        print("MASTERCARD")
    else:
        ccType = int(str(ccNumber)[:1])
        if ccType == 4:
            print("VISA")
        else:
            exit("INVALID")
    return 0


main()