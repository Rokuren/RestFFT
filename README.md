# RestFFT

# Build Casablanca
sudo apt-get install g++-4.8 g++ git make libboost1.54-all-dev libssl-dev cmake

git clone https://git.codeplex.com/casablanca

cd casablanca/Release
mkdir build.release
cd build.release
CXX=g++-4.8 cmake .. -DCMAKE_BUILD_TYPE=Release
make

# Add Library Path
export LD_LIBRARY_PATH=/home/rokuren/Workspace/casablanca/Release/build.release/Binaries:$LD_LIBRARY_PATH

# Run Command

g++ -std=c++11 Server.cpp -I ~/Workspace/RestFFT/include/ -L /home/rokuren/Workspace/casablanca/Release/build.release/Binaries/ -o server -lboost_system -lcpprest -lcrypto -lssl

