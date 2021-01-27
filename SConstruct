env = Environment()
env.Append(CCFLAGS = '-Wall -Wextra -Wpedantic -Werror -g -O0 -std=c++17')
paths = { 'CPPATH' : ['/opt/hidapi/include'], 'LIBPATH' : ['/opt/hidapi/lib'], 'LIBS' : ['hidapi-libusb']}
env.MergeFlags(paths)

#Object('blackstaramp_hid.cpp', 'blackstaramp_getset.cpp')
#Libarary('blackstar_hid', [FILES...])
env.Decider('MD5-timestamp')
env.Program('blackstar_test.out', Glob('*.cpp'))