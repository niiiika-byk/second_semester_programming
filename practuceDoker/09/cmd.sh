docker build -t myimage:latest .
docker run -ti --rm --name mycontainer -v $(pwd)/filedir:/home/filedir myimage:latest