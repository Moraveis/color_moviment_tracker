#!/bin/sh

echo '========================================================='
echo '  	INSTALAÇÃO REALIZADA UBUNTU 16.04 LTS X64'
echo '========================================================='
echo ''
echo ''
echo ''
echo ''

echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo ' Iniciando Instalação ...................................'
echo '========================================================='


echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo ' Update dos Repositorios e programas ....................'
echo '========================================================='
	sudo apt-get update -y
	sudo apt-get upgrade -y

echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo ' Instalando Bibliotecas Multimidia Padrão ...............'
echo '========================================================='
	sudo apt-get install -y build-essential cmake
	sudo apt-get install -y git
	sudo apt-get install -y libgtk2.0-dev
	sudo apt-get install -y pkg-config 
	sudo apt-get install -y libavcodec-dev
	sudo apt-get install -y libavformat-dev
	sudo apt-get install -y libswscale-dev
	sudo apt-get install -y python-dev
	sudo apt-get install -y python-numpy
	sudo apt-get install -y libjpeg-dev
	sudo apt-get install -y libpng-dev
	sudo apt-get install -y libtiff-dev
	sudo apt-get install -y libtiff5-dev
	sudo apt-get install -y libjasper-dev
	sudo apt-get install -y libgdal-dev
	sudo apt-get install -y zlib1g-dev
	sudo apt-get install -y libwebp-dev
	sudo apt-get install -y libx264-dev
	sudo apt-get install -y yasm
	sudo apt-get install -y libgstreamer0.10-dev libfaac-dev
	sudo apt-get install -y libdc1394-22-dev
	sudo apt-get install -y libxine2-dev
	sudo apt-get install -y libgstreamer-plugins-base0.10-dev
	sudo apt-get install -y libv4l-dev
	sudo apt-get install -y libqt4-dev
	sudo apt-get install -y libfaac-dev
	sudo apt-get install -y libmp3lame-dev
	sudo apt-get install -y libopencore-amrnb-dev
	sudo apt-get install -y libopencore-amrwb-dev
	sudo apt-get install -y libvorbis-dev
	sudo apt-get install -y libtheora-dev
	sudo apt-get install -y libxvidcore-dev x264 v4l-utils unzip
	sudo apt-get install -y ffmpeg

echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo ' Instalando Frameworks paralelos ........................'
echo '========================================================='
	sudo apt-get install -y libtbb-dev 
	sudo apt-get install -y libtbb2
	sudo apt-get install -y libtbb2-dbg 
	sudo apt-get install -y libpomp2-dev

echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo ' Instalando suporte a Linguagem Python ..................'
echo '========================================================='
	sudo apt install python-dev python-tk python-numpy python3-dev python3-tk python3-numpy

echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo ' Instalando Java Oracle JDK 8 ...........................'
echo '========================================================='
	sudo add-apt-repository ppa:webupd8team/java 
	sudo apt update -y
	sudo apt install oracle-java8-installer -y
	sudo apt install ant -y

echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo ' Instalando bibliotecas Extras ..........................'
echo '========================================================='
	sudo apt-get install -y libeigen3-dev
	sudo apt-get install -y doxygen
	sudo apt-get install -y libgl1-mesa-dev
	sudo apt-get install -y libglu1-mesa-dev
	sudo apt-get install -y mesa-common-dev
	sudo apt-get install -y qt5-default
	sudo apt-get install -y libatlas-base-dev
	sudo apt-get install -y gfortran

echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo ' Atualizando Repositórios de busca ......................'
echo '========================================================='
	sudo apt-get update -y

echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo ' Atualizando Programas Instalados .......................'
echo '========================================================='
	sudo apt-get upgrade -y

echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo ' Acessando Diretorio de Instalalção .....................'
echo ' Obs.: Foi utilizado diretorio padrão do user linux .....'
echo ' Obs2.: Se houver alteração no terminar informa o caminho'			
echo ' Exempo " cd /home/meuUsuarioPadrao" ....................'
echo '========================================================='
	cd /home/edmilson

echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo ' Copiando respositorio Git ..............................'
echo '========================================================='
echo ''
echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo ' Copiando OpenCv 3.1 ......'
echo '========================================================='
	git clone https://github.com/Itseez/opencv.git

echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo ' Copiando OpenCv Contrib ......'
echo '========================================================='
	git clone https://github.com/Itseez/opencv_contrib.git

echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo ' Criando pasta "build" dentro de openCV .................'
echo '========================================================='
cd opencv/
mkdir build
cd build/

echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo '  Compilando arquivos da pasta opencv ...................'
echo '========================================================='
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D WITH_V4L=ON -D WITH_QT=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules -D BUILD_EXAMPLES=ON -D WITH_OPENGL=ON ..

make -j4 "# runs 8 jobs in parallel"

echo ''
echo ''
echo ''
echo ''
echo '========================================================='
echo ' Instalando os arquivos compilados ......................'
echo '========================================================='

sudo make install

sudo /bin/bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig

echo ''
echo ''
echo ''
echo ''
echo '======================================================='
echo ' SE NÃO APRESENTOU NENHUM ERRO CRITICO, PARABÉNS !!!!! '
echo '  	OPENCV INSTALADO COM SUCESSO !!!!! '
echo '======================================================='
