from cs50 import get_string

passage = get_string("Text: ")
letters = 0
words = 1
sentences = 0

i = 0
while i < len(passage):
    # Count letters
    if (passage[i].isalpha()) == True:
        letters = letters + 1
    # Count words
    if passage[i] == " ":
        words += 1
    # Count sentences
    if passage[i] == "?" or passage[i] == "!" or passage[i] == ".":
        sentences += 1
    i += 1

index = (0.0588 * ((letters / words) * 100) - 0.296 * ((sentences / words) * 100) - 15.8)

if round(index) >= 1 and round(index) < 16:
    print(f"Grade {round(index)}")
elif round(index) < 1:
    print("Before Grade 1")
else:
    print("Grade 16+")