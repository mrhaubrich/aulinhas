from typing import Generator, Tuple

from utils import remove_acentuacao, remove_pontuacao


class Node:
    """
    Representa um nó em uma árvore AVL.

    Atributos:
        valor (str): O valor armazenado no nó.
        quantidade (int): A quantidade de ocorrências do valor no nó.
        esquerda (Node): Referência para o nó filho da esquerda.
        direita (Node): Referência para o nó filho da direita.
        altura (int): A altura do nó na árvore.

    Métodos:
        __init__(valor: str): Inicializa um novo objeto Node.
        __str__(): Retorna uma representação em string do valor do nó.
    """
    valor: str
    quantidade: int
    esquerda: "Node"
    direita: "Node"
    altura: int

    def __init__(self, valor):
        """
        Inicializa um novo objeto Node.

        Args:
            valor (str): O valor a ser armazenado no nó.
        """
        self.valor = valor
        self.quantidade = 1
        self.esquerda = None
        self.direita = None
        self.altura = 0

    def __str__(self):
        """
        Retorna uma representação em string do valor do nó.

        Returns:
            str: A representação em string do valor do nó.
        """
        return self.valor


class AVL:
    """
    Representa uma árvore AVL.

    Atributos:
        raiz (Node): Referência para o nó raiz da árvore.

    Métodos:
        __init__(): Inicializa um novo objeto AVL.
        __str__(): Retorna uma representação em string da árvore.
        __repr__(): Retorna uma representação em string da árvore.
        __len__(): Retorna o número de nós na árvore.
        __iter__(): Retorna um iterador para os nós da árvore.
        __contains__(valor: str): Verifica se um valor está na árvore.
        __getitem__(valor: str): Retorna um nó com o valor especificado.
        __setitem__(valor: str, quantidade: int): Insere um valor na árvore.
        __delitem__(valor: str): Remove um valor da árvore.
        _inserir(no: Node, valor: str): Insere um valor na árvore.
        _remover(no: Node, valor: str): Remove um valor da árvore.
        _buscar(no: Node, valor: str): Retorna um nó com o valor especificado.
        _atualizar_altura(no: Node): Atualiza a altura de um nó.
        _rotacao_esquerda(no: Node): Realiza uma rotação simples para a esquerda.
        _rotacao_direita(no: Node): Realiza uma rotação simples para a direita.
        _rotacao_dupla_esquerda(no: Node): Realiza uma rotação dupla para a esquerda.
        _rotacao_dupla_direita(no: Node): Realiza uma rotação dupla para a direita.
        _balancear(no: Node): Balanceia um nó.
        _pega_node_com_maior_quantidade(no: Node): Retorna o nó com a maior quantidade.
        _pega_node_com_menor_quantidade(no: Node): Retorna o nó com a menor quantidade.
        _pega_node_com_maior_valor(no: Node): Retorna o nó com o maior valor.
        _pega_node_com_menor_valor(no: Node): Retorna o nó com o menor valor.

    """
    raiz: Node = None

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

    def __repr__(self):
        return f"ArvoreAVL({self.raiz})"

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
            yield no
            yield from self._iter(no.direita)

    def __contains__(self, valor):
        return self.buscar(valor) is not None

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

    def first(self) -> Node | None:
        return self.raiz

    def fator_balanceamento(self, no: Node):
        return self._altura(no.direita) - self._altura(no.esquerda)

    def rotacao_esquerda(self, no: Node):
        nova_raiz = no.direita
        no.direita = nova_raiz.esquerda
        nova_raiz.esquerda = no
        no.altura = max(self._altura(no.esquerda), self._altura(no.direita)) + 1
        nova_raiz.altura = (
            max(self._altura(nova_raiz.esquerda), self._altura(nova_raiz.direita)) + 1
        )
        return nova_raiz

    def rotacao_direita(self, no: Node):
        nova_raiz = no.esquerda
        no.esquerda = nova_raiz.direita
        nova_raiz.direita = no
        no.altura = max(self._altura(no.esquerda), self._altura(no.direita)) + 1
        nova_raiz.altura = (
            max(self._altura(nova_raiz.esquerda), self._altura(nova_raiz.direita)) + 1
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

    def _inserir(self, valor: str, no: Node):
        if no is None:
            return Node(valor)

        valor_atual = self._tratar_str(no.valor)
        valor_novo = self._tratar_str(valor)

        if valor_novo < valor_atual:
            no.esquerda = self._inserir(valor, no.esquerda)
        elif valor_novo > valor_atual:
            no.direita = self._inserir(valor, no.direita)
        else:
            no.quantidade += 1
            return no

        no.altura = max(self._altura(no.esquerda), self._altura(no.direita)) + 1

        no = self._balancear(no, valor_novo, valor_atual)

        return no

    def _balancear(self, no: Node, valor_novo: str, valor_atual: str):
        fator_balanceamento = self.fator_balanceamento(no)

        if fator_balanceamento == -2:
            valor_filho_esquerda = self._tratar_str(no.esquerda.valor)
            if valor_novo < valor_filho_esquerda:
                no = self.rotacao_direita(no)
            else:
                no = self.rotacao_dupla_direita(no)
        elif fator_balanceamento == 2:
            valor_filho_direita = self._tratar_str(no.direita.valor)
            if valor_novo > valor_filho_direita:
                no = self.rotacao_esquerda(no)
            else:
                no = self.rotacao_dupla_esquerda(no)

        return no

    def remover(self, valor):
        (self.raiz, achou) = self._remover(valor, self.raiz)
        return achou

    def _remover(self, valor, no: Node) -> Tuple[Node | None, bool]:
        if no is None:
            return (None, False)

        if self._tratar_str(valor) < self._tratar_str(no.valor):
            (no.esquerda, achou) = self._remover(valor, no.esquerda)
        elif self._tratar_str(valor) > self._tratar_str(no.valor):
            (no.direita, achou) = self._remover(valor, no.direita)
        else:
            if no.esquerda is not None and no.direita is not None:
                no.valor = self._minimo(no.direita).valor
                (no.direita, achou) = self._remover(no.valor, no.direita)
            else:
                no = no.esquerda if no.esquerda is not None else no.direita
                achou = True

        if no is not None:
            no.altura = max(self._altura(no.esquerda), self._altura(no.direita)) + 1
            no = self._balancear(no, valor, no.valor)

        return (no, achou)

    def _minimo(self, no: Node) -> Node:
        """Retorna o nó com o menor valor da subárvore."""
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

        if self._tratar_str(valor) < self._tratar_str(no.valor):
            return self._buscar(valor, no.esquerda)
        if self._tratar_str(valor) > self._tratar_str(no.valor):
            return self._buscar(valor, no.direita)
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
            yield no
            yield from self._iter(no.direita)

    def __repr__(self):
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

    def pega_node_com_maior_quantidade(self):
        return self._pega_node_com_maior_quantidade(self.raiz)

    def _pega_node_com_maior_quantidade(self, no: Node):
        if no is None:
            return None
        no_original = no
        maior_quantidade = no
        while no is not None:
            if no.quantidade > maior_quantidade.quantidade:
                maior_quantidade = no
            no = no.direita
        no = no_original
        while no is not None:
            if no.quantidade > maior_quantidade.quantidade:
                maior_quantidade = no
            no = no.esquerda
        return maior_quantidade

    def pega_todos_com_uma_quantidade(self):
        return self._pega_todos_com_uma_quantidade(self.raiz)

    def _pega_todos_com_uma_quantidade(self, no: Node) -> Generator[str, None, None]:
        if no is not None:
            yield from self._pega_todos_com_uma_quantidade(no.esquerda)
            if no.quantidade == 1:
                yield no
            yield from self._pega_todos_com_uma_quantidade(no.direita)

    def pega_todos_entre_dois_valores(self, valor_minimo, valor_maximo):
        return self._pega_todos_entre_dois_valores(
            valor_minimo, valor_maximo, self.raiz
        )

    def _pega_todos_entre_dois_valores(
        self, valor_minimo, valor_maximo, no: Node
    ) -> Generator[str, None, None]:
        if no is not None:
            if (
                self._tratar_str(valor_minimo)
                <= self._tratar_str(no.valor)
                <= self._tratar_str(valor_maximo)
            ):
                yield from self._pega_todos_entre_dois_valores(
                    valor_minimo, valor_maximo, no.esquerda
                )
                yield no.valor
                yield from self._pega_todos_entre_dois_valores(
                    valor_minimo, valor_maximo, no.direita
                )
            elif self._tratar_str(valor_minimo) > self._tratar_str(no.valor):
                yield from self._pega_todos_entre_dois_valores(
                    valor_minimo, valor_maximo, no.direita
                )
            elif self._tratar_str(valor_maximo) < self._tratar_str(no.valor):
                yield from self._pega_todos_entre_dois_valores(
                    valor_minimo, valor_maximo, no.esquerda
                )

    def _altura(self, no: Node):
        if no is None:
            return -1
        return no.altura

    def _tratar_str(self, valor: str) -> str:
        valor_tratado = remove_acentuacao(valor.lower())
        valor_tratado = remove_pontuacao(valor_tratado)
        return valor_tratado
