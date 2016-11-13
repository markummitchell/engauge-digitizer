#!/usr/bin/python3

import os
from pprint import pprint
import sys
import xml.etree.ElementTree as etree

def main ():
    if sanityCheckInputs ():
        merge (sys.argv [1], sys.argv [2], sys.argv [3])

def merge (inCode, inTransifex, out):
    # Read translations downloaded from transifex
    (translationMapTransifex, countEmptyTransifex, countNotEmptyTransifex) = readTranslationMap (inTransifex)
    #for k, v in sorted (translationMapTransifex.items ()):
    #    print (k, "---", v)
        
    # Merge downloaded transifex into first ts file which came from code, and output it
    (countEmptyCode, countNotEmptyCode, countEmptyOut, countNotEmptyOut, countOverriddenOut) = mergeOldAndNew (
        inCode, translationMapTransifex, out)

    # Statistics
    print ("Downloaded translations:", countEmptyTransifex, "empty translations and", countNotEmptyTransifex,
           "nonempty translations")
    print ("Old code translations:", countEmptyCode, "empty translations and", countNotEmptyCode,
           "nonempty translations")
    print ("New code translations:", countEmptyOut, "empty translations and", countNotEmptyOut,
           "nonempty translations")

    
def mergeOldAndNew (inCode, translationMapTransifex, out):
    treeCode = etree.parse (inCode)
    rootCode = treeCode.getroot ()

    (countEmptyCode, countNotEmptyCode, countEmptyOut, countNotEmptyOut, countOverriddenOut) = recurseOutput (
    rootCode, translationMapTransifex)

    # Write output file. We need to insert DOCTYPE at the start of the file
    f = open (out, 'w')
    f.write ('<?xml version="1.0" encoding="UTF-8" ?><!DOCTYPE TS>\n')
    f.write (etree.tostring (rootCode, encoding='UTF-8', method='xml').decode ("utf-8")) # Convert bytes from tostring() into string
    f.close ()
    
    return (countEmptyCode, countNotEmptyCode, countEmptyOut, countNotEmptyOut, countOverriddenOut)
    
def readTranslationMap (inTransifex):
    treeTransifex = etree.parse (inTransifex)
    messagesTransifex = treeTransifex.findall ('.//message')

    countEmptyTransifex = 0
    countNotEmptyTransifex = 0
    
    translationMapTransifex = {}
    for message in messagesTransifex:
        sources = message.findall ('.//source')
        translations = message.findall ('.//translation')
        source = sources [0].text
        translation = translations [0].text
        empty = True
        if translation is not None:
            if len (translation) > 0:
                translationMapTransifex [source] = translation
                empty = False
        if empty:
            countEmptyTransifex += 1
        else:
            countNotEmptyTransifex += 1
    return (translationMapTransifex, countEmptyTransifex, countNotEmptyTransifex)

def recurseOutput (nodeCode, translationMapTransifex):
    countEmptyCode = 0
    countNotEmptyCode = 0
    countEmptyOut = 0
    countNotEmptyOut = 0
    countOverriddenOut = 0
    for child in nodeCode:
        (cEmptyCode, cNotEmptyCode, cEmptyOut, cNotEmptyOut, cOverriddenOut) = recurseOutput (child, translationMapTransifex)
        countEmptyCode += cEmptyCode
        countNotEmptyCode += cNotEmptyCode
        countEmptyOut += cEmptyOut
        countNotEmptyOut += cNotEmptyOut
        countOverriddenOut += cOverriddenOut
        if child.tag == "message":
            # Look for source and translation tags
            source = child.find ('.//source')
            translation = child.find ('.//translation')

            if source is not None and translation is not None:
                empty = True
                if translation.text is not None and len (translation.text) > 0:
                    empty = False
                if empty:
                    countEmptyCode += 1
                else:
                    countNotEmptyCode += 1
                
                # Update translation if there is a newer one
                if source.text in translationMapTransifex:
                    # Override the old value
                    translation.text = translationMapTransifex [source.text]
                    countOverriddenOut += 1

                if translation.text is not None and len (translation.text) > 0:
                    # Remove type='unfinished' if that attribute is present and not empty since now the translation is finished
                    try:
                        typeAtt = translation.attrib ["type"]
                        if typeAtt == "unfinished":
                            translation.attrib.pop ("type")
                    except KeyError:
                        pass
                
                empty = True
                if translation.text is not None and len (translation.text) > 0:
                        empty = False
                if empty:
                    countEmptyOut += 1
                else:
                    countNotEmptyOut += 1
    return (countEmptyCode, countNotEmptyCode, countEmptyOut, countNotEmptyOut, countOverriddenOut)

def sanityCheckInputs ():
    showUsage = False
    if len (sys.argv) != 4:
        showUsage = True
    else:
        if not os.path.isfile (sys.argv [1]) or not os.path.isfile (sys.argv [2]):
            showUsage = True
    rtn = True
    if showUsage:
        print ("Usage: <ts input file from git> <ts input file from transifex> <ts output file>")
        rtn = False
    return rtn
        
main ()    

