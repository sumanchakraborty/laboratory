
# when a container spawned as daemon,
# use following commands to control it
# - docker start <container-id>
# - docker stop <container-id>
# - docker rm <container-id>

# cleanup unused images
docker rm `docker ps -aq --no-trunc --filter "status=exited"`
docker rmi `docker images --filter 'dangling=true' -q --no-trunc`
docker images

docker build -t web .

docker run -p 8080:8080 -ti web bash   # command mode
# docker run -d -p 8080:8080 web myapp # deamon mode

