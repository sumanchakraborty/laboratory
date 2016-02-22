#!/bin/bash

CONFIG=Doxyfile
TEMPCONFIG=.tempfile

if [ ! -d "docs" ]; then
  mkdir docs
fi
cd docs
rm $CONFIG
doxygen -g
sed 's/My Project/libdeep/g' $CONFIG > $TEMPCONFIG
cp $TEMPCONFIG $CONFIG
sed 's@PROJECT_LOGO           =@PROJECT_LOGO           = ../img/logo55.png@g' $CONFIG > $TEMPCONFIG
cp $TEMPCONFIG $CONFIG
sed 's@INPUT                  =@INPUT                  = ../src ../examples/concreteslump ../examples/facerec@g' $CONFIG > $TEMPCONFIG
cp $TEMPCONFIG $CONFIG
sed 's/SOURCE_BROWSER         = NO/SOURCE_BROWSER         = YES/g' $CONFIG > $TEMPCONFIG
cp $TEMPCONFIG $CONFIG
sed 's/INLINE_SOURCES         = NO/INLINE_SOURCES         = YES/g' $CONFIG > $TEMPCONFIG
cp $TEMPCONFIG $CONFIG
sed 's/OPTIMIZE_OUTPUT_FOR_C  = NO/OPTIMIZE_OUTPUT_FOR_C  = YES/g' $CONFIG > $TEMPCONFIG
cp $TEMPCONFIG $CONFIG
sed 's/EXTRACT_ALL            = NO/EXTRACT_ALL            = YES/g' $CONFIG > $TEMPCONFIG
cp $TEMPCONFIG $CONFIG
sed 's/EXTRACT_STATIC         = NO/EXTRACT_STATIC         = YES/g' $CONFIG > $TEMPCONFIG
cp $TEMPCONFIG $CONFIG
rm $TEMPCONFIG
doxygen $CONFIG
