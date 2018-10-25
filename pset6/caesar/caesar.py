from cs50 import get_string
import sys


def main():
    # exit if correct number of arguments are not supplied
    if len(sys.argv) != 2:
        sys.exit(1)
    # modulo 26 to ensure key doesn't exceed one iteration of the alphabet
    key = int(sys.argv[1]) % 26
    plaintext = get_string("plaintext: ")
    ciphertext = ""
    for char in plaintext:
        ciphertext += addKey(char, key)
    print("ciphertext:", ciphertext)


# Applies key to a character in the plaintext
def addKey(char, key):
    ascii = ord(char)
    # leave non-alphabetic characters unchanged
    if ascii < 65 or (ascii > 90 and ascii < 97) or ascii > 122:
        return chr(ascii)
    ascii += key
    if ascii < 65 or (ascii > 90 and ascii < 97) or ascii > 122:
        return chr(ascii - 26)
    return chr(ascii)


if __name__ == "__main__":
    main()