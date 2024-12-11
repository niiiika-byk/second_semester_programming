docker build -t myimage:latest .
docker run -d --rm --name mycontainer1 --network host myimage:latest
docker run -ti --rm --name mycontainer2 --network host myimage:latest /bin/bash
# ip addr show
# exit