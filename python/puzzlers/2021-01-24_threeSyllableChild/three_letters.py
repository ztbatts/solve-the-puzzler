#!/usr/bin/env pipenv-shebang
from python.util.utilities import *

import epitran  # https://github.com/dmort27/epitran

import os
import itertools as iter


def findSolutions(alphabet, epi, phoneticDict):
    solutions = []

    for combo in tqdm(iter.permutations(alphabet, 3), desc='Trying different letter permutations', total=26 ** 3):
        phonetics = []
        for letter in combo:
            phonetics.append(epi.transliterate(letter))
        pronunciation = "".join(phonetics)
        if pronunciation in phoneticDict:
            solutions.append("".join(combo))
            print(combo, pronunciation)

    return solutions


if __name__ == "__main__":
    """ For this to run, please follow the "Installation of Flite (for English G2P) >> lex_lookup" section of 
        https://github.com/dmort27/epitran#installation-of-flite-for-english-g2p
    """

    epi = epitran.Epitran('eng-Latn')

    # pathToDict = os.path.join(get_repo_root_path(), "datasets/dictionaries/words_alpha.txt")
    pathToDict = os.path.join(get_repo_root_path(), "datasets/dictionaries/wordlist.10000.txt")
    # pathToDict = os.path.join(get_repo_root_path(), "datasets/dictionaries/engmix.txt")

    phoneticDictPicklePath = pathToDict + '.withPhonemes.pickle'
    phoneticDict = createPhoneticDict(pathToDict, epi, phoneticDictPicklePath)

    alphabet = 'abcdefghijklmnopqrstuvwxyz'  # Only includes english! Not (e.g.) greek!

    sols = findSolutions(alphabet, epi, phoneticDict)

    print("Job's done!")
