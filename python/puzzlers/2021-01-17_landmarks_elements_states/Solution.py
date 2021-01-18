#!/usr/bin/env pipenv-shebang

import itertools


def extractFirstWordFromList(pathToFile):
    file = open(pathToFile, 'r')
    elements = []
    for line in file:
        firstWord = line.strip().split("\t")[0].lower()
        elements.append(firstWord)
    return elements

def findSolution():
    landmarks = ['hooverdam', 'koreanwar']  # any other ideas?
    atomicElements = extractFirstWordFromList('/home/zach/solve-the-puzzler/datasets/atomic_elements.txt')
    states = extractFirstWordFromList('/home/zach/solve-the-puzzler/datasets/US_States.txt')

    # Try a brute force approach
    for landmark in landmarks:
        for elem in atomicElements:
            chars = landmark + elem
            twoStateCombos = itertools.combinations(states, 2)
            for combo in twoStateCombos:
                print('Landmark: ' + landmark + ', Element: ' + elem + ', states: ' + combo[0] + ', ' + combo[1])
                if sorted(combo[0] + combo[1]) == sorted(chars):
                    print('Found the two states!')
                    return elem, combo[0], combo[1]



    print("Job's done!")


if __name__ == "__main__":
    elem, firstState, secondState = findSolution()