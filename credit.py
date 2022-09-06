from cs50 import get_int

counter = 1
sum1 = 0
sum2 = 0
cardNum = get_int("Number: ")
strCardNum = str(cardNum)
for i in range(1, len(strCardNum) + 1, 1):
    lastNum = cardNum % 10

    if i % 2 == 0:
        if (lastNum * 2) >= 10:
            sum1 += (((lastNum*2) % 10) + 1)
        else:
            sum1 += (lastNum*2)

    elif i % 2 == 1:
        sum2 += lastNum

    cardNum = (cardNum - lastNum) / 10

total = sum1 + sum2

if total % 10 == 0:
    if len(strCardNum) == 15 and strCardNum[0] == '3' and (strCardNum[1] == '4' or strCardNum[1] == '7'):
        print("AMEX")
    elif len(strCardNum) == 16 and strCardNum[0] == '5' and 1 <= int(strCardNum[1]) <= 5:
        print("MASTERCARD")
    elif (len(strCardNum) == 13 or len(strCardNum) == 16) and strCardNum[0] == '4':
        print("VISA")
else:
    print(len(strCardNum))
    print("INVALID")