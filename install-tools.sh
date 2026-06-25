#!/bin/bash
# Script d'installation des outils pour développer un OS
echo "=== Installation des outils ==="
sudo apt update
sudo apt install -y \
    nasm \
    grub-pc-bin \
    grub-common \
    xorriso \
    qemu-system-x86 \
    build-essential
echo ""
echo "=== Vérification ==="
for tool in nasm grub-mkrescue xorriso qemu-system-x86_64 gcc ld; do
    if command -v $tool &> /dev/null; then
        echo "✓ $tool"
    else
        echo "✗ $tool MANQUANT"
    fi
done
echo ""
echo "Tout est prêt ! Lance 'make' pour compiler ton OS."
