#DBG?=	 -O2 -g
DBG?=	 -O2
CFLAGS+= -std=gnu99 ${DBG}
CFLAGS+= -fno-stack-protector -ffreestanding
CXXFLAGS+= -fno-stack-protector -ffreestanding

CFLAGS+= -Wall -Wimplicit -Wmissing-prototypes -Wstrict-prototypes
ifndef NOGCCERROR
CFLAGS+= -Werror
endif
