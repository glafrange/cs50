from cs50 import get_int


card_number = get_int("Enter card number: ")

modulo = 100
sum = 0

while(modulo < card_number * 10):
    product = ((card_number % modulo) // (modulo // 10)) * 2
    sum += product if (product < 10) else (1 + product % 10)
    modulo *= 100

modulo = 10

while(modulo < card_number * 10):
    next_num = (card_number % modulo) // (modulo // 10)
    sum += next_num
    modulo *= 100

card_length = len(str(card_number))
first_nums = (card_number % (pow(10, card_length)) // pow(10, card_length - 2))

if sum % 10 != 0:
    print("INVALID")
elif first_nums > 50 and first_nums < 56 and card_length == 16:
    print("MASTERCARD")
elif (first_nums == 34 or first_nums == 37) and card_length == 15:
    print("AMEX")
elif first_nums // 10 == 4 and (card_length == 16 or card_length == 13):
    print("VISA")
else:
    print("INVALID")