#!/usr/bin/env pipenv-shebang
import os
import itertools
from python.util.utilities import *


def findSolutions(atomicElements, states, landmarks):
    # Brute force approach
    solutions = []
    for landmark in landmarks:
        for elem in atomicElements:
            chars = landmark + elem
            twoStateCombos = itertools.combinations(states, 2)
            for combo in twoStateCombos:
                print('Landmark: ' + landmark + ', Element: ' + elem + ', states: ' + combo[0] + ', ' + combo[1])
                if sorted(combo[0] + combo[1]) == sorted(chars):
                    print('Found the two states!')
                    solutions.append((landmark, elem, combo[0], combo[1]))

    return solutions


if __name__ == "__main__":
    landmarks = ['hooverdam']  # any other ideas? 'koreanwar'?

    pathToElements = os.path.join(get_repo_root_path(), "datasets/atomic_elements.txt")
    atomicElements = extractFirstWordFromList(pathToElements)

    pathToStates = os.path.join(get_repo_root_path(), "datasets/US_States.txt")
    states = extractFirstWordFromList(pathToStates)

    sols = findSolutions(atomicElements, states, landmarks)

    print("Job's done!")

    for sol in sols:
        landmark, elem, firstState, secondState = sol
        print('Landmark: ' + landmark + ', Element: ' + elem + ', states: ' + firstState + ', ' + secondState)
