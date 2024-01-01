from cs50 import get_int


def main():
    # buscar altura dada pelo user
    height = get_height()
    for i in range(1, height + 1, 1):
        print(" " * (height - i) + "#" * (i) + "  " + "#"*(i))

# obter input de altura de user


def get_height():
    # Enquanto se verificar return n
    while True:
        try:
            # Pedir input e verificar se esta entre 0 e 9
            n = int(input("Height: "))
            if n > 0 and n < 9:
                break
        # Se o user nao der um intenger
        except ValueError:
            print("That's not an integer")
    return n


main()
