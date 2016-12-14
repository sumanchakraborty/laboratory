FROM centos:latest

MAINTAINER Suman Chakraborty <suman.chakraborty@gmail.com>

RUN yum -y update
RUN yum -y groupinstall 'Development Tools'
RUN yum -y install epel-release
RUN yum -y install vim dos2unix net-tools
RUN yum -y install golang curl git
RUN yum -y clean all

RUN mkdir /go
ENV GOPATH /go
ENV PATH $GOPATH:$PATH

WORKDIR ${GOPATH}
ADD . ${GOPATH}

RUN go get github.com/gorilla/mux
RUN go build -o myapp;

EXPOSE 8080
# ENTRYPOINT ["myapp"]
