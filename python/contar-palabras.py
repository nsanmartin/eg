#!/usr/bin/python3

import sys
import getopt
import string

def main(argv):
    head = None
    width = None
    try:
        opts, args = getopt.getopt(argv, 'h:w:')
    except getopt.GetoptError:
        print('palabras <filename>')
        sys.exit(2)
    for o, a in opts:
        if o == "-h":
            head = int(a)
            continue
        if o == "-w":
            width = int(a)
            continue

    diccionario = {}

    # Esto es para sacar los signos de punctacion más abajo.
    translator = str.maketrans({key: None for key in string.punctuation})

    for archivo in args:
        with open(archivo, 'r') as f:
            text = f.read()
            #print(type(text))
            text = text.translate(translator)
        palabras = text.split()
        
        if width:
            palabras = [x for x in palabras if len(x) >= width]
        llenarTabla(diccionario, palabras)

    tabla =  sorted(diccionario.items(), key=lambda x:x[1], reverse=True)
    tabla = tabla[: 1  and head or len(tabla)]
    ancho = max([len(x[0]) for x in tabla]) + 2
    print("\n".join(["%s %s" %
                     (x[0].ljust(ancho), x[1])
                     for x in tabla]))
        
def llenarTabla(tabla, pals):
    for p in pals:
        if p in tabla: tabla[p] += 1
        else: tabla[p] = 1


def enTuplas(tabla):
    sorted(tabla.items(), key=lambda x:x[1], reverse=False)

def enOrden(dicc):
    sorted(dicc, key=dicc.get)


if __name__ == "__main__":
    print(":::")
    main(sys.argv[1:])
    
