DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
CXX = g++
CXXFLAGS = -O3 -Wall $(DEPFLAGS)
OBJECTS = FuzzyLogicGenerator.o engine.o variable.o inputVariable.o outputVariable.o term.o triangleTerm.o evaluationRule.o strings.o
SRCS = FuzzyLogicGenerator.cpp engine.cpp variable.cpp inputVariable.cpp outputVariable.cpp term.cpp triangleTerm.cpp evaluationRule.cpp strings.cpp
NAME = FuzzyLogicGenerator

POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

all: $(OBJECTS)
	$(CXX) -o $(NAME) $(OBJECTS)

$(NAME): all

%.o: %.cpp $(DEPDIR)/%.d
	$(CXX) -c $(CXXFLAGS) $<
	$(POSTCOMPILE)

clean:
	rm *.o
	rm $(NAME)

remove:
	rm *.maxj
	rm *.fld
	rm *.c

$(DEPDIR)/%.d: ;

include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))
