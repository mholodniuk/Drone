TASKNO=5
APP=sterowanie-dronem
TASKDIR=${HOME}/edu/po/zad/z${TASKNO}

__start__: obj dat ./${APP}
	rm -f core.* core; ./${APP}

# Tworzy katalog "obj" gdy go nie ma
# 
obj:
	mkdir obj

dat:
	mkdir dat


./${APP}: obj/main.o obj/lacze_do_gnuplota.o obj/Wektor3D.o obj/Macierz3x3.o \
			obj/Dron.o obj/Menu.o obj/Scena.o obj/Prostopadloscian.o obj/Graniastoslup.o obj/BrylaGeometryczna.o \
				obj/GoraZDlugaGrania.o obj/GoraZOstrymSzczytem.o obj/Plaskowyz.o obj/ObiektSceny.o
	g++ -g -Wall -pedantic -std=c++17 -o ./${APP} obj/main.o obj/lacze_do_gnuplota.o obj/Wektor3D.o obj/Macierz3x3.o \
				obj/Dron.o obj/Menu.o obj/Scena.o obj/Prostopadloscian.o obj/Graniastoslup.o obj/BrylaGeometryczna.o \
					obj/GoraZDlugaGrania.o obj/GoraZOstrymSzczytem.o obj/Plaskowyz.o obj/ObiektSceny.o

ext: ./${APP}_rozszerzony
	rm -f core.* core; echo "2i 1+3.1i 2 ? / + ?" | ./${APP}_rozszerzony


obj/main.o: src/main.cpp inc/lacze_do_gnuplota.hh inc/Dron.hh inc/Macierz3x3.hh inc/Wektor3D.hh inc/Nazwy.hh\
				 inc/Menu.hh inc/Dron.hh inc/Wektor.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/main.o src/main.cpp

obj/Wektor3D.o: src/Wektor3D.cpp inc/Wektor3D.hh inc/Wektor.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Wektor3D.o src/Wektor3D.cpp

obj/Macierz3x3.o: src/Macierz3x3.cpp inc/Macierz3x3.hh inc/Wektor.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Macierz3x3.o src/Macierz3x3.cpp

obj/Menu.o: src/Menu.cpp inc/Menu.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Menu.o src/Menu.cpp

obj/Dron.o: src/Dron.cpp inc/Dron.hh inc/Macierz3x3.hh inc/Wektor3D.hh inc/Nazwy.hh inc/lacze_do_gnuplota.hh\
							inc/Prostopadloscian.hh inc/Graniastoslup.hh inc/Wektor.hh inc/ObiektSceny.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Dron.o src/Dron.cpp

obj/lacze_do_gnuplota.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/BrylaGeometryczna.o: src/BrylaGeometryczna.cpp inc/BrylaGeometryczna.hh inc/Wektor.hh inc/ObiektSceny.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/BrylaGeometryczna.o src/BrylaGeometryczna.cpp

obj/Prostopadloscian.o: src/Prostopadloscian.cpp inc/Prostopadloscian.hh inc/BrylaGeometryczna.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Prostopadloscian.o src/Prostopadloscian.cpp

obj/Graniastoslup.o: src/Graniastoslup.cpp inc/Graniastoslup.hh inc/BrylaGeometryczna.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Graniastoslup.o src/Graniastoslup.cpp

obj/Scena.o: src/Scena.cpp inc/Scena.hh inc/Dron.hh inc/Wektor.hh inc/Menu.hh inc/GoraZOstrymSzczytem.hh inc/GoraZDlugaGrania.hh inc/ObiektSceny.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Scena.o src/Scena.cpp

obj/GoraZDlugaGrania.o: src/GoraZDlugaGrania.cpp inc/GoraZDlugaGrania.hh inc/BrylaGeometryczna.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/GoraZDlugaGrania.o src/GoraZDlugaGrania.cpp

obj/GoraZOstrymSzczytem.o: src/GoraZOstrymSzczytem.cpp inc/GoraZOstrymSzczytem.hh inc/BrylaGeometryczna.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/GoraZOstrymSzczytem.o src/GoraZOstrymSzczytem.cpp

obj/Plaskowyz.o: src/Plaskowyz.cpp inc/Plaskowyz.hh inc/BrylaGeometryczna.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/Plaskowyz.o src/Plaskowyz.cpp

obj/ObiektSceny.o: src/ObiektSceny.cpp inc/ObiektSceny.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/ObiektSceny.o src/ObiektSceny.cpp

clean:
	rm -f obj/* ./${APP} core.* core
	rm -f dat/przeszkody/*

${TASKDIR}:
	mkdir -p ${TASKDIR}/bin.diablo ${TASKDIR}/bin.panamint

__TARGET__:
	if [ ! "${HOST}" = "diablo" ] && [ ! "${HOST}" = "panamint" ]; then exit 1; fi

export: __TARGET__ ./${APP}  ./${APP}_rozszerzony ${TASKDIR}
	mv ${APP} ${APP}_rozszerzony ${HOME}/edu/po/zad/z${TASKNO}/bin.${HOST}/

help:
	@echo
	@echo " make        - tworzenie i uruchomienie aplikacji"
	@echo " make ext    - tworzenie i uruchomienie aplikacji w wersji rozszerzonej"
	@echo " make clean  - usuniecie produktow kompilacji i konsolidacji"
	@echo " make help   - wyswietla niniejsza informacje"
	@echo
