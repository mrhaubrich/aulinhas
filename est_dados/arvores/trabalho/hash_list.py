#!/usr/bin/env python3


# the hash key is the first letter of the word
# the value is the word
# the hash table is a list of linked lists

import re
import sys

from rich import console as _console, pretty

from avl import AVL, Node
from hash_node import HashNode
from utils import remove_acentuacao, remove_pontuacao

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

    def print(self, reverse=False):
        lista = reversed(self._list) if reverse else self._list
        for i in lista:
            if i is not None:
                i.print()

    def print_with_letter(self, letter, reverse=False):
        lista = reversed(self._list) if reverse else self._list
        for i in lista:
            if i is not None:
                if i.value[0].valor[0] == letter:
                    i.print()

    def to_list_with_letter(self, letter: str, reverse=False):
        lista = reversed(self._list) if reverse else self._list
        _lista: list[Node] = []

        for i in lista:
            if i is not None:
                if remove_acentuacao(
                    remove_pontuacao(i.value.first().valor[0].lower())
                ) == remove_acentuacao(remove_pontuacao(letter.lower())):
                    _lista.extend(i.to_list(reverse))

        return _lista

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

    def __getitem__(self, value: str) -> Node | None:
        return self._buscar(value)

    def read_file(self, filename: str):
        with open(filename, encoding="utf-8") as f:
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

    def _buscar(self, value: str):
        index = _hash_function(value)
        if self._list[index] is None:
            return None
        return self._list[index][value]

    def remover(self, value: str) -> bool:
        index = _hash_function(value)
        if self._list[index] is None:
            return False
        return self._list[index].remover(value)

    def __len__(self):
        # if item is none return 0
        return sum(len(i) for i in self._list if i is not None)


if __name__ == "__main__":
    hash_list = HashList()

    hash_list.read_file("texto.txt")

    console.print(hash_list)
    sys.exit(0)
