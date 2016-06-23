#!/bin/bash

PROTODIR=$HOME/appsvr/thirdparty/protobuf
mkdir $PROTODIR/lib64_debug 
mkdir $PROTODIR/lib64_release

cp $PROTODIR/src/.libs/libprotobuf.a $PROTODIR/lib64_debug/libprotobuf.a
cp $PROTODIR/src/.libs/libprotobuf.a $PROTODIR/lib64_release/libprotobuf.a
