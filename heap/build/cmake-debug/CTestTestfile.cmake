# CMake generated Testfile for 
# Source directory: /Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap
# Build directory: /Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/build/cmake-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[test-"heap-c"]=] "/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/build/cmake-debug/heap-c")
set_tests_properties([=[test-"heap-c"]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/CMakeLists.txt;20;add_test;/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/CMakeLists.txt;0;")
add_test([=[test-"heap-cpp"]=] "/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/build/cmake-debug/heap-cpp")
set_tests_properties([=[test-"heap-cpp"]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/CMakeLists.txt;28;add_test;/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/CMakeLists.txt;0;")
add_test([=[test-"free-ptr"]=] "/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/build/cmake-debug/free-ptr")
set_tests_properties([=[test-"free-ptr"]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/CMakeLists.txt;35;add_test;/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/CMakeLists.txt;0;")
add_test([=[test-"delete-ptr"]=] "/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/build/cmake-debug/delete-ptr")
set_tests_properties([=[test-"delete-ptr"]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/CMakeLists.txt;41;add_test;/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/CMakeLists.txt;0;")
add_test([=[test-"unique-ptr"]=] "/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/build/cmake-debug/unique-ptr")
set_tests_properties([=[test-"unique-ptr"]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/CMakeLists.txt;47;add_test;/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/CMakeLists.txt;0;")
add_test([=[test-"heapusage"]=] "/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/build/cmake-debug/heapusage")
set_tests_properties([=[test-"heapusage"]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/CMakeLists.txt;54;add_test;/Users/dcblack/Videos/Doulos-Videos/Webinars/2022_02_CnCpp_Memory_Management/MemoryManagement/heap/CMakeLists.txt;0;")
subdirs("corrupted")
subdirs("fragmented")
subdirs("overlooked")
