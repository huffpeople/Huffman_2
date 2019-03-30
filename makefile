COMPACT = compact.h compact.c
DESCOMPACT = descompact.h descompact.c
TREE = tree.h tree.c
HEAP = heap.h heap.c 
HEADER = header.h
HASH = hash.h hash.c
MAIN = huff.c

compile_huff:
	gcc $(HEADER) $(HEAP) $(TREE) $(HASH) $(COMPACT) $(DESCOMPACT) $(MAIN) -o huffman -w