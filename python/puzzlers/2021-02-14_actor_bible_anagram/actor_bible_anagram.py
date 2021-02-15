#!/usr/bin/env pipenv-shebang
from python.util.utilities import extractLastWordFromList, get_repo_root_path

import os
import re
import pickle
from itertools import takewhile

import unidecode
from tqdm import tqdm


def isQualifiedActor(stringList):
    """ Determine if cast member is relevant to our search
    Example stringList:
    (nconst, primaryName, birthYear, deathYear, primaryProfession, knownForTitles)
    ["nm0000004", "John Belushi", "1949", "1982", "actor,soundtrack,writer", "tt0078723,tt0072562,tt0077975,tt0080455"]
    """
    notKnownForAnything = stringList[-1] == '\\N'
    notAnActor = 'actor' not in stringList[-2]
    isDead = stringList[-3].isdigit()
    hasNoBirthYear = stringList[-4] == '\\N'
    firstOrLastNameIsANumber = stringList[1].isdigit() or stringList[-5].isdigit()
    if notKnownForAnything or notAnActor or isDead or hasNoBirthYear or firstOrLastNameIsANumber:
        return False
    else:
        return True


def parseLine(stringList):
    """ Extracts first/last name. Makes lower case, removes accents and nonalpha characters (e.g. dashes).
    Example stringList:
    (nconst, primaryName, birthYear, deathYear, primaryProfession, knownForTitles)
    ["nm0000004", "John Belushi", "1949", "1982", "actor,soundtrack,writer", "tt0078723,tt0072562,tt0077975,tt0080455"]
    """
    regex = re.compile('[^a-zA-Z]')
    name = list(takewhile(lambda x: not x.isdigit(), stringList[1:]))
    first = unidecode.unidecode(regex.sub('', name[0].lower()))
    last = unidecode.unidecode(regex.sub('', name[-1].lower()))
    return first, last


def parseIMDB(pathToActors, pickleFile=None):
    """ Parse thru title.principals.tsv.gz from https://www.imdb.com/interfaces/ to find relevant actors
    If pickle file is availble, just loads previously parsed result.
    """
    if pickleFile and os.path.exists(pickleFile):
        elements = pickle.load(open(pickleFile, "rb"))
    else:
        file = open(pathToActors, 'r', encoding='utf-8')
        numLines = len(open(pathToActors).readlines())
        elements = []
        for line in tqdm(file, desc="Parsing all (most) actors from IMBD ... ", total=numLines):
            strippedLine = line.strip()
            splitLine = strippedLine.split()
            if isQualifiedActor(splitLine):
                elements.append(parseLine(splitLine))
    if pickleFile:
        pickle.dump(elements, open(pickleFile, "wb"))
    return elements


if __name__ == "__main__":
    # List of bible books, and same list with each element name sorted (e.g. "mark" -> "arkm")
    pathToBibleBooks = os.path.join(get_repo_root_path(), "datasets/bible_books.txt")
    bibleBooks = set(extractLastWordFromList(pathToBibleBooks, " "))
    bibleBooksSortedLetters = {"".join(sorted(book)) for book in bibleBooks}

    # List of (firstName, lastName) relevant actors
    pathToActors = os.path.join(get_repo_root_path(), "datasets/imdbActors.tsv")
    pickFileName = os.path.join(get_repo_root_path(), "datasets/imdbActors.pickle")
    actors = parseIMDB(pathToActors, pickFileName)

    sol = [(first, last) for first, last in actors
           if first in bibleBooks and last not in bibleBooks
           and "".join(sorted(last)) in bibleBooksSortedLetters]

    if sol:
        print("FOUND ANSWER(s)!")
        for first, last in sol:
            print(first, " ", last)
    else:
        print("COULDN'T FIND ANYBODY")

    print("Job's done!")
