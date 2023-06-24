import re


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
