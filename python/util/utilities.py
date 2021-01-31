import json
import pickle
from pathlib import Path

from tqdm import tqdm  # progress bar


def extractFirstWordFromList(pathToFile):
    file = open(pathToFile, 'r', encoding='utf-8')
    elements = []
    for line in file:
        firstWord = line.strip().split("\t")[0].lower()
        elements.append(firstWord)
    return elements


def createPhoneticDict(pathToFile, epi, pathToSaveDict):
    if Path(pathToSaveDict).exists():
        return pickle.load(open(pathToSaveDict, "rb"))
    words = extractFirstWordFromList(pathToFile)

    phoneticDict = {}
    for word in tqdm(words, desc='Creating phonetic dictionary (word-phoneme pairs)...'):
        pronunciation = epi.transliterate(word)
        phoneticDict[pronunciation] = word
    pickle.dump(phoneticDict, open(pathToSaveDict, "wb"))
    return phoneticDict


def createMapOfSortedLettersInDictionary(pathToTxtFile):
    words = extractFirstWordFromList(pathToTxtFile)
    sortedWords = {"".join(sorted(word)): word for word in words}
    return sortedWords


def loadJson(pathToJsonFile):
    with open(pathToJsonFile) as f:
        data = json.load(f)
    return data
