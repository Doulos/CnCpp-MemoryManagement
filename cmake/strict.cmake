# Turn on maximum warnings for compilers we use

if (MSVC)
    # warning level 4
    add_compile_options( /W4 /WX )
else() # GCC or LLVM
    # lots of warnings
    add_compile_options( -Wall -Wextra -pedantic )
endif()

# vim:nospell
