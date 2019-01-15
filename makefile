# @Author: Cody Craig <codycraig>
# @Date:   08-Jan-2019, 9:41:52 am
# @Email:  cody.craig500@gmail.com
# @Filename: makefile
# @Last modified by:   codycraig
# @Last modified time: 08-Jan-2019, 5:20:36 pm



# makefile for count.c

CC=gcc
CGLAGS = -g -Wall

all: count

count: count.c
	$(CC) $(CFLAGS) -o count count.c

clean:
	rm count
