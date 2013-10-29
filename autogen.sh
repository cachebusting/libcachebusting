#!/bin/bash
mkdir m4 && aclocal --install -I m4 && autoreconf -vif || exit 1
