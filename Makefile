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

CC := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic
LIBS := -lm 
DEBUG_CFLAGS := -g
RELEASE_CFLAGS := -O2

OBJDIR := obj
BUILDDIR := .
EXE_NAME := programa-principal
DOCSDIR := docs

define Doxyfile 

	INPUT = include src README.md
	RECURSIVE = YES
	EXTRACT_ALL = YES
	FILE_PATTERNS = *.h *.c

	PROJECT_NAME = SciLabProject
	USE_MDFILE_AS_MAINPAGE = README.md

	OUTPUT_DIRECTORY = $(DOCSDIR)
	GENERATE_HTML = YES
	GENERATE_LATEX = YES

endef

# END CONFIGURATION























