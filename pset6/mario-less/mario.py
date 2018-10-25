from cs50 import get_int

# prompt user until valid number input
while(True):
    height = get_int("Enter height: ")
    if height >= 0 and height <= 23:
        break
# iterate through height
for row in range(0, height):
    # print spaces
    for space in range(0, height - row - 1):
        print(" ", end="")
    # print blocks
    for block in range(height - row - 2, height):
        print("#", end="")
    # new line
    print("")