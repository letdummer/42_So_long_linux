#!/bin/bash

# Caminho do executável
PROGRAMA="./so_long"

# Lista de mapas de teste
MAPAS=(
"./maps/invalid/map_extra_player.ber"
"./maps/invalid/map_not_retangular.ber"
#"./maps/invalid/map_no_collectible.ber"
#"./maps/invalid/map_no_wall.ber"
)

# Loop para testar cada mapa
i=1
for MAPA in "${MAPAS[@]}"
do
    echo "# Teste [$i] => $MAPA"
    
    if [ -f "$MAPA" ]
    then
        $PROGRAMA "$MAPA"
        STATUS=$?

        if [ $STATUS -ne 0 ]
        then
            echo "-> OK: Erro detectado como esperado (retorno $STATUS)"
        else
            echo "-> FALHA: Programa aceitou mapa inválido (retorno $STATUS)"
        fi
    else
        echo "-> ERRO: Arquivo de mapa não encontrado: $MAPA"
    fi

    echo "-----------------------------"
    sleep 1
    i=$((i + 1))
done
