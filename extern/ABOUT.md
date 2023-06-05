This `extern/` directory contains external libraries and scripts needed by this project but not found in the system installation. They are not installed on the OS for many different reasons including:

1. They are third party supplied libraries
2. They are newer or specific variations than needed elsewhere
3. They are not installed on the OS, and perhaps don't belong.
4. You do not have permission to install (e.g., lack root permissions)
5. They may not be managed as git in their original locations
6. They may be completely optional for this project.
7. They need to be configured, built and installed separately. Perhaps they don't use `cmake` (e.g., `autotools`)
8. They do not change often
9. They use a completely different programming language. (debatable)

The `extern/bin/` directory may contain scripts to specifically manage some of these libraries and simplify maintenance. These may also help in porting the project to different platforms.

Libraries that should *not* be here include situations where:

1. Specific customizations need to be added
2. They are specifically designed for this project
3. You will be making changes to them (other than just choosing a different version)
4. The OS installed versions will suffice

The install target for these libraries is the `extern/` directory itself. Hence you will see the directories `include/`, `lib/`, or `share/` directly inside `extern`. Your `cmake` environment should be setup to search these locations. Source for these libraries is under a directory with a name related to the library (e.g., {fmtlib} is located under `extern/fmt`.

Following is conceptual example of what you may see. This example presumes use of the GSL, fmt, and stackusage libraries. The ABOUT.md files, such as this one, are simply documentation notes.

extern/
├── ABOUT.md
├── GSL/
│   └── _SOURCE_
├── bin/
│   ├── ABOUT.md
│   ├── build-fmt
│   ├── build-gsl
│   └── build-stackusage
├── fmt/
│   └── _SOURCE_
├── include/
│   └── _VARIOUS_
├── lib/
│   ├── cmake/
│   └── pkgconfig/
├── share/
│   ├── cmake/
│   └── man/
└── stackusage/
    └── _SOURCE_

<!--- vim:nospell --->
