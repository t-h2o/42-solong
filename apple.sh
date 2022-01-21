#	Download this minilibx in the intra

tar -xvzf minilibx_mms_20200219_beta.tgz
mv minilibx_mms_20200219 mlx-apple
make -C mlx-apple/
cp mlx-apple/libmlx.dylib ./
