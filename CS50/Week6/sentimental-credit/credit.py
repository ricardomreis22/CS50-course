from cs50 import get_int

n = get_int("Numero do cartao: ")
m = n
b = m
mult = 0
soma = 0

i = 1

while n > 0:

    digit = n % 10

    if i % 2 == 0:

        aux1 = digit * 2

        if aux1 > 9:

            aux2 = (aux1 % 10) + (aux1 // 10)

        else:

            aux2 = aux1

        mult = mult + aux2

    elif i % 2 != 0:

        soma = soma + digit

    i += 1

    n = int(n) // 10

if (mult + soma) % 10 != 0:

    print("INVALID")

else:

    while m > 100:

        m = m // 10

    if m == 34 or m == 37 and len(str(b)) == 15:

        print("AMEX")

    elif m == 51 or m == 52 or m == 53 or m == 54 or m == 55 and len(str(b)) == 16:

        print("MASTERCARD")

    elif m // 10 == 4 and len(str(b)) == 13 or len(str(b)) == 16:

        print("VISA")

    else:

        print("INVALID")