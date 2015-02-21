<img src="https://github.com/bashrc/libdeep/blob/master/examples/cancer_classification/cancer_detection_training_error.png?raw=true" width=640/>

This is a C library which can be used in deep learning applications.  It allows multiple layers to be trained and also includes the dropouts technique to avoid overfitting the data.

A Python API for libdeep can be found at https://github.com/bashrc/libdeep-python

Installation
============

On Debian based systems:

```bash
sudo apt-get install build-essential gnuplot doxygen
```

On Fedora based systems:

```bash
sudo yum groupinstall "Development Tools"
sudo yum install gnuplot doxygen
```

To build from source:

```bash
make
sudo make install
```

This creates the library and installs it into /usr/local

Unit Tests
==========

You can run the unit tests to check that the system is working as expected:

```bash
make tests
./tests
```

Or to check for any memory leaks:

```bash
valgrind --leak-check=full ./tests
```

Source Documentation
====================

To generate source code documentation make sure that you have doxygen installed and then run the generatedocs.sh script.  A subdirectory called docs will be created within which html and latex formated documentation can be found.  For general usage information you can also see the manpage.

```bash
man libdeep
```

Examples
========

<img src="https://github.com/bashrc/libdeep/blob/master/examples/facerec/libdeep_facerec.png?raw=true" width=300/>

There are also some example programs within the examples directory. Reading the examples is the best way to learn how to use this library within your own code. Examples are:

 * Simple face recognition
 * Determining whether a cancer is malignant or benign
 * Assessing wine quality from ingredients
 * Predicting concrete quality from ingredients

Portability
===========

Although this software was primarily written to run on Linux-based systems it's pretty much just vanilla C code and so it should be easily portable to other platforms, such as Microsoft Windows and Mac systems. The independent random number generator should mean that results are consistent across different compilers and platforms.

Packaging
=========

To build packages for Debian (deb) or Fedora (rpm) based systems there are two scripts, debian.sh and rpm.sh which can be used to generate packages for convenient installation.
