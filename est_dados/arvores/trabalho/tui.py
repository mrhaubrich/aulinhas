#!/usr/bin/env python3
from rich.console import Console
from rich.pretty import install
from rich.table import Table

from hash_list import HashList

install()

console = Console()


class Tui:
    main_menu = [
        "1. Inserir palavra",
        "2. Consultar palavra",
        "3. Remover palavra",
        "4. Contar quantidade de palavras",
        "5. Contar ocorrências de uma palavra",
        "6. Exibe palavras por letra",
        "7. Exibe palavra com maior número de ocorrências",
        "8. Exibir palavras com uma única ocorrencia",
        # TODO: Adicionar outras
        "9. Ler arquivo",
    ]

    def __init__(self):
        self.hash_list = HashList()

    def main(self):
        while True:
            self.print_main_menu()
            option = input("Digite a opção: ")
            if option == "1":
                self.inserir()
            elif option == "2":
                self.buscar()
            elif option == "3":
                self.remove()
            elif option == "4":
                self.count()
            elif option == "5":
                self.count_word()
            elif option == "6":
                self.print_by_letter()
            elif option == "7":
                self.print_most_occur()
            elif option == "8":
                self.print_one_occur()
            elif option == "9":
                self.read_file()
            else:
                print("Opção inválida")

    def print_main_menu(self):
        console.clear()
        console.print("Menu principal", style="bold underline")
        for option in self.main_menu:
            console.print(option)

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

    def remove(self):
        word = input("Digite a palavra: ")
        if self.hash_list.remove(word):
            print("Palavra removida com sucesso")
        else:
            print("Palavra não encontrada")

    def count(self):
        print(f"Quantidade de palavras: {self.hash_list.count()}")
            
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