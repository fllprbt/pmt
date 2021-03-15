# Currently works only for Linux (A solution to expose sound hardware to Mac is under investigation)
FROM ubuntu:18.04
RUN apt-get update 
RUN apt-get install git g++ libasound-dev qt5-default make libaubio-dev portaudio19-dev -y
RUN git clone https://github.com/fllprbt/pmt --recurse-submodules /app
WORKDIR /app/portaudio
RUN ./configure && make
WORKDIR /app
RUN qmake src/pmt.pro
RUN make clean
RUN make
RUN usermod -aG audio root
CMD ["./pmt"]
