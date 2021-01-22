#
#  Makefile für GNU C++
#
#  Anwendung:
#
#  make      - Erzeugung des ausfuehrbaren Programms
#

#************************************************************
#
# CC: Name des C++ Compilers:
#
CC = g++
#
#************************************************************
#
# Liste der C++ SourceFiles
#
CCFILES  = src/main.cpp \
           src/NNeural.cpp

#************************************************************
#
# Liste der Library Files
#

LNKCMD =
INCCMD = -I./inc        


#************************************************************
#
# C++ Flags:
#
# -c  = nur compilieren, nicht linken
# -O2 = Optimierung: schnellen Code erzeugen
#
# Assembler-Flags:
#
# -ml = Case-Sensitiv für alle Symbole
#
# CCFLAGS  = -O -static-libgcc -L. -I$(INCPATH) -I$(INCSTE)
#
CCFLAGS = -O2 $(INCCMD)


#************************************************************
#
# Regeln zur Erzeugung eines .obj-Files aus C++ Quelldateien
# und aus Assembler-Dateien:
#
# $@ = Dateiname des Ziels
# $< = Der Name der ersten Abhängigkeit.
#        
.cpp.o:
	$(CC) -c $(CCFLAGS) -o$@ $<  
    

#************************************************************
#
# Liste der Objekt-Dateien
# Die Liste der Objekt-Dateien entspricht der Liste der 
# Quellcode-Dateien, nur dass die Endung .cpp durch .obj
# ersetzt wird (Ersetzungregel)
#
CCOBJECTS  = $(CCFILES:.cpp=.o)


#************************************************************
#
# Name des Ziels
#
TARGET = neural_network                                                      

#************************************************************
#
# Wenn make ohne Parameter gestartet wird, wird "default"
# gemacht.
#
default: $(TARGET)
#
clean:
	rm -fv *.o
	rm -fv $(LIBPATH)/*.o


install:
	cp -v $(TARGET).exe /bin


#************************************************************
#
# Regel zur Erzeugung des Targets aus den Objekt-Dateien.
#
$(TARGET): $(CCOBJECTS)
	$(CC) -s -o $(TARGET) $(CCOBJECTS)	
