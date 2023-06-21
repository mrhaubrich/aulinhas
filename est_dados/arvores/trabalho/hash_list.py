# the hash key is the first letter of the word
# the value is the word
# the hash table is a list of linked lists

from avl import AVL


class HashNode:
    key: str
    next: "HashNode"
    value: AVL

    def __init__(self, key, value):
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
            print('None')
        else:
            self.value.print()

    def __str__(self):
        return str(self.value)
    
class HashList:
    _list: list[HashNode] = [None] * 26

    def insert(self, value: str):
        key = value[0].lower()
        index = ord(key) - 97
        if self._list[index] is None:
            self._list[index] = HashNode(key, AVL())
        self._list[index].insert(value)


    def print(self):
        for i in self._list:
            if i is not None:
                i.print()

if __name__ == '__main__':
    hash_list = HashList()

    hash_list.insert('alface')

    hash_list.insert('banana')

    hash_list.insert('carambola')

    hash_list.insert('abacate')

    hash_list.insert('abacaxi')

    hash_list.insert('avestruz')

    hash_list.insert('aviao')

    hash_list.insert('aa')

    hash_list.print()
    
