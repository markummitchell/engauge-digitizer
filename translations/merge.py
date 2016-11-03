#!/usr/bin/python3

import os
import sys
import xml.etree.ElementTree as etree

def main ():
    # Sanity check inputs
    showUsage = False
    if len (sys.argv) != 4:
        showUsage = True
    else:
        if not os.path.isfile (sys.argv [1]) or not os.path.isfile (sys.argv [2]):
            showUsage = True
    if showUsage:
        print ("Usage: <ts input file from git> <ts input file from transifex> <ts output file>")
    else:
        merge (sys.argv [1], sys.argv [2], sys.argv [3])

def merge (in1, in2, out):
    # Read input files
    tree1 = etree.parse (in1)
    tree2 = etree.parse (in2)
    root1 = tree1.getroot ()
    root2 = tree2.getroot ()
    allMessages = tree2.findall ('.//message')
    downloadedSourcesTranslations = {}
    for message in allMessages:
        sources = message.findall ('.//source')
        translations = message.findall ('.//translation')
        source = sources [0].text
        translation = translations [0].text
        if translation is not None:
            downloadedSourcesTranslations [source] = translation

    # Merge into first ts file
    recurseOutput (root1, downloadedSourcesTranslations)

    # Output
    tree1.write (out)

def recurseOutput (node1, downloadedSourcesTranslations):
    for child in node1:
        recurseOutput (child, downloadedSourcesTranslations)
        if child.tag == "message":
            # Look for source and translation tags
            source = child.find ('.//source')
            translation = child.find ('.//translation')

            # Update translation if there is a newer one
            if source.text in downloadedSourcesTranslations:
                translation.text = downloadedSourcesTranslations [source.text]
    
main ()    
