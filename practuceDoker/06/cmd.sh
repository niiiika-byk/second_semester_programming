docker build -t myimage:1 -f Dockerfile1 .
docker build -t myimage:2 -f Dockerfile2 .
docker run -ti --rm --name mycontainer myimage:1
docker run -ti --rm --name mycontainer myimage:2
