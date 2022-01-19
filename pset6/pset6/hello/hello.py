from cs50 import get_string


# Def main function + get string + print Hello name
def main():
    name = get_string("What is your name ? ")
    print(f"hello, {name}")


# Launch main function
main()