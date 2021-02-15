#!/usr/bin/env pipenv-shebang
import os
import itertools as iter

from python.util.utilities import *


def loadStateAdjacencyGraph(pathToStateGraph):
    """ returns a dict with (all lower-case):
        Key = Single US state
        Value = List of states that are physically connected to the key state
    """
    graph = {}
    file = open(pathToStateGraph, 'r', encoding='utf-8')
    for line in file:
        words = line.strip().split(" ")
        graph[words[0].lower()] = [word.lower() for word in words[1:]]
    return graph


def isConnected(stateList, stateGraph):
    """ Checks if list of states is connected in the order given """
    state_pairs = zip(stateList[:-1], stateList[1:])
    for first, second in state_pairs:
        if first not in stateGraph or second not in stateGraph[first]:
            return False
    return True


def isAnyConnected(stateList, stateGraph):
    """ Checks if any ordering permutation of stateList is connected """
    for states in iter.permutations(stateList, len(stateList)):
        if isConnected(states, stateGraph):
            return True
    return False


def findAllEightLetterCombos(sorted_letter_dict, states_w_abbrev):
    solutions = {}
    for combo in iter.combinations(states_w_abbrev.keys(), 4):
        combo_lower = tuple(state.lower() for state in combo)
        candidate = "".join(sorted("".join(combo_lower)))

        if candidate in sorted_letter_dict:
            solutions[sorted_letter_dict[candidate]] = combo_lower

    return solutions


if __name__ == "__main__":
    # pathToDict = os.path.join(get_repo_root_path(), "datasets/dictionaries/words_alpha.txt")
    pathToDict = os.path.join(get_repo_root_path(), "datasets/dictionaries/wordlist.10000.txt")
    # pathToDict = os.path.join(get_repo_root_path(), "datasets/dictionaries/engmix.txt")
    sorted_letter_dict = createMapOfSortedLettersInDictionary(pathToDict)

    pathToStates = os.path.join(get_repo_root_path(), "datasets/US_States_w_abbrev.json")
    states_w_abbrev = loadJson(pathToStates)

    unconnected_solutions = findAllEightLetterCombos(sorted_letter_dict, states_w_abbrev)

    pathToStateGraph = os.path.join(get_repo_root_path(), "datasets/US_State_Neighbors.txt")
    state_graph = loadStateAdjacencyGraph(pathToStateGraph)

    sols = {word: combo
            for (word, combo) in unconnected_solutions.items()
            if isAnyConnected(combo, state_graph)}

    for word, combo in sols.items():
        print(word, combo)

    print("Job's done!")
