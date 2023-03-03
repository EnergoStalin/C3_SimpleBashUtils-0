#!/bin/sh

# while sleep 3600; do :; done

cd ../cat && make _test_prebuild & \
cd ../grep && make _test_prebuild
