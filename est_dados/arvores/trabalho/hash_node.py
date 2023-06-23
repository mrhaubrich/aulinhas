from avl import AVL


class HashNode:
    next: "HashNode"
    value: AVL

    def __init__(self, value):
        self.value = value
        self.next = None

    def hash(self, value):
        return value[0].lower()

    def inserir(self, value: str):
        if self.value is None:
            self.value = AVL()
        self.value.inserir(value)

    def print(self):
        if self.value is None:
            print("None")
        else:
            self.value.print()

    def get_most_occur(self):
        return self.value.pega_node_com_maior_quantidade()

    def __str__(self):
        return str(self.value)
    
    def __getitem__(self, value):
        return self.value[value]