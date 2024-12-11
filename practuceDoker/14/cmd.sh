docker build -t learning:latest .
docker run -ti --rm --name mycontainer learning:latest
# docker logs -f mycontainer
# docker exec -ti mycontainer /bin/bash