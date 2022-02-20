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
	echo this is a Mac os
	
	# Download this minilibx in the intra 42
	# this one ...
	# minilibx_opengl.tgz
	# ... not this one !
	# minilibx_mms_20200219_beta.tgz
	
	curl -O https://projects.intra.42.fr/uploads/document/document/7125/minilibx_opengl.tgz
	tar -xvzf minilibx_opengl.tgz
	mv minilibx_opengl_20191021 mlx-apple
	make -C mlx-apple/
	make
	./so_long Map/map_1.ber
	exit
fi

