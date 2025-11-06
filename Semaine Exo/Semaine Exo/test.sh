#!/bin/bash

# Script de test rapide pour le parser OBJ

echo "========================================="
echo "Test du Parser OBJ"
echo "========================================="
echo ""

# Compilation
echo "[1/3] Compilation..."
g++ -std=c++17 -o TestObjParser TestObjParser.cpp ObjParser.cpp 2>&1

if [ $? -ne 0 ]; then
    echo "❌ Erreur de compilation"
    exit 1
fi

echo "✅ Compilation reussie"
echo ""

# Test 1: cube.obj
echo "[2/3] Test avec cube.obj..."
echo "-------------------------------------------"
./TestObjParser cube.obj
echo ""

# Test 2: test-formats.obj
echo "[3/3] Test avec test-formats.obj..."
echo "-------------------------------------------"
./TestObjParser test-formats.obj
echo ""

echo "========================================="
echo "✅ Tous les tests sont termines"
echo "========================================="
