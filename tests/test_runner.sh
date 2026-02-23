#!/usr/bin/env bash
set -e

echo "🧪 Compilando..."
make clean
make

echo "🧪 Test 1: tiempo y salir"
printf "tiempo\nsalir\n" | ./build/sistema_os > /tmp/eafitos_out.txt

grep -q "Fecha y Hora" /tmp/eafitos_out.txt && echo "✅ OK tiempo" || (echo "❌ Falló tiempo" && exit 1)

echo "🧪 Test 2: ayuda por comando"
printf "ayuda calc\nsalir\n" | ./build/sistema_os > /tmp/eafitos_help.txt
grep -q "Calculadora" /tmp/eafitos_help.txt && echo "✅ OK ayuda calc" || (echo "❌ Falló ayuda calc" && exit 1)

echo "✅ Todos los tests pasaron"