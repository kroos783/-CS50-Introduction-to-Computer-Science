from cs50 import get_float


def main():
    change = 0.00   # def change variable in float
    while(change < 0.01):   # prompt user until good value float
        change = get_float("Change owed: ")

    cents = round(change * 100)
    print(f"Total cents: {cents}")  # print value of cents

    number_piece = 0
    while(cents > 0.00):    # give money while > 0.00
        while(cents >= 25):
            cents = cents - 25
            number_piece += 1
        while(cents >= 10):
            cents = cents - 10
            number_piece += 1
        while(cents >= 5):
            cents = cents - 5
            number_piece += 1
        while(cents >= 1):
            cents = cents - 1
            number_piece += 1

    print(f"Number of piece: {number_piece}")   # print final value number of piece


main()