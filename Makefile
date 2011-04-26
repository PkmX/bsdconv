PREFIX?=/usr/local
CFLAGS+=-Wall -DPREFIX='"${PREFIX}"'
SHLIBVER=4

TODO_CODECS_BASIC_TABLE=
TODO_CODECS_BASIC_TABLE+=from/3F
TODO_CODECS_BASIC_TABLE+=from/ANSI-CONTROL
TODO_CODECS_BASIC_TABLE+=from/ASCII-NAMED-HTML-ENTITY
TODO_CODECS_BASIC_TABLE+=from/ASCII-NUMERIC-HTML-ENTITY
TODO_CODECS_BASIC_TABLE+=from/ASCII
TODO_CODECS_BASIC_TABLE+=from/BIG5-5C
TODO_CODECS_BASIC_TABLE+=from/BSDCONV
TODO_CODECS_BASIC_TABLE+=from/BSDCONV_KEYWORD
TODO_CODECS_BASIC_TABLE+=from/BSDCONV_LOG
TODO_CODECS_BASIC_TABLE+=from/BYTE
TODO_CODECS_BASIC_TABLE+=from/CP1251
TODO_CODECS_BASIC_TABLE+=from/CP1252
TODO_CODECS_BASIC_TABLE+=from/CP949
TODO_CODECS_BASIC_TABLE+=from/ESCAPE
TODO_CODECS_BASIC_TABLE+=from/GBK
TODO_CODECS_BASIC_TABLE+=from/ISO-8859-1
TODO_CODECS_BASIC_TABLE+=from/NUL
TODO_CODECS_BASIC_TABLE+=from/PASS
TODO_CODECS_BASIC_TABLE+=from/SHIFT-JIS
TODO_CODECS_BASIC_TABLE+=from/SKIP
TODO_CODECS_BASIC_TABLE+=from/UAO250
TODO_CODECS_BASIC_TABLE+=from/UTF-16BE
TODO_CODECS_BASIC_TABLE+=from/UTF-16LE
TODO_CODECS_BASIC_TABLE+=from/UTF-32BE
TODO_CODECS_BASIC_TABLE+=from/UTF-32LE
TODO_CODECS_BASIC_TABLE+=from/UTF-8
TODO_CODECS_BASIC_TABLE+=inter/AMBIGUOUS-PAD
TODO_CODECS_BASIC_TABLE+=inter/AMBIGUOUS-UNPAD
TODO_CODECS_BASIC_TABLE+=inter/BIG5-DEFRAG
TODO_CODECS_BASIC_TABLE+=inter/FROM_ALIAS
TODO_CODECS_BASIC_TABLE+=inter/FULL
TODO_CODECS_BASIC_TABLE+=inter/HALF
TODO_CODECS_BASIC_TABLE+=inter/BSDCONV_INFO
TODO_CODECS_BASIC_TABLE+=inter/INTER_ALIAS
TODO_CODECS_BASIC_TABLE+=inter/JP_PINYIN
TODO_CODECS_BASIC_TABLE+=inter/LOWER
TODO_CODECS_BASIC_TABLE+=inter/MAC
TODO_CODECS_BASIC_TABLE+=inter/NL2BR
TODO_CODECS_BASIC_TABLE+=inter/TO_ALIAS
TODO_CODECS_BASIC_TABLE+=inter/UNIX
TODO_CODECS_BASIC_TABLE+=inter/UPPER
TODO_CODECS_BASIC_TABLE+=inter/UPSIDEDOWN
TODO_CODECS_BASIC_TABLE+=inter/WIN
TODO_CODECS_BASIC_TABLE+=inter/ZHCN
TODO_CODECS_BASIC_TABLE+=inter/ZHTW
TODO_CODECS_BASIC_TABLE+=inter/ZHTW_WORDS
TODO_CODECS_BASIC_TABLE+=to/3F
TODO_CODECS_BASIC_TABLE+=to/ANSI-CONTROL
TODO_CODECS_BASIC_TABLE+=to/ASCII-ESCAPED-UNICODE
TODO_CODECS_BASIC_TABLE+=to/ASCII-HEX-NUMERIC-HTML-ENTITY
TODO_CODECS_BASIC_TABLE+=to/ASCII-HTML-CNS11643-IMG
TODO_CODECS_BASIC_TABLE+=to/ASCII-HTML-INFO
TODO_CODECS_BASIC_TABLE+=to/ASCII-HTML-UNICODE-IMG
TODO_CODECS_BASIC_TABLE+=to/ASCII-NAMED-HTML-ENTITY
TODO_CODECS_BASIC_TABLE+=to/ASCII
TODO_CODECS_BASIC_TABLE+=to/BIG5-5C
TODO_CODECS_BASIC_TABLE+=to/BSDCONV
TODO_CODECS_BASIC_TABLE+=to/BSDCONV_KEYWORD
TODO_CODECS_BASIC_TABLE+=to/BSDCONV_LOG
TODO_CODECS_BASIC_TABLE+=to/BSDCONV_RAW
TODO_CODECS_BASIC_TABLE+=to/BSDCONV_STDOUT
TODO_CODECS_BASIC_TABLE+=to/BYTE
TODO_CODECS_BASIC_TABLE+=to/CP936
TODO_CODECS_BASIC_TABLE+=to/CP936_TRANS
TODO_CODECS_BASIC_TABLE+=to/CP950
TODO_CODECS_BASIC_TABLE+=to/CP950_TRANS
TODO_CODECS_BASIC_TABLE+=to/GBK
TODO_CODECS_BASIC_TABLE+=to/ISO-8859-1
TODO_CODECS_BASIC_TABLE+=to/NUL
TODO_CODECS_BASIC_TABLE+=to/PASS
TODO_CODECS_BASIC_TABLE+=to/RAW
TODO_CODECS_BASIC_TABLE+=to/UAO250
TODO_CODECS_BASIC_TABLE+=to/UCS-2BE
TODO_CODECS_BASIC_TABLE+=to/UCS-2LE
TODO_CODECS_BASIC_TABLE+=to/UNICODE
TODO_CODECS_BASIC_TABLE+=to/UTF-16BE
TODO_CODECS_BASIC_TABLE+=to/UTF-16LE
TODO_CODECS_BASIC_TABLE+=to/UTF-32BE
TODO_CODECS_BASIC_TABLE+=to/UTF-32LE
TODO_CODECS_BASIC_TABLE+=to/UTF-8

TODO_CODECS_EXTRA_TABLE=
TODO_CODECS_EXTRA_TABLE+=from/CNS11643
TODO_CODECS_EXTRA_TABLE+=from/CP936
TODO_CODECS_EXTRA_TABLE+=from/CP950
TODO_CODECS_EXTRA_TABLE+=from/GB2312
TODO_CODECS_EXTRA_TABLE+=from/UAO241
TODO_CODECS_EXTRA_TABLE+=inter/CHEWING
TODO_CODECS_EXTRA_TABLE+=inter/CNS11643
TODO_CODECS_EXTRA_TABLE+=inter/HAN_PINYIN
TODO_CODECS_EXTRA_TABLE+=inter/UNICODE
TODO_CODECS_EXTRA_TABLE+=inter/ZH_COMP
TODO_CODECS_EXTRA_TABLE+=inter/ZH_DECOMP
TODO_CODECS_EXTRA_TABLE+=to/CNS11643
TODO_CODECS_EXTRA_TABLE+=to/GB2312
TODO_CODECS_EXTRA_TABLE+=to/UAO241

TODO_CODECS_BASIC_CALLBACK=
TODO_CODECS_BASIC_CALLBACK+=from/ANSI-CONTROL
TODO_CODECS_BASIC_CALLBACK+=from/ASCII-NUMERIC-HTML-ENTITY
TODO_CODECS_BASIC_CALLBACK+=from/BSDCONV
TODO_CODECS_BASIC_CALLBACK+=from/BSDCONV_LOG
TODO_CODECS_BASIC_CALLBACK+=from/ESCAPE
TODO_CODECS_BASIC_CALLBACK+=from/PASS
TODO_CODECS_BASIC_CALLBACK+=from/SKIP
TODO_CODECS_BASIC_CALLBACK+=from/UTF-16BE
TODO_CODECS_BASIC_CALLBACK+=from/UTF-16LE
TODO_CODECS_BASIC_CALLBACK+=from/UTF-32BE
TODO_CODECS_BASIC_CALLBACK+=from/UTF-32LE
TODO_CODECS_BASIC_CALLBACK+=from/UTF-8
TODO_CODECS_BASIC_CALLBACK+=inter/AMBIGUOUS-PAD
TODO_CODECS_BASIC_CALLBACK+=inter/AMBIGUOUS-UNPAD
TODO_CODECS_BASIC_CALLBACK+=inter/BIG5-DEFRAG
TODO_CODECS_BASIC_CALLBACK+=inter/BSDCONV_INFO
TODO_CODECS_BASIC_CALLBACK+=to/3F
TODO_CODECS_BASIC_CALLBACK+=to/ANSI-CONTROL
TODO_CODECS_BASIC_CALLBACK+=to/ASCII-ESCAPED-UNICODE
TODO_CODECS_BASIC_CALLBACK+=to/ASCII-HEX-NUMERIC-HTML-ENTITY
TODO_CODECS_BASIC_CALLBACK+=to/ASCII-HTML-CNS11643-IMG
TODO_CODECS_BASIC_CALLBACK+=to/ASCII-HTML-INFO
TODO_CODECS_BASIC_CALLBACK+=to/ASCII-HTML-UNICODE-IMG
TODO_CODECS_BASIC_CALLBACK+=to/BSDCONV
TODO_CODECS_BASIC_CALLBACK+=to/BSDCONV_LOG
TODO_CODECS_BASIC_CALLBACK+=to/BSDCONV_RAW
TODO_CODECS_BASIC_CALLBACK+=to/BSDCONV_STDOUT
TODO_CODECS_BASIC_CALLBACK+=to/PASS
TODO_CODECS_BASIC_CALLBACK+=to/RAW
TODO_CODECS_BASIC_CALLBACK+=to/UCS-2BE
TODO_CODECS_BASIC_CALLBACK+=to/UCS-2LE
TODO_CODECS_BASIC_CALLBACK+=to/UNICODE
TODO_CODECS_BASIC_CALLBACK+=to/UTF-16BE
TODO_CODECS_BASIC_CALLBACK+=to/UTF-16LE
TODO_CODECS_BASIC_CALLBACK+=to/UTF-32BE
TODO_CODECS_BASIC_CALLBACK+=to/UTF-32LE
TODO_CODECS_BASIC_CALLBACK+=to/UTF-8

TODO_CODECS_EXTRA_CALLBACK=
TODO_CODECS_EXTRA_CALLBACK+=from/CNS11643
TODO_CODECS_EXTRA_CALLBACK+=to/CNS11643

all: libbsdconv bsdconv_mktable meta bsdconv codecs

alias:
.for t in from inter to
	python tools/mkalias.py codecs/$t/alias codecs/inter/${t:U}_ALIAS.txt
.endfor

builddir:
	mkdir -p build/bin
	mkdir -p build/lib
	mkdir -p build/include
	mkdir -p build/share/bsdconv/from
	mkdir -p build/share/bsdconv/inter
	mkdir -p build/share/bsdconv/to

libbsdconv: builddir src/libbsdconv.c src/bsdconv.h
	$(CC) ${CFLAGS} src/libbsdconv.c -fPIC -shared -o build/lib/libbsdconv.so.${SHLIBVER}

bsdconv: builddir libbsdconv meta src/bsdconv.h src/bsdconv.c
	$(CC) ${CFLAGS} src/bsdconv.c -L./build/lib/ -lbsdconv -o build/bin/bsdconv

bsdconv_mktable: builddir src/bsdconv.h
	$(CC) ${CFLAGS} src/bsdconv_mktable.c -o build/bin/bsdconv_mktable

codecs_basic_table: builddir bsdconv_mktable
.	for item in ${TODO_CODECS_BASIC_TABLE}
	./build/bin/bsdconv_mktable codecs/${item}.txt ./build/share/bsdconv/${item}
.	endfor

codecs_basic_callback: builddir libbsdconv
.	for item in ${TODO_CODECS_BASIC_CALLBACK}
	$(CC) ${CFLAGS} -fPIC -shared -o ./build/share/bsdconv/${item}.so codecs/${item}.c
.	endfor

codecs_extra_table: builddir bsdconv_mktable
.	for item in ${TODO_CODECS_EXTRA_TABLE}
	./build/bin/bsdconv_mktable codecs/${item}.txt ./build/share/bsdconv/${item}
.	endfor

codecs_extra_callback: builddir libbsdconv
.	for item in ${TODO_CODECS_EXTRA_CALLBACK}
	$(CC) ${CFLAGS} -fPIC -shared -o ./build/share/bsdconv/${item}.so codecs/${item}.c
.	endfor

codecs: codecs_basic codecs_extra
codecs_basic: codecs_basic_table codecs_basic_callback
codecs_extra: codecs_extra_table codecs_extra_callback

meta:
	ln -sf libbsdconv.so.${SHLIBVER} build/lib/libbsdconv.so
	cp src/bsdconv.h build/include

clean:
	rm -rf build

install: install_main install_basic install_extra

install_main:
	install -s -m 555 build/bin/bsdconv ${PREFIX}/bin
	install -s -m 555 build/bin/bsdconv_mktable ${PREFIX}/bin
	install -m 444 build/include/bsdconv.h ${PREFIX}/include
	install -s -m 444 build/lib/libbsdconv.so.${SHLIBVER} ${PREFIX}/lib
	ln -sf libbsdconv.so.${SHLIBVER} ${PREFIX}/lib/libbsdconv.so
	mkdir -p ${PREFIX}/share/bsdconv/from
	mkdir -p ${PREFIX}/share/bsdconv/inter
	mkdir -p ${PREFIX}/share/bsdconv/to

install_basic:
.	for item in ${TODO_CODECS_BASIC_TABLE}
	install -m 444 build/share/bsdconv/${item} ${PREFIX}/share/bsdconv/${item}
.	endfor
.	for item in ${TODO_CODECS_BASIC_CALLBACK}
	install -s -m 444 build/share/bsdconv/${item}.so ${PREFIX}/share/bsdconv/${item}.so
.	endfor

install_extra:
.	for item in ${TODO_CODECS_EXTRA_TABLE}
	install -m 444 build/share/bsdconv/${item} ${PREFIX}/share/bsdconv/${item}
.	endfor
.	for item in ${TODO_CODECS_EXTRA_CALLBACK}
	install -s -m 444 build/share/bsdconv/${item}.so ${PREFIX}/share/bsdconv/${item}.so
.	endfor


