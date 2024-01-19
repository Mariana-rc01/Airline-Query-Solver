# START COPYRIGHT NOTICE

# 	Copyright 2023 Hugo Abelheira, Mariana Rocha, Luís França
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.

# END COPYRIGHT NOTICE

# START CONFIGURATION

CC             := gcc
CFLAGS         := -Wall -Wextra -Werror -pedantic $(shell pkg-config --cflags glib-2.0) -fexec-charset=UTF-8
LIBS           := -lm $(shell pkg-config --libs glib-2.0) -lncurses
DEBUG_CFLAGS   := -g
RELEASE_CFLAGS := -O2

OBJDIR         := obj
EXE_NAME       := programa-principal
TEST_EXE_NAME  := programa-testes
DOCSDIR        := docs

define Doxyfile

	INPUT                  = include src README.md
	RECURSIVE              = YES
	EXTRACT_ALL            = YES
	FILE_PATTERNS 		   = *.h *.c

	PROJECT_NAME 		   = SciLabProject
	USE_MDFILE_AS_MAINPAGE = README.md

	OUTPUT_DIRECTORY	   = $(DOCSDIR)
	GENERATE_HTML          = YES
	GENERATE_LATEX         = YES

endef

# END CONFIGURATION

# START MAKEFILE RULES

export Doxyfile

SHELL := bash -O globstar # Dependency on bash for recursive wildcards

SOURCES = $(shell ls src/**/*.c)
HEADERS = $(shell ls include/**/*.h)
OBJECTS = $(patsubst src/%.c, $(OBJDIR)/%.o, $(SOURCES))

ifeq ($(DEBUG), 1)
	CFLAGS += ${DEBUG_CFLAGS}
else
	CFLAGS += ${RELEASE_CFLAGS}
endif

default: $(EXE_NAME) $(TEST_EXE_NAME)

$(OBJDIR)/%.o: src/%.c $(HEADERS) $(OBJDIRS)
	@mkdir -p $(shell dirname $@)
	${CC} -c -o $@ $< ${CFLAGS} -Iinclude

$(OBJDIR)/%.o: src/%.c $(HEADERS) $(OBJDIRS)
	@mkdir -p $(shell dirname $@)
	${CC} -c -o $@ $< ${CFLAGS} -Iinclude

$(EXE_NAME): $(OBJECTS)
	$(CC) -o $@ $^ ${LIBS}

$(TEST_EXE_NAME): $(OBJECTS)
	$(CC) -o $@ $^ ${LIBS}

$(DOCSDIR): $(SOURCES) $(HEADERS) README.md
	echo "$$Doxyfile" | doxygen -

clean:
	@rm -r $(OBJDIR)     > /dev/null 2>&1 ||:
	@rm $(EXE_NAME)      > /dev/null 2>&1 ||:
	@rm $(TEST_EXE_NAME) > /dev/null 2>&1 ||:
	@rm -r $(DOCSDIR)    > /dev/null 2>&1 ||:
	@rm Resultados/*.csv > /dev/null 2>&1 ||:
	@rm Resultados/*.txt > /dev/null 2>&1 ||:

# END MAKEFILE RULES

