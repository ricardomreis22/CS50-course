from cs50 import get_string
# Text from user
text = get_string("Text: ")

# count letters
letters = words = sentences = 0

# add letters to counter for every letter in text
for char in text:
    if char.isalpha():
        letters += 1
    if char.isspace():
        words += 1
    if char in ["?", ".", "!"]:
        sentences += 1

words += 1
# letras em 100 palavras
l = letters * 100 / words

# frases em 100 palavras
s = sentences * 100 / words

# index
index = 0.0588 * l - 0.296 * s - 15.8

# nota e classficacao
grade = round(index)

if index < 1:
    print("Before Grade 1")

elif index > 16:
    print("Grade 16+")

else:
    print("Grade ", grade)

