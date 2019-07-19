FROM cgal/testsuite-docker:ubuntu
MAINTAINER Yuanxin Zhong <zyxin@umich.edu>

ARG CGAL_VERSION=4.14

# Install dependencies
RUN apt-get install git python3-pip -y
RUN pip3 install numpy scikit-build

# Build CGAL
RUN git clone https://github.com/CGAL/cgal.git -b releases/CGAL-${CGAL_VERSION}
RUN mkdir buildCGAL
RUN cd buildCGAL; cmake ../cgal
RUN cd buildCGAL; make install
