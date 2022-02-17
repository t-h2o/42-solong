UNAME=`uname -s`

LINUX_PKG+="xorg "
LINUX_PKG+="libxext-dev "
LINUX_PKG+="zlib1g-dev "
LINUX_PKG+="gcc "
LINUX_PKG+="make "
LINUX_PKG+="xorg "
LINUX_PKG+="libxext-dev "
LINUX_PKG+="libbsd-dev"

if [ $UNAME == "Linux" ]
then
	echo this is a Linux os
	yes | sudo apt-get install $LINUX_PKG
	git clone https://github.com/42Paris/minilibx-linux mlx-linux
	sudo ./mlx-linux/configure
	make -C mlx-linux/
	make
	exit
fi

if [ $UNAME == "Darwin" ]
then
#	Download this minilibx in the intra 42
	echo this is a Mac os
	tar -xvzf minilibx_mms_20200219_beta.tgz
	mv minilibx_mms_20200219 mlx-apple
	make -C mlx-apple/
	cp mlx-apple/libmlx.dylib ./
	./so_long Map/map_1.ber
	exit
fi

