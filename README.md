# RestFFT

# Build Casablanca
sudo apt-get install g++-4.8 g++ git make libboost1.54-all-dev libssl-dev cmake

git clone https://git.codeplex.com/casablanca

cd casablanca/Release
mkdir build.release
cd build.release
CXX=g++-4.8 cmake .. -DCMAKE_BUILD_TYPE=Release
make

# Install fftw | Might have been fixed by the linker addition
http://www.fftw.org/
./configure
make
make install

# Add Library Path
export LD_LIBRARY_PATH=/home/rokuren/Workspace/casablanca/Release/build.release/Binaries:$LD_LIBRARY_PATH

# Run Command || If I have time try to remember how to make a make file

g++ -std=c++11 Server.cpp lodepng.cpp fftw++.cc -I ~/Workspace/RestFFT/include/ -L /home/rokuren/Workspace/casablanca/Release/build.release/Binaries/ -o server -lboost_system -lcpprest -lcrypto -lssl -lfftw3

# Curl Command

curl --header "Content-Type:application/octet-stream" --data-binary @spiderman.png http://localhost:18080/transform > out.cplx
