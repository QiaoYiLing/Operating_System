
if ! [ -x /opt/gcc-3.4.6-2f ]  ; then
wget http://mirrors.ustc.edu.cn/loongson/loongson1b/Tools/toolchain/gcc-3.4.6-2f.tar.gz -c
tar zxvf gcc-3.4.6-2f.tar.gz
mkdir -p /opt
mv gcc-3.4.6-2f /opt
fi

PATH=/opt/gcc-3.4.6-2f/bin:$PATH
