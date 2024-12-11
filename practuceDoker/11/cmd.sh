docker build -t myimage:latest .
docker run -d --rm --name mycontainer1 myimage:latest
docker run -ti --rm --name mycontainer2 myimage:latest /bin/bash
# ip addr show
# docker network inspect bridge
# exit
docker run -d --rm --name mycontainer2 myimage:latest
docker network create my-net
docker run -ti --rm --name mycontainer3 --network my-net myimage:latest /bin/bash
docker run -ti --rm --name mycontainer4 --network my-net myimage:latest /bin/bash