#!/usr/bin/env bash
set -e

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null && pwd)"
ARCH="$(uname -m)"

ACADOS_FLAGS="-DACADOS_WITH_QPOASES=ON -UBLASFEO_TARGET -DBLASFEO_TARGET=$BLAS_TARGET"

if [[ "$OSTYPE" == "darwin"* ]]; then
  ARCHNAME="Darwin"
  ACADOS_FLAGS="$ACADOS_FLAGS -DCMAKE_OSX_ARCHITECTURES=arm64;x86_64 -DCMAKE_MACOSX_RPATH=1"
elif [ -f /TICI ]; then
  ARCHNAME="agnos-aarch64"
  BLAS_TARGET="ARMV8A_ARM_CORTEX_A57"
elif [[ "$ARCH" == "aarch64" ]]; then
  ARCHNAME="linux-aarch64"
  BLAS_TARGET="ARMV8A_ARM_CORTEX_A57"
else
  ARCHNAME="linux-x86_64"
  BLAS_TARGET="X64_AUTOMATIC"
fi

if [ ! -d acados_repo/ ]; then
  git clone https://github.com/acados/acados.git $DIR/acados_repo
  # git clone https://github.com/commaai/acados.git $DIR/acados_repo
fi
cd acados_repo
git fetch --all
git checkout 8ea8827fafb1b23b4c7da1c4cf650de1cbd73584
git submodule update --recursive --init

# build
mkdir -p build
cd build
cmake $ACADOS_FLAGS ..
make -j20 install

INSTALL_DIR="$DIR/$ARCHNAME"
rm -rf $INSTALL_DIR
mkdir -p $INSTALL_DIR

rm $DIR/acados_repo/lib/*.json

rm -rf $DIR/include $DIR/acados_template
cp -r $DIR/acados_repo/include $DIR
cp -r $DIR/acados_repo/lib $INSTALL_DIR
cp -r $DIR/acados_repo/interfaces/acados_template/acados_template $DIR/
#pip3 install -e $DIR/acados/interfaces/acados_template

# build tera
cd $DIR/acados_repo/interfaces/acados_template/tera_renderer/
if [[ "$OSTYPE" == "darwin"* ]]; then
  cargo build --verbose --release --target aarch64-apple-darwin
  cargo build --verbose --release --target x86_64-apple-darwin
  lipo -create -output target/release/t_renderer target/x86_64-apple-darwin/release/t_renderer target/aarch64-apple-darwin/release/t_renderer
else 
  cargo build --verbose --release
fi
cp target/release/t_renderer $INSTALL_DIR/
