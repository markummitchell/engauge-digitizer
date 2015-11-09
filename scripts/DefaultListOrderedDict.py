# Dictionary that maintains key order like OrderedDict, and is able to store lists as values like defaultdict

from collections import OrderedDict

class DefaultListOrderedDict(OrderedDict):
    def __missing__(self,k):
        self[k] = []
        return self[k]
