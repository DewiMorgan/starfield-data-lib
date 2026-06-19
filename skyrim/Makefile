CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O3
TARGET = parser
SRC = parser.cpp core.cpp ASTP.cpp ASPC.cpp AVIF.cpp CAMS.cpp CELL.cpp CLAS.cpp CLFM.cpp COLL.cpp CSTY.cpp DIAL.cpp DLBR.cpp DOBJ.cpp ECZN.cpp EFSH.cpp EQUP.cpp EYES.cpp FACT.cpp FLST.cpp FSTP.cpp FSTS.cpp GMST.cpp GRUP.cpp IMAD.cpp IMGS.cpp IPDS.cpp IPCT.cpp KYWD.cpp LAND.cpp LCRT.cpp LGTM.cpp LTEX.cpp MATO.cpp MATT.cpp MODT.cpp MOVT.cpp MUSC.cpp OBND.cpp OTFT.cpp WOOP.cpp REVB.cpp SNCT.cpp VTYP.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
