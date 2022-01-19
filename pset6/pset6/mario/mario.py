from cs50 import get_int


# def main function
def main():
    height = 0
    while (height < 1 or height > 8):  # make a loop with condition
        height = get_int("Height: ")

    for i in range(0, height):  # make a "array"
        for j in range(0, height):
            if j < height - i - 1:
                print(" ", end="")  # print without auto \n
            else:
                print("#", end="")  # print without auto \n
        print()  # print to new line array


main()