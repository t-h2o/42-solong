PNG		=	empty.png	\
			wall.png	\
			exit.png	\
			player.png	\
			collectible.png

ASS		=	assets_1.png	\
			assets_2.png	\
			assets_3.png	\
			assets_4.png	\
			assets_5.png	\
			assets_6.png	\
			assets_7.png	\

XPM		=	${ASS:.png=.xpm}
#XPM		=	${PNG:.png=.xpm}

%.xpm : %.png
	convert $< $@

all:	${XPM}

clean:
	rm -f *xpm
