#!/usr/bin/env python3
#coding:utf-8

import os
import shutil
import licant

licant.include("rabbit", "rabbit.g.py")

target = "librabbit.so"

install_include_path = '/usr/local/include/rabbit' 
install_directory_path = '/usr/lib/'
install_library_path = os.path.join(install_directory_path, target)


licant.cxx_shared_library("librabbit.so",
	mdepends=[
		"rabbit"
	],
	cxx_flags="-fPIC",
	cc_flags="-fPIC"
)

@licant.routine(deps=["librabbit.so"])
def install():
	os.system("cp {0} {1}".format(target, install_directory_path))
	
	shutil.rmtree(install_include_path, True)
	shutil.copytree("rabbit", install_include_path, 
		symlinks=False, ignore=shutil.ignore_patterns('*.cpp', '*.c'))
	
	print("successfully installed")

licant.ex("librabbit.so")