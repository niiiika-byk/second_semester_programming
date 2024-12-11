docker build -t myimage:latest .
docker volume create newvolume
docker run -ti --rm --name mycontainer -v $(pwd)/filedir:/home/filedir -v newvolume:/home/otherfiledir myimage:latest
docker volume inspect newvolume
cat /var/lib/docker/volumes/newvolume/_data/text.txt
docker volume rm newvolume