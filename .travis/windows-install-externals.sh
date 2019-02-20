#!/bin/bash

externals_install_dir_name=externals-install
externals_install_bindir=$externals_install_dir_name/bin
externals_install_includedir=$externals_install_dir_name/include
externals_install_libdir=$externals_install_dir_name/lib

mkdir -p $externals_install_bindir
mkdir -p $externals_install_includedir
mkdir -p $externals_install_libdir

# Download and install glew
wget https://sourceforge.net/projects/glew/files/latest/download/glew-2.1.0-win32.zip
7z x glew-2.1.0-win32.zip
cp glew-2.1.0/bin/Release/x64/glew32.dll $externals_install_bindir
cp -r glew-2.1.0/include/GL $externals_install_includedir
cp glew-2.1.0/lib/Release/x64/glew32.lib $externals_install_libdir

# Download and install GLM
wget https://github.com/g-truc/glm/archive/stable.zip
7z x stable.zip
cd glm-stable
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$TRAVIS_BUILD_DIR/$externals_install_dir_name -DGLM_TEST_ENABLE=OFF -G "Visual Studio 15 2017 Win64" ..
cmake --build . --config Release --target INSTALL
cd ../..

# Download and install freeglut
wget https://sourceforge.net/projects/freeglut/files/freeglut/3.0.0/freeglut-3.0.0.tar.gz
7z x freeglut-3.0.0.tar.gz && 7z x freeglut-3.0.0.tar
cd freeglut-3.0.0
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$TRAVIS_BUILD_DIR/$externals_install_dir_name -DFREEGLUT_BUILD_DEMOS=OFF -DFREEGLUT_BUILD_SHARED_LIBS=ON -DFREEGLUT_BUILD_STATIC_LIBS=OFF -DINSTALL_PDB=OFF -G "Visual Studio 15 2017 Win64" ..
cmake --build . --config Release --target INSTALL
cd ../..

# Clean to avoid search pollution
rm -rf *.zip *.tar.gz glew-2.1.0 glm-stable freeglut-3.0.0
