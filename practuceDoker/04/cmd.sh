docker build -t myimage:latest -f appdir/Dockerfile .
docker run -ti --rm --name mycontainer myimage:latest
