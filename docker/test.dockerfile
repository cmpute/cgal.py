FROM cgal:latest
MAINTAINER Yuanxin Zhong <zyxin@umich.edu>

# Build binding
COPY ./ /opt/src/
RUN cd /opt/src ; python3 setup.py build
