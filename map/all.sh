make re -C ./..
clear 

for file in map_error*
do
	echo $file
	./../so_long $file | grep Error
done
