#!/usr/bin/env python3


# the hash key is the first letter of the word
# the value is the word
# the hash table is a list of linked lists

import re
import sys

from rich import console as _console, pretty

from avl import AVL, Node
from hash_node import HashNode

pretty.install()

console = _console.Console()


def _hash_function(value: str):
    key = remove_acentuacao(value[0].lower().strip())
    return ord(key) - 97


class HashList:
    _list: list[HashNode | None] = [None] * 26

    def inserir(self, value: str):
        index = _hash_function(value)
        if self._list[index] is None:
            self._list[index] = HashNode(AVL())
        self._list[index].inserir(value)

    def print(self):
        for i in self._list:
            if i is not None:
                i.print()
            # else:
            #     print('|   None')

    def get_most_occur(self):
        most_occur: Node | None = None
        for i in self._list:
            if i is not None:
                node = i.get_most_occur()
                if node is not None:
                    if most_occur is None or node.quantidade > most_occur.quantidade:
                        most_occur = node
        return most_occur

    def __str__(self):
        s = ""
        for i in self._list:
            if i is not None:
                s += str(i)
        return s

    def read_file(self, filename: str):
        with open(filename, encoding='utf-8') as f:
            for word in remove_pontuacao(f.read()).split():
                self.inserir(word.strip())

    def get_one_occur(self):
        one_occur: list[Node] = []
        for i in self._list:
            if i is not None:
                node = i.value.pega_todos_com_uma_quantidade()
                if node is not None:
                    one_occur.extend(node)
        return one_occur
    
    def buscar(self, value: str):
        index = _hash_function(value)
        if self._list[index] is None:
            return None
        return self._list[index][value]


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
    regex = re.compile(r"[^\w\s]")
    val = regex.sub("", val)
    return val


if __name__ == "__main__":
    hash_list = HashList()

    hash_list.read_file("texto.txt")

    console.print(hash_list)
    sys.exit(0)
