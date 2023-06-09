from avl import AVL


class HashNode:
    def __init__(self, value):
        self.value: AVL = value
        self.next: "HashNode" = None

    def inserir(self, value: str):
        if self.value is None:
            self.value = AVL()
        self.value.inserir(value)

    def remover(self, value: str):
        return self.value.remover(value)

    def get_most_occur(self):
        return self.value.pega_node_com_maior_quantidade()

    def __str__(self):
        return str(self.value)

    def __getitem__(self, value: str):
        return self.value[value]

    def __len__(self):
        if self.value is None:
            return 0
        return len(self.value)

    def to_str(self, reverse=False):
        return self.value.to_str(reverse)

    def to_list(self, reverse=False):
        lista = list(iter(self.value))
        if reverse:
            lista.reverse()
        return lista

    def first(self):
        return self.value.first()

    def print(self):
        if self.value is not None:
            print(self.value)
