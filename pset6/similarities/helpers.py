from nltk.tokenize import sent_tokenize

def lines(a, b):
    similar_lines = []
    a = a.split('\n')
    b = b.split('\n')

    print(a)

    for i in range(len(a)):
        if a[i] == b[i]:
            similar_lines.append(a[i])

    print(similar_lines)
    return similar_lines


def sentences(a, b):
    a_sentences = sent_tokenize(a)
    b_sentences = sent_tokenize(b)
    similar_sentences = []

    for i in range(len(a_sentences)):
        if a_sentences[i] == b_sentences[i]:
            similar_sentences.append(a_sentences[i])

    print(similar_sentences)
    return similar_sentences


def substrings(a, b, n):

    return []


substrings("abc. bde", "abc. def", 3)