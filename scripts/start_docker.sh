xhost +
sudo docker run -p 50003:22 \
                --net=host \
                -v "/home/lxy/MonoLaneMapping":"/home/MonoLaneMapping/" \
                -v "/home/lxy/OpenLane/lane3d_1000_training/training":"/home/data/" \
		            --privileged=true \
	              -itd lxy2019/mono_lane_mapping:v0.4 /bin/bash
#

Container_id=$(sudo docker ps | grep 'lxy2019/mono_lane_mapping:v0.4' | awk '{print $1}')

echo $Container_id

if [ -z "$Container_id" ]; then
    echo "Container not found"
else
    sudo docker exec -it $Container_id service ssh start
fi

sudo docker exec -it $Container_id /bin/bash



