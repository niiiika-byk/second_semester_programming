docker build -t myimage:latest -f ./Dockerfile_free_name ./appdir
docker run -ti --rm --name mycontainer myimage:latest
