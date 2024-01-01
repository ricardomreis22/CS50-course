def main():

    # Get user input
    text = input("Say soomething! ")

    result = replace(text)

    print(result)



    # Call replace function

    # Print

def replace(text):

    # Replace :) and :( for emojis
    text1 = text.replace(":)", "🙂")

    text2 = text1.replace(":(", "🙁")

    return text2

main ()
