from nltk.tokenize import sent_tokenize


def lines(a, b):
    similar_lines = []
    # split lines into array
    a = a.split('\n')
    b = b.split('\n')

    # check if sentence is similar and not a duplicate
    for _, sentence in enumerate(a):
        if sentence in b and sentence not in similar_lines:
            similar_lines.append(sentence)

    return similar_lines


def sentences(a, b):
    # sent_tokenize breaks strings into sentences
    a_sentences = sent_tokenize(a)
    b_sentences = sent_tokenize(b)
    similar_sentences = []

    # check if sentence is similar and not duplicate
    for _, sentence in enumerate(a_sentences):
        if sentence in b_sentences and sentence not in similar_sentences:
            similar_sentences.append(sentence)

    return similar_sentences


def substrings(a, b, n):
    similar_substr = []
    a_substrings = []
    b_substrings = []

    # break strings into substrings
    for i in range(0, len(a) - n + 1):
        a_substrings.append(a[i:i+n])

    for i in range(0, len(b) - n + 1):
        b_substrings.append(b[i:i+n])

    # check if substrings are similar and not duplicate
    for _, substr in enumerate(a_substrings):
        if substr in b_substrings and substr not in similar_substr:
            similar_substr.append(substr)

    for _, substr in enumerate(b_substrings):
        if substr in a_substrings and substr not in similar_substr:
            similar_substr.append(substr)

    return similar_substr