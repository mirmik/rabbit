#!/usr/bin/env python3
#coding:utf-8

import licant

licant.include("igris")
licant.include("nos")
licant.include("rabbit")
licant.include("linalg-v3")

licant.cxx_application("target",
	sources=["main.cpp"],
	mdepends=[
		"rabbit", 
		"nos",
		"linalg-v3"
	]
)

licant.ex("target")