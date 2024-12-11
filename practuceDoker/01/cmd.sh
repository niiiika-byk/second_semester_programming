docker build -t myimage:latest .
docker run -ti --rm --name mycontainer myimage:latest
docker build -q -t myimage:latest .
docker build --pull -t myimage:latest .