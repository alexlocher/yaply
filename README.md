# YaPLY - Yet Another PLY library

This is a very simple and easy C++ PLY library, which might be of use for somebody. 

The PLY format is a very simple but highly flexible data format, which was originally designed to store 3D data but can actually be used to store any kind of data. 

For a description of the file format, see here (http://paulbourke.net/dataformats/ply/)

The library is still under development and I'm happy to merge any pull requests fixing bugs ;). 

## Licence 

The library is provided under the MIT licence - as it is and without any warranty. See LICENCE.txt

## Usage

The library consists of a single header file without any external dependencies.

#### create scalar properties out of a vector
```c++
std::vector<float> data(999);
std::generate(data.begin(), data.end(), 
              []{return rand(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));} 
              );

yaply::PlyFile plyFile;
plyFile["vertex"].nrElements = data.size();     // set the number of elements in that property (must be set before data!)
plyFile["vertex"].setScalars("x", data.data()); // copy the data to a single propery
```
#### set multiple scalar properies of an element at once
```c++
std::vector<Eigen::Vector3d> vecOf3dPts;            // sample vector
plyFile["vertex"].nrElements = vecOf3dPts.size(); 
plyFile["vertex"].setScalars["x,y,z", data.data()); // property names separated by comma
```

#### set a list property
```c++
std::vector<std::vector<int>> vecOfPtVisibility;     // sample visibility information for every point
plyFile["vertex"].setList("visibility",vecOfPtVisibility);
```

#### copy the data of a scalar property into a vector
```c++
std::vector<int> d;
plyFile["vertex"].getScalarProperty("propertyname", d); // returns false in case of failure
```

#### save / load ply file
```c++
bool binary = true;
plyFile.save("filename.ply", binary);

yaply::PlyFile f;
f.load("filename.ply"); // returns false in case of failure
```

## Installation
Since this is a pure header based library without any dependencies, the installation is super simple ;). 
You can also use cmake:

```bash
git clone https://github.com/alexlocher/yaply.git
cd yaply && mkdir build && cd build
cmake ..
make install
```
