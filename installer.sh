#!/bin/bash

function showHelp() {
  clear
  echo "Opciones:"
  echo "i: Instala el juego"
  echo "d: Desinstala el juego"
  echo "h: Muestra esta ayuda"
  echo "q: Cierra el instalador"
}

function install() {
  clear
  echo "~~~~~~~ INSTALACIÓN DEL JUEGO ~~~~~~~"
  rm -rf build
  mkdir build
  cd build || (echo "Ocurrió un error durante la instalacion. Terminando"  && exit)
  cmake .. -DINSTALL=ON
  make
  sudo make install
}

function uninstall() {
  clear
  echo "~~~~~~~ DESINSTALANDO ~~~~~~~"
  echo "Removiendo binarios..."
  sudo rm /usr/local/bin/l4dclient /usr/local/bin/l4dserver
  echo "Removiendo bibliotecas..."
  sudo rm /usr/local/lib/libSDL2pp.so*
  echo "Removiendo assets..."
  sudo rm -rf /var/games/l4d/
}

clear
showHelp
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
printf "> Ingrese una opción: "

while true; do
  read option
  clear
  echo ""
  case $option in
  i)
    install
    ;;
  d)
    uninstall
    ;;
  h)
    showHelp
    ;;
  q)
    clear
    exit 0
    ;;
  *)
    echo "Ingresó una opcion que no es valida. Puede ver ayuda con 'h'."
    ;;
  esac
  echo
  echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
  printf "> Ingrese una opción: "
done
