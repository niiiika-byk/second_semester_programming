docker build -t myimage:1 app1dir/
docker build -t myimage:2 app2dir/
docker run -ti --rm --name mycontainer myimage:1
docker run -ti --rm --name mycontainer myimage:2
docker run -ti --rm --name mycontainer myimage:2 python app1.py
