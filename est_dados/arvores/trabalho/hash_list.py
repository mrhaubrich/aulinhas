#!/usr/bin/env python3


# the hash key is the first letter of the word
# the value is the word
# the hash table is a list of linked lists

import re
import sys

from rich import console as _console, pretty

from avl import AVL

pretty.install()

console = _console.Console()


class HashNode:
    next: "HashNode"
    value: AVL

    def __init__(self, value):
        self.value = value
        self.next = None

    def hash(self, value):
        return value[0].lower()

    def insert(self, value: str):
        if self.value is None:
            self.value = AVL()
        self.value.inserir(value)

    def print(self):
        if self.value is None:
            print("None")
        else:
            self.value.print()

    def get_most_occur(self):
        return self.value.get_most_occur()

    def __str__(self):
        return str(self.value)


def hash_function(value: str):
    key = remove_acentuacao(value[0].lower().strip())
    return ord(key) - 97


class HashList:
    _list: list[HashNode] = [None] * 26

    def insert(self, value: str):
        index = hash_function(value)
        if self._list[index] is None:
            self._list[index] = HashNode(AVL())
        self._list[index].insert(value)

    def print(self):
        for i in self._list:
            if i is not None:
                i.print()
            # else:
            #     print('|   None')

    def get_most_occur(self):
        most_occur = None
        most_occur_word = None
        for i in self._list:
            if i is not None:
                inner_most_occur = i.get_most_occur()
                if most_occur is None:
                    most_occur = inner_most_occur
                if inner_most_occur is not None and inner_most_occur > most_occur:
                    most_occur = i.value.get_most_occur()
        return most_occur_word

    def __str__(self):
        s = ""
        for i in self._list:
            if i is not None:
                s += str(i)
            # else:
            #     s += '|   None'
        return s
    
    def read_file(self, filename: str):
        with open(filename) as f:
            for word in remove_pontuacao(f.read()).split():
                self.insert(word.strip())


def remove_acentuacao(val: str) -> str:
    regex = re.compile(r"[áàãâä]")
    val = regex.sub("a", val)
    regex = re.compile(r"[éèêë]")
    val = regex.sub("e", val)
    regex = re.compile(r"[íìîï]")
    val = regex.sub("i", val)
    regex = re.compile(r"[óòõôö]")
    val = regex.sub("o", val)
    regex = re.compile(r"[úùûü]")
    val = regex.sub("u", val)
    return val


def remove_pontuacao(val: str) -> str:
    # not \w
    regex = re.compile(r"[^\w\s]")
    val = regex.sub("", val)
    return val


if __name__ == "__main__":
    hash_list = HashList()

    
    console.print(hash_list)
    sys.exit(0)

