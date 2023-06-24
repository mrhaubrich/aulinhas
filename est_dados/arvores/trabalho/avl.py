from typing import Generator, Tuple

from utils import remove_acentuacao, remove_pontuacao


class Node:
    valor: str = None
    quantidade: int = 1
    esquerda: "Node" = None
    direita: "Node" = None
    altura = 0

    def __init__(self, valor):
        self.valor = valor

    def __str__(self):
        return self.valor


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

    def _inserir(self, valor: str, no: Node):
        if no is None:
            return Node(valor)
        if remove_acentuacao(remove_pontuacao(valor.lower())) < remove_acentuacao(
            remove_pontuacao(no.valor.lower())
        ):
            no.esquerda = self._inserir(valor, no.esquerda)
            if self.altura(no.esquerda) - self.altura(no.direita) == 2:
                if remove_acentuacao(
                    remove_pontuacao(valor.lower())
                ) < remove_acentuacao(remove_pontuacao(no.esquerda.valor.lower())):
                    no = self.rotacao_direita(no)
                else:
                    no = self.rotacao_dupla_direita(no)
        elif remove_acentuacao(remove_pontuacao(valor.lower())) > remove_acentuacao(
            remove_pontuacao(no.valor.lower())
        ):
            no.direita = self._inserir(valor, no.direita)
            if self.altura(no.direita) - self.altura(no.esquerda) == 2:
                if remove_acentuacao(
                    remove_pontuacao(valor.lower())
                ) > remove_acentuacao(remove_pontuacao(no.direita.valor.lower())):
                    no = self.rotacao_esquerda(no)
                else:
                    no = self.rotacao_dupla_esquerda(no)
        else:
            no.quantidade += 1
        no.altura = max(self.altura(no.esquerda), self.altura(no.direita)) + 1
        return no

    def remover(self, valor):
        (self.raiz, achou) = self._remover(valor, self.raiz)
        return achou

    def _remover(self, valor, no: Node) -> Tuple[Node | None, bool]:
        achou = False
        if no is None:
            return (None, achou)
        if valor < no.valor:
            (no.esquerda, achou) = self._remover(valor, no.esquerda)
            if self.altura(no.direita) - self.altura(no.esquerda) == 2:
                if self.altura(no.direita.direita) >= self.altura(no.direita.esquerda):
                    no = self.rotacao_esquerda(no)
                else:
                    no = self.rotacao_dupla_esquerda(no)
        elif valor > no.valor:
            (no.direita, achou) = self._remover(valor, no.direita)
            if self.altura(no.esquerda) - self.altura(no.direita) == 2:
                if self.altura(no.esquerda.esquerda) >= self.altura(
                    no.esquerda.direita
                ):
                    no = self.rotacao_direita(no)
                else:
                    no = self.rotacao_dupla_direita(no)
        elif no.esquerda is not None and no.direita is not None:
            no.valor = self._minimo(no.direita).valor
            (no.direita, achou) = self._remover(no.valor, no.direita)
        else:
            no = no.esquerda if no.esquerda is not None else no.direita
            achou = True
        if no is not None:
            no.altura = max(self.altura(no.esquerda), self.altura(no.direita)) + 1
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

        if valor < no.valor:
            return self._buscar(valor, no.esquerda)
        if valor > no.valor:
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
            yield no.valor
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

    def _pega_todos_com_uma_quantidade(self, no: Node) -> Generator[Node, None, None]:
        if no is None:
            return
        yield from self._pega_todos_com_uma_quantidade(no.esquerda)
        if no.quantidade == 1:
            yield no
        yield from self._pega_todos_com_uma_quantidade(no.direita)

    def to_str(self, reverse=False):
        return self._to_str(self.raiz, reverse)

    def _to_str(self, no: Node, reverse=False):
        if no is None:
            return ""
        if reverse:
            return (
                self._to_str(no.direita, reverse)
                + f" {str(no)} "
                + self._to_str(no.esquerda, reverse)
            )
        return (
            self._to_str(no.esquerda, reverse)
            + f" {str(no)} "
            + self._to_str(no.direita, reverse)
        )

    def to_list(self, reverse=False):
        return self._to_list(self.raiz, reverse)

    def _to_list(self, no: Node, reverse=False) -> Generator[Node, None, None]:
        if no is None:
            return
        if reverse:
            yield from self._to_list(no.direita, reverse)
            yield no
            yield from self._to_list(no.esquerda, reverse)
        else:
            yield from self._to_list(no.esquerda, reverse)
            yield no
            yield from self._to_list(no.direita, reverse)

    def first(self) -> Node | None:
        return self.raiz
