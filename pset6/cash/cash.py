from cs50 import get_float

# prompt user until non-negative number input
while(True):
    change_owed = get_float("Enter the change owed: ")
    if change_owed >= 0:
        break

# initialize variables and convert change_owed to cents
coin_list = [25, 10, 5, 1]
coins_returned = 0
change_owed *= 100

for _, coin in enumerate(coin_list):
    coins_returned += change_owed // coin
    change_owed %= coin

print(coins_returned)