#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
    DESTDIR_ARG="--root=$DESTDIR"
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/ridma/mybot_ws/src/simple_navigation_goals"

# snsure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/ridma/mybot_ws/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/ridma/mybot_ws/install/lib/python2.7/dist-packages:/home/ridma/mybot_ws/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/ridma/mybot_ws/build" \
    "/usr/bin/python" \
    "/home/ridma/mybot_ws/src/simple_navigation_goals/setup.py" \
    build --build-base "/home/ridma/mybot_ws/build/simple_navigation_goals" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/ridma/mybot_ws/install" --install-scripts="/home/ridma/mybot_ws/install/bin"
