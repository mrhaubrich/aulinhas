class Node:
    valor: str = None
    quantidade: int = 1
    esquerda: "Node" = None
    direita: "Node" = None
    altura = 0

    def __init__(self, valor):
        self.valor = valor

    def __str__(self):
        return str(self.valor)

    def __repr__(self):
        return str(self.valor)

    def __eq__(self, other):
        return self.valor == other.valor

    def __ne__(self, other):
        return self.valor != other.valor

    def __lt__(self, other):
        return self.valor < other.valor

    def __le__(self, other):
        return self.valor <= other.valor

    def __gt__(self, other):
        return self.valor > other.valor

    def __ge__(self, other):
        return self.valor >= other.valor


class AVL:
    raiz: Node = None

    def altura(self, no: Node):
        if no is None:
            return -1
        return no.altura

    def fator_balanceamento(self, no: Node):
        return self.altura(no.direita) - self.altura(no.esquerda)

    def rotacao_esquerda(self, no: Node):
        nova_raiz = no.direita
        no.direita = nova_raiz.esquerda
        nova_raiz.esquerda = no
        no.altura = max(self.altura(no.esquerda), self.altura(no.direita)) + 1
        nova_raiz.altura = (
            max(self.altura(nova_raiz.esquerda), self.altura(nova_raiz.direita)) + 1
        )
        return nova_raiz

    def rotacao_direita(self, no: Node):
        nova_raiz = no.esquerda
        no.esquerda = nova_raiz.direita
        nova_raiz.direita = no
        no.altura = max(self.altura(no.esquerda), self.altura(no.direita)) + 1
        nova_raiz.altura = (
            max(self.altura(nova_raiz.esquerda), self.altura(nova_raiz.direita)) + 1
        )
        return nova_raiz

    def rotacao_dupla_esquerda(self, no: Node):
        no.direita = self.rotacao_direita(no.direita)
        return self.rotacao_esquerda(no)

    def rotacao_dupla_direita(self, no: Node):
        no.esquerda = self.rotacao_esquerda(no.esquerda)
        return self.rotacao_direita(no)

    def inserir(self, valor):
        self.raiz = self._inserir(valor, self.raiz)

    def _inserir(self, valor, no: Node):
        if no is None:
            return Node(valor)
        elif valor < no.valor:
            no.esquerda = self._inserir(valor, no.esquerda)
            if self.altura(no.esquerda) - self.altura(no.direita) == 2:
                if valor < no.esquerda.valor:
                    no = self.rotacao_direita(no)
                else:
                    no = self.rotacao_dupla_direita(no)
        elif valor > no.valor:
            no.direita = self._inserir(valor, no.direita)
            if self.altura(no.direita) - self.altura(no.esquerda) == 2:
                if valor > no.direita.valor:
                    no = self.rotacao_esquerda(no)
                else:
                    no = self.rotacao_dupla_esquerda(no)
        else:
            no.quantidade += 1
        no.altura = max(self.altura(no.esquerda), self.altura(no.direita)) + 1
        return no

    def remover(self, valor):
        self.raiz = self._remover(valor, self.raiz)

    def _remover(self, valor, no: Node):
        if no is None:
            return None
        elif valor < no.valor:
            no.esquerda = self._remover(valor, no.esquerda)
            if self.altura(no.direita) - self.altura(no.esquerda) == 2:
                if self.altura(no.direita.direita) >= self.altura(no.direita.esquerda):
                    no = self.rotacao_esquerda(no)
                else:
                    no = self.rotacao_dupla_esquerda(no)
        elif valor > no.valor:
            no.direita = self._remover(valor, no.direita)
            if self.altura(no.esquerda) - self.altura(no.direita) == 2:
                if self.altura(no.esquerda.esquerda) >= self.altura(
                    no.esquerda.direita
                ):
                    no = self.rotacao_direita(no)
                else:
                    no = self.rotacao_dupla_direita(no)
        elif no.esquerda is not None and no.direita is not None:
            no.valor = self._minimo(no.direita).valor
            no.direita = self._remover(no.valor, no.direita)
        else:
            no = no.esquerda if no.esquerda is not None else no.direita
        if no is not None:
            no.altura = max(self.altura(no.esquerda), self.altura(no.direita)) + 1
        return no

    def _minimo(self, no: Node):
        while no.esquerda is not None:
            no = no.esquerda
        return no

    def _maximo(self, no: Node):
        while no.direita is not None:
            no = no.direita
        return no

    def buscar(self, valor):
        return self._buscar(valor, self.raiz)

    def _buscar(self, valor, no: Node):
        if no is None:
            return None
        elif valor < no.valor:
            return self._buscar(valor, no.esquerda)
        elif valor > no.valor:
            return self._buscar(valor, no.direita)
        else:
            return no

    def __contains__(self, valor):
        return self.buscar(valor) is not None

    def __len__(self):
        return self._len(self.raiz)

    def _len(self, no: Node):
        if no is None:
            return 0
        return 1 + self._len(no.esquerda) + self._len(no.direita)

    def __iter__(self):
        return self._iter(self.raiz)

    def _iter(self, no: Node):
        if no is not None:
            yield from self._iter(no.esquerda)
            yield no.valor
            yield from self._iter(no.direita)

    def __repr__(self):
        return f"ArvoreAVL({self.raiz})"

    def __str__(self):
        return f"ArvoreAVL({self.raiz})"

    def __getitem__(self, valor):
        return self.buscar(valor)

    def __setitem__(self, valor, novo_valor):
        no = self.buscar(valor)
        if no is None:
            self.inserir(novo_valor)
        else:
            no.valor = novo_valor

    def __delitem__(self, valor):
        self.remover(valor)

    def __str__(self):
        return self._str("", self.raiz, None)

    def _str(self, prefix, no: Node, is_left) -> str:
        if no is not None:
            s = prefix
            s += "├──" if is_left == 1 else "└──"
            s += f"{no.valor}({no.quantidade})\n"
            new_prefix = prefix + ("|   " if is_left == 1 else "    ")
            s += self._str(new_prefix, no.esquerda, 1)
            s += self._str(new_prefix, no.direita, 0)
            return s
        return ""

    def print(self):
        print(self)

    def get_most_occur(self) -> Node or None:
        self.most_occur: Node or None = None
        return self._get_most_occur(self.raiz)
    
    def _get_most_occur(self, no: Node) -> Node or None:
        if no is not None:
            self._get_most_occur(no.esquerda)
            if self.most_occur is None:
                self.most_occur = no
            if no.quantidade > self.most_occur.quantidade:
                self.most_occur = no
            self._get_most_occur(no.direita)
        return self.most_occur


if __name__ == "__main__":
    arvore = AVL()

    for i in range(15):
        arvore.inserir(i)

    print("depois de inserir")
    arvore.print()

    for i in range(10):
        del arvore[i]

    print("depois de deletar")
    arvore.print()

    for i in range(15):
        arvore.inserir(i)

    print("depois de inserir novamente")
    arvore.print()