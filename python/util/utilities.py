import json
import pickle
from pathlib import Path

from tqdm import tqdm  # progress bar
import git

def get_repo_root_path():
    git_repo = git.Repo(__file__, search_parent_directories=True)
    git_root = git_repo.git.rev_parse("--show-toplevel")
    return git_root

def extractLastWordFromList(pathToFile, separator="\t"):
    file = open(pathToFile, 'r', encoding='utf-8')
    elements = []
    for line in file:
        firstWord = line.strip().split(separator)[-1].lower()
        elements.append(firstWord)
    return elements

def extractFirstWordFromList(pathToFile, separator="\t"):
    file = open(pathToFile, 'r', encoding='utf-8')
    elements = []
    for line in file:
        firstWord = line.strip().split(separator)[0].lower()
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
