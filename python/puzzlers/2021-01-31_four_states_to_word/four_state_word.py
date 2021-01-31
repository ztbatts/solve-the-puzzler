import itertools as iter

from python.util.utilities import *


def loadStateAdjacencyGraph():
    pathToStateGraph = '/home/zach/solve-the-puzzler/datasets/US_State_Neighbors.txt'
    graph = {}
    file = open(pathToStateGraph, 'r', encoding='utf-8')
    for line in file:
        words = line.strip().split(" ")
        graph[words[0].lower()] = [word.lower() for word in words[1:]]
    return graph


# Checks if list of states is connected in the order given
def isConnected(stateList, stateGraph):
    state_pairs = zip(stateList[:-1], stateList[1:])
    for first, second in state_pairs:
        if first not in stateGraph or second not in stateGraph[first]:
            return False
    return True


# Checks if any ordering permutation of stateList is connected
def isAnyConnected(stateList, stateGraph):
    for states in iter.permutations(stateList, len(stateList)):
        if isConnected(states, stateGraph):
            return True
    return False


def findAllEightLetterCombos():
    pathToDict = '/home/zach/solve-the-puzzler/datasets/dictionaries/wordlist.10000.txt'
    # pathToDict = '/home/zach/solve-the-puzzler/datasets/dictionaries/words_alpha.txt'
    pathToStates = '/home/zach/solve-the-puzzler/datasets/US_States_w_abbrev.json'

    sorted_letter_dict = createMapOfSortedLettersInDictionary(pathToDict)
    states_w_abbrev = loadJson(pathToStates)

    solutions = {}

    for combo in iter.combinations(states_w_abbrev.keys(), 4):
        combo_lower = tuple(state.lower() for state in combo)
        candidate = "".join(sorted("".join(combo_lower)))

        if candidate in sorted_letter_dict:
            solutions[sorted_letter_dict[candidate]] = combo_lower

    return solutions


if __name__ == "__main__":
    state_graph = loadStateAdjacencyGraph()
    unconnected_solutions = findAllEightLetterCombos()

    sols = {word: combo
            for (word, combo) in unconnected_solutions.items()
            if isAnyConnected(combo, state_graph)}

    print("Job's done!")
