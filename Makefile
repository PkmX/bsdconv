PREFIX?=/usr/local
CFLAGS+=-Wall -DPREFIX='"${PREFIX}"'
SHLIBVER=4

TODO_CODECS_TABLE=
TODO_CODECS_TABLE+=from/3F
TODO_CODECS_TABLE+=from/ASCII-NAMED-HTML-ENTITY
TODO_CODECS_TABLE+=from/ASCII-NUMERIC-HTML-ENTITY
TODO_CODECS_TABLE+=from/ASCII
TODO_CODECS_TABLE+=from/BIG5-5C
TODO_CODECS_TABLE+=from/BSDCONV
TODO_CODECS_TABLE+=from/BSDCONV_KEYWORD
TODO_CODECS_TABLE+=from/BYTE
TODO_CODECS_TABLE+=from/CNS11643
TODO_CODECS_TABLE+=from/CP936
TODO_CODECS_TABLE+=from/CP950
TODO_CODECS_TABLE+=from/GB2312
TODO_CODECS_TABLE+=from/GBK
TODO_CODECS_TABLE+=from/ISO-8859-1
TODO_CODECS_TABLE+=from/MOZ18
TODO_CODECS_TABLE+=from/UTF-16BE
TODO_CODECS_TABLE+=from/UTF-16LE
TODO_CODECS_TABLE+=from/UTF-32BE
TODO_CODECS_TABLE+=from/UTF-32LE
TODO_CODECS_TABLE+=from/UTF-8
TODO_CODECS_TABLE+=inter/CHEWING
TODO_CODECS_TABLE+=inter/CNS11643
TODO_CODECS_TABLE+=inter/FROM_ALIAS
TODO_CODECS_TABLE+=inter/FULL
TODO_CODECS_TABLE+=inter/HALF
TODO_CODECS_TABLE+=inter/HAN_PINYIN
TODO_CODECS_TABLE+=inter/INTER_ALIAS
TODO_CODECS_TABLE+=inter/JP_PINYIN
TODO_CODECS_TABLE+=inter/LOWER
TODO_CODECS_TABLE+=inter/MAC
TODO_CODECS_TABLE+=inter/NL2BR
TODO_CODECS_TABLE+=inter/TO_ALIAS
TODO_CODECS_TABLE+=inter/UNICODE
TODO_CODECS_TABLE+=inter/UNIX
TODO_CODECS_TABLE+=inter/UPPER
TODO_CODECS_TABLE+=inter/UPSIDEDOWN
TODO_CODECS_TABLE+=inter/WIN
TODO_CODECS_TABLE+=inter/ZHCN
TODO_CODECS_TABLE+=inter/ZHTW
TODO_CODECS_TABLE+=to/3F
TODO_CODECS_TABLE+=to/ASCII-ESCAPED-UNICODE
TODO_CODECS_TABLE+=to/ASCII-HEX-NUMERIC-HTML-ENTITY
TODO_CODECS_TABLE+=to/ASCII-HTML-CNS11643-IMG
TODO_CODECS_TABLE+=to/ASCII-HTML-UNICODE-IMG
TODO_CODECS_TABLE+=to/ASCII-NAMED-HTML-ENTITY
TODO_CODECS_TABLE+=to/ASCII
TODO_CODECS_TABLE+=to/BIG5-5C
TODO_CODECS_TABLE+=to/BSDCONV
TODO_CODECS_TABLE+=to/BSDCONV_KEYWORD
TODO_CODECS_TABLE+=to/BSDCONV_STDOUT
TODO_CODECS_TABLE+=to/BYTE
TODO_CODECS_TABLE+=to/CNS11643
TODO_CODECS_TABLE+=to/CP936
TODO_CODECS_TABLE+=to/CP936_TRANS
TODO_CODECS_TABLE+=to/CP950
TODO_CODECS_TABLE+=to/CP950_TRANS
TODO_CODECS_TABLE+=to/GB2312
TODO_CODECS_TABLE+=to/GBK
TODO_CODECS_TABLE+=to/ISO-8859-1
TODO_CODECS_TABLE+=to/UCS-2BE
TODO_CODECS_TABLE+=to/UCS-2LE
TODO_CODECS_TABLE+=to/UTF-16BE
TODO_CODECS_TABLE+=to/UTF-16LE
TODO_CODECS_TABLE+=to/UTF-32BE
TODO_CODECS_TABLE+=to/UTF-32LE
TODO_CODECS_TABLE+=to/UTF-8

TODO_CODECS_TABLE_EXTRA=
TODO_CODECS_TABLE_EXTRA+=inter/ZH_COMP
TODO_CODECS_TABLE_EXTRA+=inter/ZH_DECOMP

TODO_CODECS_CALLBACK=
TODO_CODECS_CALLBACK+=from/ASCII-NUMERIC-HTML-ENTITY
TODO_CODECS_CALLBACK+=from/BSDCONV
TODO_CODECS_CALLBACK+=from/CNS11643
TODO_CODECS_CALLBACK+=from/UTF-16BE
TODO_CODECS_CALLBACK+=from/UTF-16LE
TODO_CODECS_CALLBACK+=from/UTF-32BE
TODO_CODECS_CALLBACK+=from/UTF-32LE
TODO_CODECS_CALLBACK+=from/UTF-8
TODO_CODECS_CALLBACK+=to/3F
TODO_CODECS_CALLBACK+=to/ASCII-ESCAPED-UNICODE
TODO_CODECS_CALLBACK+=to/ASCII-HEX-NUMERIC-HTML-ENTITY
TODO_CODECS_CALLBACK+=to/ASCII-HTML-CNS11643-IMG
TODO_CODECS_CALLBACK+=to/ASCII-HTML-UNICODE-IMG
TODO_CODECS_CALLBACK+=to/BSDCONV
TODO_CODECS_CALLBACK+=to/BSDCONV_STDOUT
TODO_CODECS_CALLBACK+=to/CNS11643
TODO_CODECS_CALLBACK+=to/UCS-2BE
TODO_CODECS_CALLBACK+=to/UCS-2LE
TODO_CODECS_CALLBACK+=to/UTF-16BE
TODO_CODECS_CALLBACK+=to/UTF-16LE
TODO_CODECS_CALLBACK+=to/UTF-32BE
TODO_CODECS_CALLBACK+=to/UTF-32LE
TODO_CODECS_CALLBACK+=to/UTF-8

all: libbsdconv bsdconv_mktable bsdconv codecs meta

alias:
.for t in from inter to
	cd codecs/$t/ && \
	cp alias alias.tmp && \
	find *.txt |awk 'BEGIN{FS=".txt"}; {print $$1"\t"$$1}' >> alias.tmp
	python tools/mkalias.py codecs/$t/alias.tmp codecs/inter/${t:U}_ALIAS.txt
	rm codecs/$t/alias.tmp
.endfor

builddir:
	mkdir -p build/bin
	mkdir -p build/lib
	mkdir -p build/include
	mkdir -p build/share/bsdconv/from
	mkdir -p build/share/bsdconv/inter
	mkdir -p build/share/bsdconv/to

libbsdconv: builddir src/bsdconv_func.c src/libbsdconv.c src/bsdconv.h
	$(CC) ${CFLAGS} src/bsdconv_func.c src/libbsdconv.c -fPIC -shared -o build/lib/libbsdconv.so.${SHLIBVER}

bsdconv: builddir src/bsdconv_func.c src/libbsdconv.c src/bsdconv.h src/bsdconv.c
	$(CC) ${CFLAGS} src/bsdconv_func.c src/libbsdconv.c src/bsdconv.c -o build/bin/bsdconv

bsdconv_mktable: builddir src/bsdconv.h
	$(CC) ${CFLAGS} src/bsdconv_func.c src/bsdconv_mktable.c -o build/bin/bsdconv_mktable

codecs_table: builddir bsdconv_mktable
.	for item in ${TODO_CODECS_TABLE}
	./build/bin/bsdconv_mktable codecs/${item}.txt ./build/share/bsdconv/${item}
.	endfor

codecs_table_extra: builddir bsdconv_mktable
.	for item in ${TODO_CODECS_TABLE_EXTRA}
	./build/bin/bsdconv_mktable codecs/${item}.txt ./build/share/bsdconv/${item}
.	endfor

codecs_callback: builddir
.	for item in ${TODO_CODECS_CALLBACK}
	$(CC) ${CFLAGS} -fPIC -shared -o ./build/share/bsdconv/${item}.so ./src/bsdconv_func.c codecs/${item}.c
.	endfor

codecs: codecs_table codecs_callback

meta:
	ln -sf libbsdconv.so.${SHLIBVER} build/lib/libbsdconv.so
	cp src/bsdconv.h build/include

clean:
	rm -rf build

install:
	cp -R build/ ${PREFIX}


