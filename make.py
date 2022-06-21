#!/usr/bin/env python3
#coding:utf-8

import os
import shutil
import licant
import licant.install

licant.include("rabbit", "rabbit.g.py")

target = "librabbit.so"

install_include_path = '/usr/local/include/rabbit' 
install_directory_path = '/usr/lib/'
install_library_path = os.path.join(install_directory_path, target)


licant.cxx_shared_library("librabbit.so",
	mdepends=[
		"rabbit",
		"rabbit.opengl"
	],
	cxx_flags="-fPIC -Weffc++ -Wextra",
	cc_flags="-fPIC",
	cxxstd = "c++2a"
)

licant.install.install_library(
	tgt="install",
	uninstall="uninstall",
	libtgt="librabbit.so",
	hroot="rabbit",
	headers="rabbit")

licant.ex("librabbit.so")
