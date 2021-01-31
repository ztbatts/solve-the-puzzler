#!/usr/bin/env pipenv-shebang
import itertools as iter

import epitran

from python.util.utilities import *


def findSolutions():
    epi = epitran.Epitran('eng-Latn')
    # x = epi.transliterate('there')
    x = epi.transliterate(u'Berkeley')
    # pathToDict = '/home/zach/solve-the-puzzler/datasets/dictionaries/engmix.txt'
    # pathToDict = '/home/zach/solve-the-puzzler/datasets/dictionaries/wordlist.10000.txt'
    pathToDict = '/home/zach/solve-the-puzzler/datasets/dictionaries/words_alpha.txt'
    savePath = pathToDict + '.withPhonemes.pickle'
    phoneticDict = createPhoneticDict(pathToDict, epi, savePath)

    solutions = []

    alphabet = 'abcdefghijklmnopqrstuvwxyz'
    for combo in tqdm(iter.permutations(alphabet, 3), desc='trying different letter permutations', total=26 ** 3):
        phonetics = []
        for letter in combo:
            phonetics.append(epi.transliterate(letter))
        pronunciation = "".join(phonetics)
        if pronunciation in phoneticDict:
            solutions.append("".join(combo))
            print(combo, pronunciation)

    return solutions


if __name__ == "__main__":
    sols = findSolutions()
    print("Job's done!")
