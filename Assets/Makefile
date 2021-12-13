PNG		=	empty.png	\
			wall.png	\
			exit.png	\
			player.png	\
			collectible.png


XPM		=	${PNG:.png=.xpm}

%.xpm : %.png
	convert $< $@

all:	${XPM}

clean:
	rm -f *xpm
