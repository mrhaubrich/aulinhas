#!/usr/bin/env python3
from rich.console import Console
from rich.pretty import install
from rich.table import Table

from hash_list import HashList

install()

console = Console()


class Tui:
    def get_main_menu(self):
        return {
            "1": {
                "text": "Inserir palavra",
                "function": self.inserir,
            },
            "2": {
                "text": "Consultar palavra",
                "function": self.buscar,
            },
            "3": {
                "text": "Remover palavra",
                "function": self.remover,
            },
            "4": {
                "text": "Contar quantidade de palavras",
                "function": self.count,
            },
            "5": {
                "text": "Contar ocorrências de uma palavra",
                "function": self.count_word,
            },
            "6": {
                "text": "Exibe palavras por letra",
                "function": self.print_by_letter,
            },
            "7": {
                "text": "Exibe palavra com maior número de ocorrências",
                "function": self.print_most_occur,
            },
            "8": {
                "text": "Exibir palavras com uma única ocorrencia",
                "function": self.print_one_occur,
            },
            "9": {
                "text": "Ler arquivo",
                "function": self.read_file,
            },
        }

    def __init__(self):
        self.hash_list = HashList()

    def main(self):
        while True:
            self.print_main_menu()
            option = console.input("Digite a opção: ")
            if option == "0":
                break
            try:
                self.get_main_menu()[option]["function"]()
            except KeyError:
                console.print("Opção inválida", style="bold red")
                self.press_any_key()

    def print_main_menu(self):
        console.clear()
        console.print("Menu principal", style="bold")
        for key, value in self.get_main_menu().items():
            console.print(f"{key}. {value['text']}")

    def inserir(self):
        word = console.input("Digite a palavra: ")
        self.hash_list.inserir(word)
        print("Palavra inserida com sucesso")

    def buscar(self):
        word = input("Digite a palavra: ")
        palavra = self.hash_list.buscar(word)
        table = None
        console.clear()
        if palavra is not None:
            table = Table(title="Palavra encontrada")
            table.add_column("Palavra")
            table.add_column("Ocorrências")
            table.add_row(palavra.valor, str(palavra.quantidade))
        else:
            console.print("Palavra não encontrada", style="bold red")
        if table:
            console.print(table)
        self.press_any_key()

    def remover(self):
        palavra = console.input("Digite a palavra: ")
        console.clear()
        if self.hash_list.remover(palavra):
            console.print("Palavra removida com sucesso", style="bold green")
        else:
            console.print("Palavra não encontrada", style="bold red")
        self.press_any_key()

    def count(self):
        console.clear()
        console.print(f"Quantidade de palavras: {len(self.hash_list)}")
        self.press_any_key()

    def count_word(self):
        word = input("Digite a palavra: ")
        print(f"Quantidade de ocorrências: {self.hash_list.count_word(word)}")

    def print_by_letter(self):
        letter = input("Digite a letra: ")
        self.hash_list.print_by_letter(letter)

    def print_most_occur(self):
        most_occur = self.hash_list.get_most_occur()
        table = Table(title="Palavra com mais ocorrências")
        table.add_column("Palavra")
        table.add_column("Ocorrências")
        table.add_row(most_occur.valor, str(most_occur.quantidade))
        console.clear()
        console.print(table)
        self.press_any_key()

    def print_by_occur(self):
        occur = int(input("Digite a quantidade de ocorrências: "))
        self.hash_list.print_by_occur(occur)

    def print_one_occur(self):
        words = self.hash_list.get_one_occur()
        table = Table(title="Palavras com uma única ocorrência")
        table.add_column("Palavra")
        table.add_column("Ocorrências")
        for word in words:
            table.add_row(word.valor, str(word.quantidade))
        console.clear(False)
        console.print(table)
        self.press_any_key()

    def read_file(self):
        file_name = console.input("Digite o nome do arquivo (padrão: texto.txt): ")
        if file_name == "":
            file_name = "texto.txt"
        self.hash_list.read_file(file_name)

    def press_any_key(self):
        console.input("Pressione qualquer tecla para continuar...")


if __name__ == "__main__":
    tui = Tui()
    tui.main()
