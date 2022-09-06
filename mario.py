from cs50 import get_int
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

for i in range(height):
    # spaces
    for j in range(height - 1, i, -1):
        print(" ", end="")
    # Right aligned hashes
    for k in range(-1, i, 1):
        print("#", end="")

    print("  ", end="")

    # Left aligned hashes
    for h in range(-1, i, 1):
        print("#", end="")
    print()