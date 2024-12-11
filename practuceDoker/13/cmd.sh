docker build -t myimage:latest .
docker network create -d macvlan --subnet=172.20.5.0/24 --gateway=172.20.5.1 --aux-address="my-router=172.20.5.44" -o parent=ens3 pub_net
docker run -ti --rm --name mycontainer1 --network pub_net myimage:latest
docker run -ti --rm --name mycontainer2 --network pub_net myimage:latest