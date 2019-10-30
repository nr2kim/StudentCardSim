SENTINEL:=-1
KIND:=NOBUSY
OPT:= # -multi -O2

CXX = u++					# compiler
CXXFLAGS = -g -Wall -Wextra ${OPT} -MMD -std=c++11 -DTYPE="${TYPE}" \
	   -DSENTINEL=${SENTINEL} -D${KIND}	# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = main.o Bank.o BottlingPlant.o Courier.o Groupoff.o NameServer.o Truck.o VendingMachine.o WATCardOffice.o config.o # object files forming 1st executable with prefix "q2"
EXEC1 = soda				# 1st executable name

OBJECTS = ${OBJECTS1}		# all object files
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC1}			# all executables

#############################################################

.PHONY : all clean

all : ${EXECS}					# build all executables

${EXEC1} : ${OBJECTS1}
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXECS} ImplType ImplKind
