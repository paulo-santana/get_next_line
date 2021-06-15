NAME = test

SRC_DIR = ../
BONUS_DIR = ../

MAIN_FILES = main.c \
			 utils/string.c \
			 utils/print_errors.c

SRCS_FILES = get_next_line.c \
			 get_next_line_utils.c

BONUS_SRCS_FILES = get_next_line_bonus.c \
				   get_next_line_utils_bonus.c

SRCS = ${MAIN_FILES} ${addprefix ${SRC_DIR}, ${SRCS_FILES}}
BONUS_SRCS = ${MAIN_FILES} ${addprefix ${BONUS_SRCS_DIR}, ${BONUS_SRCS_FILES}}

OBJS = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS_SRCS:.c=.o}

BUFFER_SIZES = 32 9999 1 10000000

CFLAGS = -Wall -Werror -Wextra -g

CC = clang ${CFLAGS}

run: ${BUFFER_SIZES}

%.o: %.c
	${CC} -I${SRC_DIR} -DBUFFER_SIZE=${BUFFER_SIZE} -c $< -o $@

${BUFFER_SIZES}: BUFFER_SIZE :=$@
${BUFFER_SIZES}: ${OBJS}
	${CC} -I${SRC_DIR} ${OBJS} -o ${NAME}
