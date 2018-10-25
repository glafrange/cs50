from cs50 import get_int

# prompting user until input is valid
while(True):
    num = get_int("enter a number: ")
    if num >= 0 and num <= 23:
        break

for i in range(0, num):
    # print spaces
    for space in range(0, num - i - 1):
        print(" ", end="")
    # print bricks
    for brick in range(num - i - 1, num):
        print("#", end="")
    # print gap
    print("  ", end="")
    # print second half of bricks
    for brick in range(num - i - 1, num):
        print("#", end="")
    # new line
    print("")